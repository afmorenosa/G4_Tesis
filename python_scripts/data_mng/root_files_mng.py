"""Function that manage root files."""
from ROOT import TFile
import numpy as np


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

        # Get number of non-empty entries.
        for entry in photons_branch:
            if len(entry.X):
                nentries += 1

    return nentries


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
    # Create the variables to store the data.
    X_set = np.memmap(x_array_file, mode="w+",
                      shape=(nentries, 14472))
    y_set = np.memmap(y_array_file, mode="w+", shape=(nentries))

    index = 0

    for file_name in files_list:

        # Open root file.
        root_file = TFile.Open(file_name)

        # Get Photons TTree.
        photons_branch = root_file.GetDirectory("ntuple").Get("Photons")

        i = 0
        for entry in photons_branch:

            # Fill the data of the TTree.
            i += 1

            # Print percentage of progress.
            print(f"[{i/photons_branch.GetEntries()*100:.2f}%]",
                  f"getting data from: {file_name} - entry: {i}, of: " +
                  f"{photons_branch.GetEntries()}",
                  f"Non-emtpy data: {index + 1}, of: {nentries}",
                  end="\r")

            if len(entry.X) == 0:
                continue
            photons_counter = np.zeros((6*3, 4*3, 67))  # Sc 14 472, Pb 1 584

            # Set a zeros matrix.
            for photon in range(len(entry.X)):
                photons_counter[3 * entry.X[photon] + entry.c[photon],
                                3 * entry.Y[photon] + entry.r[photon],
                                entry.Z[photon]] += 1

            # Add data.
            X_set[index] = photons_counter.flatten()
            y_set[index] = entry.primary

            index += 1

        # Close root file.
        root_file.Close()
        print()


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
    for file_name in files_list:
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
            print(f"[{i/photons_branch.GetEntries()*100:.2f}%]",
                  f"Getting data from: {file_name} - entry: {i}, of: " +
                  f"{photons_branch.GetEntries()}",
                  end="\r")

            if len(entry.X) == 0:
                continue
            photons_counter = np.zeros((6*3, 4*3, 67))

            # Set a zeros matrix.
            for photon in range(len(entry.X)):
                photons_counter[3 * entry.X[photon] + entry.c[photon],
                                3 * entry.Y[photon] + entry.r[photon],
                                entry.Z[photon]] += 1

            # Add data.
            X_set.append(photons_counter.flatten())
            y_set.append(entry.primary)

        # Train the classifier.
        classification_method.partial_fit(X_set, y_set, classes=[0, 1, 2])

        # Close root file.
        root_file.Close()
        print()
