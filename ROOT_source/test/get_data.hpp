#ifndef GET_DATA
#define GET_DATA

// C++ includes.
#include <iostream>
#include <map>

// ROOT includes.
#include "TString.h"
#include "TTree.h"

std::map< TString, std::vector< std::vector<double> > > get_complete_matrix_data(
  TTree *tree, TString material
);

std::vector< std::vector<double> > get_matrix_data_scintillator(
  TTree *tree,
  TString variable
);

std::vector< std::vector<double> > get_matrix_data_lead(
  TTree *tree,
  TString variable
);

#endif // GET_DATA
