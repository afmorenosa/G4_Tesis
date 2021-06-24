#!/bin/bash
#export PYTHONPATH=/afs/cern.ch/user/a/amorenos/.local/lib/python3/lib/python3.6/site-packages/:/afs/cern.ch/user/a/amorenos/.local/lib/python3/lib64/python3.6/site-packages/:$PYTHONPATH

source /cvmfs/sft.cern.ch/lcg/views/LCG_85swan3/x86_64-slc6-gcc49-opt/setup.sh

echo "Running MultinomialNB"
python ia_train.py -tr /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[A-E]* -ts /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[F-J]* -c MultinomialNB

echo "Running BernoulliNB"
python ia_train.py -tr /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[A-E]* -ts /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[F-J]* -c BernoulliNB

echo "Running Perceptron"
python ia_train.py -tr /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[A-E]* -ts /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[F-J]* -c Perceptron

echo "Running SGDClassifier"
python ia_train.py -tr /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[A-E]* -ts /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[F-J]* -c SGDClassifier

echo "Running PassiveAggressiveClassifier"
python ia_train.py -tr /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[A-E]* -ts /eos/user/a/amorenos/DataG4Thesis/run_2_group_1_[F-J]* -c PassiveAggressiveClassifier
