#include "get_data.hpp"

//**********************************************************//
// Get the the data vector of the matieral given.           //
//**********************************************************//
std::map< TString, std::vector< std::vector<double> > > get_complete_matrix_data(
  TTree *tree, TString material
) {
  // Create the map for data vectors.
  std::map< TString, std::vector< std::vector<double> > > data;

  // Set the maximun values of the coordinates for each material.
  std::map<TString, Int_t> x_max = {
    {"scintillator", 3*6},
    {"lead", 6}
  };
  std::map<TString, Int_t> y_max = {
    {"scintillator", 3*4},
    {"lead", 4}
  };
  std::map<TString, Int_t> z_max = {
    {"scintillator", 67},
    {"lead", 66}
  };

  int n_cells = x_max[material] + y_max[material] * z_max[material];

  // Create the data vectors
  data["E"] = std::vector< std::vector<double> >(n_cells);
  data["SL"] = std::vector< std::vector<double> >(n_cells);
  data["photons"] = std::vector< std::vector<double> >(n_cells);
  data["electrons"] = std::vector< std::vector<double> >(n_cells);

  // Initialize data variables.

  // -- For E and S.
  std::vector<int> *X_step = {};
  std::vector<int> *Y_step = {};
  std::vector<int> *Z_step = {};
  std::vector<int> *c_step = {};
  std::vector<int> *r_step = {};
  std::vector<float> *E_vec = {};
  std::vector<float> *SL_vec = {};
  // -- For photons.
  std::vector<int> *X_photons = {};
  std::vector<int> *Y_photons = {};
  std::vector<int> *Z_photons = {};
  std::vector<int> *c_photons = {};
  std::vector<int> *r_photons = {};
  // -- For electrons.
  std::vector<int> *X_electrons = {};
  std::vector<int> *Y_electrons = {};
  std::vector<int> *Z_electrons = {};
  std::vector<int> *c_electrons = {};
  std::vector<int> *r_electrons = {};

  // Set memory.

  // -- For E and SL.
  tree->SetBranchAddress("X_step_" + material, &X_step);
  tree->SetBranchAddress("Y_step_" + material, &Y_step);
  tree->SetBranchAddress("Z_step_" + material, &Z_step);
  if (material.EqualTo("scintillator")){
    tree->SetBranchAddress("c_step_" + material, &c_step);
    tree->SetBranchAddress("r_step_" + material, &r_step);
  }
  tree->SetBranchAddress("E_step_" + material, &E_vec);
  tree->SetBranchAddress("SL_step_" + material, &SL_vec);
  // -- For photons.
  tree->SetBranchAddress("X_photons_" + material, &X_photons);
  tree->SetBranchAddress("Y_photons_" + material, &Y_photons);
  tree->SetBranchAddress("Z_photons_" + material, &Z_photons);
  if (material.EqualTo("scintillator")){
    tree->SetBranchAddress("c_photons_" + material, &c_photons);
    tree->SetBranchAddress("r_photons_" + material, &r_photons);
  }
  // -- For electrons.
  tree->SetBranchAddress("X_electrons_" + material, &X_electrons);
  tree->SetBranchAddress("Y_electrons_" + material, &Y_electrons);
  tree->SetBranchAddress("Z_electrons_" + material, &Z_electrons);
  if (material.EqualTo("scintillator")){
    tree->SetBranchAddress("c_electrons_" + material, &c_electrons);
    tree->SetBranchAddress("r_electrons_" + material, &r_electrons);
  }

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  // Fill matrix.
  for (int i = 0; i < nentries; i++) {
    printf(
      "[%.2f] Getting the hole data.\r", (i + 1.0)/nentries*100
    );

    nbytes = tree->GetEntry(i);

    // Create the vector to store the acumulative value of the variable.
    std::vector<float> E_values(n_cells, 0.0);
    std::vector<float> SL_values(n_cells, 0.0);
    std::vector<int> photons_values(n_cells, 0);
    std::vector<int> electrons_values(n_cells, 0);

    for (size_t j = 0; j < X_step->size(); j++) {

      int x, y;

      if (material.EqualTo("scintillator")){
        x = X_step->at(j)*3 + c_step->at(j);
        y = Y_step->at(j)*3 + r_step->at(j);
      } else {
        x = X_step->at(j);
        y = Y_step->at(j);
      }

      int coord =
      x * x_max[material] +
      y * y_max[material] +
      Z_step->at(j);

      E_values[coord] += E_vec->at(i);
      SL_values[coord] += SL_vec->at(i);

    }

    for (size_t j = 0; j < X_photons->size(); j++) {

      int x, y;

      if (material.EqualTo("scintillator")){
        x = X_photons->at(j)*3 + c_photons->at(j);
        y = Y_photons->at(j)*3 + r_photons->at(j);
      } else {
        x = X_photons->at(j);
        y = Y_photons->at(j);
      }

      int coord =
      x * x_max[material] +
      y * y_max[material] +
      Z_photons->at(j);

      photons_values[coord] += 1;

    }

    for (size_t j = 0; j < X_electrons->size(); j++) {

      int x, y;

      if (material.EqualTo("scintillator")){
        x = X_electrons->at(j)*3 + c_electrons->at(j);
        y = Y_electrons->at(j)*3 + r_electrons->at(j);
      } else {
        x = X_electrons->at(j);
        y = Y_electrons->at(j);
      }

      int coord =
      x * x_max[material] +
      y * y_max[material] +
      Z_electrons->at(j);

      electrons_values[coord] += 1;

    }

    for (size_t j = 0; j < n_cells; j++) {
      data["E"][j].push_back(
        E_values[j]
      );
      data["SL"][j].push_back(
        SL_values[j]
      );
      data["photons"][j].push_back(
        photons_values[j]
      );
      data["electrons"][j].push_back(
        electrons_values[j]
      );
    }

  }

  std::cout << "\n-- Info: All data got from the detector."
  << '\n';

  // Reset the branch memory for new tasks.
  tree->ResetBranchAddresses();

  // Free memory.

  // -- For E and S.
  delete X_step;
  delete Y_step;
  delete Z_step;
  delete c_step;
  delete r_step;
  delete E_vec;
  delete SL_vec;
  // -- For photons.
  delete X_photons;
  delete Y_photons;
  delete Z_photons;
  delete c_photons;
  delete r_photons;
  // -- For electrons.
  delete X_electrons;
  delete Y_electrons;
  delete Z_electrons;
  delete c_electrons;
  delete r_electrons;

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
