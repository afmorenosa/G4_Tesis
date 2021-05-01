#ifndef DATA_TEST
#define DATA_TEST

// C++ includes.
#include <vector>

// ROOT includes.
#include "TString.h"
#include "TMath.h"
#include "TTree.h"
#include "TH1.h"

// Project includes.
#include "get_data.hpp"
#include "results.hpp"

std::vector<Double_t> kolmogorov_test (
  std::vector< std::vector<double> > data_a,
  std::vector< std::vector<double> > data_b
);

void kolmogorov_test_counter (
  TTree *tree_a,
  TTree *tree_b,
  TString particle,
  TString material,
  TString label
);

void kolmogorov_test_energy (
  TTree *tree_a,
  TTree *tree_b,
  TString material,
  TString label
);

void kolmogorov_test_step_lenght (
  TTree *tree_a,
  TTree *tree_b,
  TString material,
  TString label
);

#endif // DATA_TEST
