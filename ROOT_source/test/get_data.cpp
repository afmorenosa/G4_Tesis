#include "get_data.hpp"

//**********************************************************//
// Get the the data vector of the variable given.           //
// If variable is a particle between photons and electrons, //
// it will give a data vector of particle production in     //
// both materials, scintillator and lead                    //
//**********************************************************//
std::map< TString, std::vector< std::vector<double> > > get_complete_matrix_data(
  TTree *tree
) {
  // Create the map for data vectors.
  std::map< TString, std::vector< std::vector<double> > > data;

  // Create the data vectors
  data["scintillator_E"] = std::vector< std::vector<double> >(14472);
  data["scintillator_SL"] = std::vector< std::vector<double> >(14472);
  data["scintillator_photons"] = std::vector< std::vector<double> >(14472);
  data["scintillator_electrons"] = std::vector< std::vector<double> >(14472);
  data["lead_E"] = std::vector< std::vector<double> >(1584);
  data["lead_SL"] = std::vector< std::vector<double> >(1584);
  data["lead_photons"] = std::vector< std::vector<double> >(1584);
  data["lead_electrons"] = std::vector< std::vector<double> >(1584);

  // Initialize data variables.

  // - For scintillator.
  // -- For E and S.
  std::vector<int> *X_scintillator_step = {};
  std::vector<int> *Y_scintillator_step = {};
  std::vector<int> *Z_scintillator_step = {};
  std::vector<int> *c_scintillator_step = {};
  std::vector<int> *r_scintillator_step = {};
  std::vector<float> *E_scintillator = {};
  std::vector<float> *SL_scintillator = {};
  // -- For photons.
  std::vector<int> *X_scintillator_photons = {};
  std::vector<int> *Y_scintillator_photons = {};
  std::vector<int> *Z_scintillator_photons = {};
  std::vector<int> *c_scintillator_photons = {};
  std::vector<int> *r_scintillator_photons = {};
  // -- For electrons.
  std::vector<int> *X_scintillator_electrons = {};
  std::vector<int> *Y_scintillator_electrons = {};
  std::vector<int> *Z_scintillator_electrons = {};
  std::vector<int> *c_scintillator_electrons = {};
  std::vector<int> *r_scintillator_electrons = {};

  // - For lead.
  // -- For E and S.
  std::vector<int> *X_lead_step = {};
  std::vector<int> *Y_lead_step = {};
  std::vector<int> *Z_lead_step = {};
  std::vector<float> *E_lead = {};
  std::vector<float> *SL_lead = {};
  // -- For photons.
  std::vector<int> *X_lead_photons = {};
  std::vector<int> *Y_lead_photons = {};
  std::vector<int> *Z_lead_photons = {};
  // -- For electrons.
  std::vector<int> *X_lead_electrons = {};
  std::vector<int> *Y_lead_electrons = {};
  std::vector<int> *Z_lead_electrons = {};

  // Set memory.

  // - For scintillator.
  // -- For E and SL.
  tree->SetBranchAddress("X_step_scintillator", &X_scintillator_step);
  tree->SetBranchAddress("Y_step_scintillator", &Y_scintillator_step);
  tree->SetBranchAddress("Z_step_scintillator", &Z_scintillator_step);
  tree->SetBranchAddress("c_step_scintillator", &c_scintillator_step);
  tree->SetBranchAddress("r_step_scintillator", &r_scintillator_step);
  tree->SetBranchAddress("E_step_scintillator", &E_scintillator);
  tree->SetBranchAddress("SL_step_scintillator", &SL_scintillator);
  // -- For photons.
  tree->SetBranchAddress("X_photons_scintillator", &X_scintillator_photons);
  tree->SetBranchAddress("Y_photons_scintillator", &Y_scintillator_photons);
  tree->SetBranchAddress("Z_photons_scintillator", &Z_scintillator_photons);
  tree->SetBranchAddress("c_photons_scintillator", &c_scintillator_photons);
  tree->SetBranchAddress("r_photons_scintillator", &r_scintillator_photons);
  // -- For electrons.
  tree->SetBranchAddress("X_electrons_scintillator", &X_scintillator_electrons);
  tree->SetBranchAddress("Y_electrons_scintillator", &Y_scintillator_electrons);
  tree->SetBranchAddress("Z_electrons_scintillator", &Z_scintillator_electrons);
  tree->SetBranchAddress("c_electrons_scintillator", &c_scintillator_electrons);
  tree->SetBranchAddress("r_electrons_scintillator", &r_scintillator_electrons);

  // - For lead.
  // -- For E and SL.
  tree->SetBranchAddress("X_step_lead", &X_lead_step);
  tree->SetBranchAddress("Y_step_lead", &Y_lead_step);
  tree->SetBranchAddress("Z_step_lead", &Z_lead_step);
  tree->SetBranchAddress("E_step_lead", &E_lead);
  tree->SetBranchAddress("SL_step_lead", &SL_lead);
  // -- For photons.
  tree->SetBranchAddress("X_photons_lead", &X_lead_photons);
  tree->SetBranchAddress("Y_photons_lead", &Y_lead_photons);
  tree->SetBranchAddress("Z_photons_lead", &Z_lead_photons);
  // -- For electrons.
  tree->SetBranchAddress("X_electrons_lead", &X_lead_electrons);
  tree->SetBranchAddress("Y_electrons_lead", &Y_lead_electrons);
  tree->SetBranchAddress("Z_electrons_lead", &Z_lead_electrons);

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  // Fill matrix.
  for (int i = 0; i < nentries; i++) {
    printf(
      "[%.2f] Getting the hole data.\r", (i + 1.0)/nentries*100
    );

    nbytes = tree->GetEntry(i);

    // Create the vector to store the acumulative value of the variable.
    std::vector<float> scintillator_E_values(14472, 0.0);
    std::vector<float> scintillator_SL_values(14472, 0.0);
    std::vector<int> scintillator_photons_values(14472, 0);
    std::vector<int> scintillator_electrons_values(14472, 0);

    std::vector<float> lead_E_values(1584, 0.0);
    std::vector<float> lead_SL_values(1584, 0.0);
    std::vector<int> lead_photons_values(1584, 0);
    std::vector<int> lead_electrons_values(1584, 0);

    for (size_t j = 0; j < X_scintillator_step->size(); j++) {

      int coord =
      (X_scintillator_step->at(j)*3 + c_scintillator_step->at(j))*4*3*67 +
      (Y_scintillator_step->at(j)*3 + r_scintillator_step->at(j))*67 +
      Z_scintillator_step->at(j);

      scintillator_E_values[coord] += E_scintillator->at(i);
      scintillator_SL_values[coord] += SL_scintillator->at(i);

    }

    for (size_t j = 0; j < X_scintillator_photons->size(); j++) {

      int coord =
      (X_scintillator_photons->at(j)*3 + c_scintillator_photons->at(j))*4*3*67 +
      (Y_scintillator_photons->at(j)*3 + r_scintillator_photons->at(j))*67 +
      Z_scintillator_photons->at(j);

      scintillator_photons_values[coord] += 1;

    }

    for (size_t j = 0; j < X_scintillator_electrons->size(); j++) {

      int coord =
      (X_scintillator_electrons->at(j)*3 + c_scintillator_electrons->at(j))*4*3*67 +
      (Y_scintillator_electrons->at(j)*3 + r_scintillator_electrons->at(j))*67 +
      Z_scintillator_electrons->at(j);

      scintillator_electrons_values[coord] += 1;

    }

    for (size_t j = 0; j < X_lead_step->size(); j++) {

      int coord =
      X_lead_step->at(j)*4*66 +
      Y_lead_step->at(j)*66 +
      Z_lead_step->at(j);

      lead_E_values[coord] += E_lead->at(i);
      lead_SL_values[coord] += SL_lead->at(i);

    }

    for (size_t j = 0; j < X_lead_photons->size(); j++) {

      int coord =
      X_lead_photons->at(j)*4*66 +
      Y_lead_photons->at(j)*66 +
      Z_lead_photons->at(j);

      lead_photons_values[coord] += 1;

    }

    for (size_t j = 0; j < X_lead_electrons->size(); j++) {

      int coord =
      X_lead_electrons->at(j)*4*66 +
      Y_lead_electrons->at(j)*66 +
      Z_lead_electrons->at(j);

      lead_electrons_values[coord] += 1;

    }

    for (size_t j = 0; j < 14472; j++) {
      data["scintillator_E"][j].push_back(
        scintillator_E_values[j]
      );
      data["scintillator_SL"][j].push_back(
        scintillator_SL_values[j]
      );
      data["scintillator_photons"][j].push_back(
        scintillator_photons_values[j]
      );
      data["scintillator_electrons"][j].push_back(
        scintillator_electrons_values[j]
      );
    }

    for (size_t j = 0; j < 1584; j++) {
      data["lead_E"][j].push_back(
        lead_E_values[j]
      );
      data["lead_SL"][j].push_back(
        lead_SL_values[j]
      );
      data["lead_photons"][j].push_back(
        lead_photons_values[j]
      );
      data["lead_electrons"][j].push_back(
        lead_electrons_values[j]
      );
    }

  }

  std::cout << "\n-- Info: All data got from the detector."
  << '\n';

  // Reset the branch memory for new tasks.
  tree->ResetBranchAddresses();

  return data;

}

//**********************************************************//
// Get the the data vector of the variable given.           //
// If variable is a particle between photons and electrons, //
// it will give a data vector of particle production in     //
// scintillator.                                            //
//**********************************************************//
std::vector< std::vector<double> > get_matrix_data_scintillator(
  TTree *tree,
  TString variable
) {
  // Create the data vector.
  std::vector< std::vector<double> > data(14472);

  // Initialize data variables.
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

  // Fill matrix.
  for (int i = 0; i < nentries; i++) {
    printf(
      "[%.2f] Getting data from the scintillator.\r", (i + 1.0)/nentries*100
    );

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

  std::cout << "\n-- Info: " << variable << " data got from scintillator."
  << '\n';

  // Reset the branch memory for new tasks.
  tree->ResetBranchAddresses();

  return data;

}

//**********************************************************//
// Get the the data vector of the variable given.           //
// If variable is a particle between photons and electrons, //
// it will give a data vector of particle production in     //
// lead.                                                    //
//**********************************************************//
std::vector< std::vector<double> > get_matrix_data_lead(
  TTree *tree,
  TString variable
) {
  // Create the data vector.
  std::vector< std::vector<double> > data(1584);

  // Initialize data variables.
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

  // Fill matrix.
  for (int i = 0; i < nentries; i++) {
    printf("[%.2f] Getting data from the lead.\r", (i + 1.0)/nentries*100);

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

  std::cout << "\n-- Info: " << variable << " data got from lead." << '\n';

  // Reset the branch memory for new tasks.
  tree->ResetBranchAddresses();

  return data;

}

//
// get_data.cpp ends here.
//
