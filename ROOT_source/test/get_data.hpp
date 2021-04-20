#ifndef GET_DATA
#define GET_DATA

// C++ includes.
#include <vector>
#include <iostream>

// ROOT includes.
#include "TString.h"
#include "TTree.h"

std::vector< std::vector<double> > get_matrix_data_scintillator(
  TTree *tree,
  TString variable
);

std::vector< std::vector<double> > get_matrix_data_lead(
  TTree *tree,
  TString variable
);

#endif // GET_DATA
