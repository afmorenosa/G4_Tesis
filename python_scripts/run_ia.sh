#!/bin/bash
# Config for LinuxPlus.
# export PYTHONPATH=/afs/cern.ch/user/a/amorenos/.local/lib/python3/lib/python3.6/site-packages/:/afs/cern.ch/user/a/amorenos/.local/lib/python3/lib64/python3.6/site-packages/:$PYTHONPATH

python ia_train.py -tr /run/media/kittycata/f3693830-8b69-459b-be98-62f207ddee77/spacecata/Documents/Projects/Geant4/G4_Tesis/run/run_2/run_2_group_1_A_*_t0.root -ts /run/media/kittycata/f3693830-8b69-459b-be98-62f207ddee77/spacecata/Documents/Projects/Geant4/G4_Tesis/run/run_2/run_2_group_1_F_*_t0.root -c MultinomialNB

python ia_train.py -tr /run/media/kittycata/f3693830-8b69-459b-be98-62f207ddee77/spacecata/Documents/Projects/Geant4/G4_Tesis/run/run_2/run_2_group_1_A_*_t0.root -ts /run/media/kittycata/f3693830-8b69-459b-be98-62f207ddee77/spacecata/Documents/Projects/Geant4/G4_Tesis/run/run_2/run_2_group_1_F_*_t0.root -c BernoulliNB

python ia_train.py -tr /run/media/kittycata/f3693830-8b69-459b-be98-62f207ddee77/spacecata/Documents/Projects/Geant4/G4_Tesis/run/run_2/run_2_group_1_A_*_t0.root -ts /run/media/kittycata/f3693830-8b69-459b-be98-62f207ddee77/spacecata/Documents/Projects/Geant4/G4_Tesis/run/run_2/run_2_group_1_F_*_t0.root -c Perceptron

python ia_train.py -tr /run/media/kittycata/f3693830-8b69-459b-be98-62f207ddee77/spacecata/Documents/Projects/Geant4/G4_Tesis/run/run_2/run_2_group_1_A_*_t0.root -ts /run/media/kittycata/f3693830-8b69-459b-be98-62f207ddee77/spacecata/Documents/Projects/Geant4/G4_Tesis/run/run_2/run_2_group_1_F_*_t0.root -c SGDClassifier

python ia_train.py -tr /run/media/kittycata/f3693830-8b69-459b-be98-62f207ddee77/spacecata/Documents/Projects/Geant4/G4_Tesis/run/run_2/run_2_group_1_A_*_t0.root -ts /run/media/kittycata/f3693830-8b69-459b-be98-62f207ddee77/spacecata/Documents/Projects/Geant4/G4_Tesis/run/run_2/run_2_group_1_F_*_t0.root -c PassiveAggressiveClassifier
