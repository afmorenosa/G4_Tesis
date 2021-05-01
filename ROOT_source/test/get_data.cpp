#include "get_data.hpp"

//**********************************************************//
// Get the the histogram of the variable given.             //
// If variable is a particle between photons and electrons, //
// it will give a histograms of particle productions in     //
// scintillator.                                            //
//**********************************************************//
std::vector< std::vector<double> > get_matrix_data_scintillator(
  TTree *tree,
  TString variable
) {
  // Create the data vector.
  std::vector< std::vector<double> > data(14472);

  // Initialize variable.
  std::vector<int> *X = {};
  std::vector<int> *Y = {};
  std::vector<int> *Z = {};
  std::vector<int> *c = {};
  std::vector<int> *r = {};
  std::vector<float> *E = {};
  std::vector<float> *SL = {};

  if (variable.EqualTo("E") || variable.EqualTo("SL")) {

    tree->SetBranchAddress("X_step_scintillator", &X);
    tree->SetBranchAddress("Y_step_scintillator", &Y);
    tree->SetBranchAddress("Z_step_scintillator", &Z);
    tree->SetBranchAddress("c_step_scintillator", &c);
    tree->SetBranchAddress("r_step_scintillator", &r);
    tree->SetBranchAddress("E_step_scintillator", &E);
    tree->SetBranchAddress("SL_step_scintillator", &SL);

  } else {

    tree->SetBranchAddress(
      TString("X_") + variable + TString("_scintillator"), &X
    );
    tree->SetBranchAddress(
      TString("Y_") + variable + TString("_scintillator"), &Y
    );
    tree->SetBranchAddress(
      TString("Z_") + variable + TString("_scintillator"), &Z
    );
    tree->SetBranchAddress(
      TString("c_") + variable + TString("_scintillator"), &c
    );
    tree->SetBranchAddress(
      TString("r_") + variable + TString("_scintillator"), &r
    );

  }

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  // Fill histograms.
  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    // Create the vector to store the acumulative value of the variable.
    std::vector<float> values(14472, 0.0);

    for (size_t j = 0; j < X->size(); j++) {

      int coord =
      (X->at(j)*3 + c->at(j))*4*3*67 + (Y->at(j)*3 + r->at(j))*67 + Z->at(j);

      if (variable.EqualTo("E")) {
        values[coord] += E->at(i);
      } else if (variable.EqualTo("SL")) {
        values[coord] += SL->at(i);
      } else {
        values[coord] += 1;
      }

    }

    for (size_t j = 0; j < values.size(); j++) {
      data[j].push_back(values[j]);
    }

  }

  return data;

}

//**********************************************************//
// Get the the histogram of the variable given.             //
// If variable is a particle between photons and electrons, //
// it will give a histograms of particle productions in     //
// lead.                                                    //
//**********************************************************//
std::vector< std::vector<double> > get_matrix_data_lead(
  TTree *tree,
  TString variable
) {
  // Create the data vector.
  std::vector< std::vector<double> > data(1584);

  // Initialize variable.
  std::vector<int> *X = {};
  std::vector<int> *Y = {};
  std::vector<int> *Z = {};
  std::vector<float> *E = {};
  std::vector<float> *SL = {};

  if (variable.EqualTo("E") || variable.EqualTo("SL")) {

    tree->SetBranchAddress("X_step_scintillator", &X);
    tree->SetBranchAddress("Y_step_scintillator", &Y);
    tree->SetBranchAddress("Z_step_scintillator", &Z);
    tree->SetBranchAddress("E_step_scintillator", &E);
    tree->SetBranchAddress("SL_step_scintillator", &SL);

  } else {

    tree->SetBranchAddress(
      TString("X_") + variable + TString("_scintillator"), &X
    );
    tree->SetBranchAddress(
      TString("Y_") + variable + TString("_scintillator"), &Y
    );
    tree->SetBranchAddress(
      TString("Z_") + variable + TString("_scintillator"), &Z
    );

  }

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  // Fill histograms.
  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    // Create the vector to store the acumulative value of the variable.
    std::vector<float> values(1584, 0.0);

    for (size_t j = 0; j < X->size(); j++) {

      if (variable.EqualTo("E")) {
        values[X->at(j)*4*66 + Y->at(j)*66 + Z->at(j)] += E->at(i);
      } else if (variable.EqualTo("SL")) {
        values[X->at(j)*4*66 + Y->at(j)*66 + Z->at(j)] += SL->at(i);
      } else {
        values[X->at(j)*4*66 + Y->at(j)*66 + Z->at(j)] += 1;
      }

    }

    for (size_t j = 0; j < values.size(); j++) {
      data[j].push_back(values[j]);
    }

  }

  return data;

}

//
// get_data.cpp ends here.
//
