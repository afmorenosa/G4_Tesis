#!/bin/python3
"""
Train machine learning.

Script that take data from the root files and train a machine learning with
scikitlearn lib.
"""
from sklearn.naive_bayes import MultinomialNB
from sklearn.naive_bayes import BernoulliNB
from sklearn.linear_model import Perceptron
from sklearn.linear_model import SGDClassifier
from sklearn.linear_model import PassiveAggressiveClassifier
# from data_mng import root_files_mng
import root_files_mng
import numpy as np
import argparse

# Set parser for the console arguments.
parser = argparse.ArgumentParser(description='Train and machine learning.',
                                 formatter_class=argparse.RawTextHelpFormatter)

# Set arguments.
parser.add_argument("-tr", "--train", type=str, metavar="train_file",
                    nargs="+",
                    required=True,
                    help="The input root file to train the machine learning.")

parser.add_argument("-ts", "--test", type=str, metavar="test_file", nargs="+",
                    required=True,
                    help="The input root file to test the machine learning.")

parser.add_argument("-c", "--classifier", type=str,
                    metavar="classifier_method", default="MultinomialNB",
                    help="""
The machine learning classifier to be used.
You can select between MultinomialNB, BernoulliNB,
Perceptron, SGDClassifier and PassiveAggressiveClassifier.
(default: MultinomialNB).""")

# Parse arguments.
args = parser.parse_args()

classifiers_dict = {"MultinomialNB": MultinomialNB, "BernoulliNB": BernoulliNB,
                    "Perceptron": Perceptron,
                    "SGDClassifier": SGDClassifier,
                    "PassiveAggressiveClassifier": PassiveAggressiveClassifier}

# Create the classifiers.
print "\nUsing {} classifier".format(args.classifier)
clf = classifiers_dict[args.classifier]()

# Train the data.
print "\nTraining"
root_files_mng.train_data(args.train, clf)
print "Trained\n"

# Get the number of entries.
nentries = root_files_mng.get_nentries(args.test)

# Get the test variables.
root_files_mng.get_data(args.test, nentries)
X_test = np.memmap("x_temp.data", shape=(nentries, 60501))
y_test = np.memmap("y_temp.data", shape=(nentries))

# Print results of the test.
print "\n"
print "Results {}".format(clf.score(X_test, y_test))

# Delete train data.
del X_test, y_test
