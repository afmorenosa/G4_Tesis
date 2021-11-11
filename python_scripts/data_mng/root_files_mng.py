"""Function that manage root files."""
from multiprocessing import Pool, cpu_count
from ROOT import TFile
import pandas as pd
import numpy as np


def get_matrix_data(variable, X, Y, Z, c=None, r=None, val=None):
    """
    Get the matrix with the accumulative value.

    Args:
    ----
        variable: The name of the variable that will be getted.
        X: The vector of the values for the x coordinates.
        Y: The vector of the values for the y coordinates.
        Z: The vector of the values for the z coordinates.
        c: The vector of the values for the column in the module cell, if None,
        it is understanded that is from a lead cell.
        r: The vector of the values for the row in the module cell, if None, it
        is understanded that is from a lead cell.
        val: The vector of the values for the variable that will be
        accumulated.

    Returns
    -------
        The matrix with the accumulative value in the significative cells for a
        given variable.

    """
    all_significative_cells = pd.read_csv("significative_cells.csv")

    if c:
        mat_shape = (6*3, 4*3, 67)
        significative_cells = all_significative_cells[
            all_significative_cells.material == "scintillator"
        ]
    else:
        mat_shape = (6, 4, 66)
        significative_cells = all_significative_cells[
            all_significative_cells.material == "lead"
        ]

    photons_counter = np.zeros(mat_shape)  # Sc 14 472, Pb 1 584

    # Set a zeros matrix.
    for step in range(len(X)):
        if c:
            X_val = 3 * X[step] + c[step]
            Y_val = 3 * Y[step] + r[step]
        else:
            X_val = X[step]
            Y_val = Y[step]

        if val:
            acoum = val[step]
        else:
            acoum = 1

        photons_counter[X_val,
                        Y_val,
                        Z[step]] += acoum

    return photons_counter.flatten()[significative_cells[variable]]


def get_values_matrix(entry):
    """
    Get the matrix with all the accumulative significative values.

    Args:
    ----
        entry: The entry from the TTree.

    Returns
    -------
        The matrix with the accumulative value in the significative cells for
        all the variables.

    """
    photons_scintillator = get_matrix_data(
        "photons", entry.X_photons_scintillator, entry.Y_photons_scintillator,
        entry.Z_photons_scintillator, entry.c_photons_scintillator,
        entry.r_photons_scintillator
    )

    electrons_scintillator = get_matrix_data(
        "electrons", entry.X_electrons_scintillator,
        entry.Y_electrons_scintillator, entry.Z_electrons_scintillator,
        entry.c_electrons_scintillator, entry.r_electrons_scintillator
    )

    E_scintillator = get_matrix_data(
        "E", entry.X_step_scintillator, entry.Y_step_scintillator,
        entry.Z_step_scintillator, entry.c_step_scintillator,
        entry.r_step_scintillator, val=entry.E_step_scintillator
    )

    SL_scintillator = get_matrix_data(
        "SL", entry.X_step_scintillator, entry.Y_step_scintillator,
        entry.Z_step_scintillator, entry.c_step_scintillator,
        entry.r_step_scintillator, val=entry.SL_step_scintillator
    )

    photons_lead = get_matrix_data(
        "photons", entry.X_photons_lead, entry.Y_photons_lead,
        entry.Z_photons_lead
    )

    electrons_lead = get_matrix_data(
        "electrons", entry.X_electrons_lead, entry.Y_electrons_lead,
        entry.Z_electrons_lead
    )

    E_lead = get_matrix_data(
        "E", entry.X_step_lead, entry.Y_step_lead, entry.Z_step_lead,
        val=entry.E_step_lead
    )

    SL_lead = get_matrix_data(
        "SL", entry.X_step_lead, entry.Y_step_lead, entry.Z_step_lead,
        val=entry.SL_step_lead
    )

    res_mat = photons_scintillator
    res_mat = np.append(res_mat, electrons_scintillator)
    res_mat = np.append(res_mat, E_scintillator)
    res_mat = np.append(res_mat, SL_scintillator)
    res_mat = np.append(res_mat, photons_lead)
    res_mat = np.append(res_mat, electrons_lead)
    res_mat = np.append(res_mat, E_lead)
    res_mat = np.append(res_mat, SL_lead)

    return res_mat


def get_nentries(files_list):
    """
    Get the total number of entries in the root files.

    Args:
    ----
        files_list: Tupple or list with string of the paths to the
        root files.

    Retrutns:
    --------
        The total number of entries in the given root files.

    """
    # Set .
    nentries = 0

    for file_name in files_list:
        # Open root file.
        root_file = TFile.Open(file_name)

        # Get Photons TTree.
        photons_branch = root_file.GetDirectory("ntuple").Get("Photons")

        nentries += photons_branch.GetEntries()

    return nentries


def get_test_matrix(file_name, X_set, y_set, index, nentries):
    """."""
    # Open root file.
    root_file = TFile.Open(file_name)

    # Get Photons TTree.
    photons_branch = root_file.GetDirectory("ntuple").Get("Photons")

    i = 0
    for entry in photons_branch:

        # Fill the data of the TTree.
        i += 1

        # Print percentage of progress.
        print(
            f"[{i/photons_branch.GetEntries()*100:.2f}%]",
            f"getting data from: {file_name} - entry: {i}, of: " +
            f"{photons_branch.GetEntries()}"
        )

        res_mat = get_values_matrix(entry)

        # Add data.
        X_set[index] = res_mat
        y_set[index] = entry.primary

        index += 1

    # Close root file.
    root_file.Close()
    return True


def get_data(files_list, nentries, x_array_file="x_temp.data",
             y_array_file="y_temp.data"):
    """
    Extract data from a set of files.

    Args:
    ----
        files_list: Tupple or list with string of the paths to the
        root files.
        nentries: Int of the total nomber of entries in the given root files.
        x_array_file: String of the file where the X data is stored.
        y_array_file: String of the file where the y data is stored.

    """
    # Create the pool of processes.
    pool = Pool(processes=int(cpu_count()))

    # Create the variables to store the data.
    X_set = np.memmap(x_array_file, mode="w+",
                      shape=(nentries, 60501))
    y_set = np.memmap(y_array_file, mode="w+", shape=(nentries))

    index = 0

    train_matrices = [
        pool.apply_async(
            get_test_matrix, [file_name, X_set, y_set, index, nentries]
        )
        for file_name in files_list
    ]

    for train_matrix in train_matrices:
        if train_matrix.get(timeout=60000):
            print("Matrix added")


def get_train_matrix(file_name):
    """
    Get the matrix for the training.

    Args:
    ----
        file_name: The root file name.

    """
    X_set = []
    y_set = []

    # Open root file.
    root_file = TFile.Open(file_name)

    # Get Photons TTree.
    photons_branch = root_file.GetDirectory("ntuple").Get("Photons")

    i = 0
    for entry in photons_branch:

        # Fill the data of the TTree.
        i += 1

        # Print percentage of progress.
        print(
            f"[{i/photons_branch.GetEntries()*100:.2f}%]",
            f"Getting data from: {file_name} - entry: {i}, of: " +
            f"{photons_branch.GetEntries()}"

        )
        res_mat = get_values_matrix(entry)

        # Add data.
        X_set.append(res_mat)
        y_set.append(entry.primary)

    # Close root file.
    root_file.Close()

    return [X_set, y_set]


def train_data(files_list, classification_method):
    """
    Train a classifier over a set of files.

    Args:
    ----
        files_list: Tupple or list with string of the paths to the
        root files.
        classification_method: Classification method to be trained. It should
        have partial_fit method.

    """
    # Print the number of cores.
    print(f"n_cpus: {cpu_count()}")

    # Create the pool of processes.
    pool = Pool(processes=int(cpu_count()))

    train_matrices = [
        pool.apply_async(get_train_matrix, [file_name])
        for file_name in files_list
    ]

    for train_matrix in train_matrices:
        res_mat = train_matrix.get(timeout=60000)

        # Train the classifier.
        classification_method.partial_fit(
            res_mat[0],
            res_mat[1],
            classes=[0, 1, 2]
        )
