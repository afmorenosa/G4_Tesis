#!/bin/bash
# Config for LinuxPlus.
export PYTHONPATH=/afs/cern.ch/user/a/amorenos/.local/lib/python3/:/afs/cern.ch/user/a/amorenos/.local/lib/python3/lib/python3.6/site-packages/:/afs/cern.ch/user/a/amorenos/.local/lib/python3/lib64/python3.6/site-packages/:$PYTHONPATH

python3 ia_train.py -tr /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[A-E]* -ts /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[F-J]* -c MultinomialNB

python3 ia_train.py -tr /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[A-E]* -ts /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[F-J]* -c BernoulliNB

python3 ia_train.py -tr /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[A-E]* -ts /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[F-J]* -c Perceptron

python3 ia_train.py -tr /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[A-E]* -ts /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[F-J]* -c SGDClassifier

python3 ia_train.py -tr /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[A-E]* -ts /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[F-J]* -c PassiveAggressiveClassifier
