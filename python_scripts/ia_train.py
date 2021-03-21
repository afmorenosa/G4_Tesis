"""
Train machine learning.

Script that take data from the root files and train a machine learning with
scikitlearn lib.
"""
from sklearn.neural_network import MLPClassifier
from ROOT import TFile
import numpy as np
import argparse

# Set parser for the console arguments.
parser = argparse.ArgumentParser(description='Train and machine learning.')

# Set arguments.
parser.add_argument("-tr", "--train", type=str, metavar="train_file",
                    nargs="+",
                    required=True,
                    help="The input root file to train the machine learning")

parser.add_argument("-ts", "--test", type=str, metavar="test_file", nargs="+",
                    required=True,
                    help="The input root file to test the machine learning")

# Parse arguments.
args = parser.parse_args()


def get_data(files_list):
    """Extract data from a set of files.

    Args:
    ----
        files_list: Tupple or list with the paths to the
        root files.

    Retrutns:
    --------
        Two lists with the data of the number of the photons created in each
        scintillator and the primary particle.

    """
    # Create the testing variable.
    X_set = []
    y_set = []

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
                  f"gettin data from: {file_name} - entry: {i} of: " +
                  f"{photons_branch.GetEntries()}",
                  end="\r")

            if len(entry.X) == 0:
                continue

            photons_counter = np.zeros((16*3, 8*3, 67))

            # Set a zeros matrix.
            for x in entry.X:
                for y in entry.Y:
                    for z in entry.Z:
                        photons_counter[x, y, z] += 1
            # Add data.
            X_set.append(photons_counter.flatten())
            y_set.append(entry.primary)

        # Close root file.
        root_file.Close()
        print()

    # Return data sets.
    return X_set, y_set


# Create the classifiers.
clf = MLPClassifier(solver='adam', alpha=1e-5,
                    hidden_layer_sizes=(5, 7, 9, 4, 3), random_state=1)

# Create the training variables.
X_train, y_train = get_data(args.train)

# Train the data.
print("\nTraining", f"Total of data: {len(X_train)}")
clf.fit(X_train, y_train)
print("Trained\n")

X_test, y_test = get_data(args.test)

# Print results of the test.
print("\n")
print(f"Results {clf.score(X_test, y_test)}")
