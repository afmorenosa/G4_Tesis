#ifndef SIGNIFICATIVE_CELLS
#define SIGNIFICATIVE_CELLS

// C++ includes.
#include <vector>
#include <string>
#include <map>

// ROOT includes.
#include "TString.h"

// Project includes.
#include "results.hpp"
#include "test.hpp"

std::vector<TString> get_significative_cells(
  std::vector<TTree *>trees,
  TString label,
  bool save=true,
  Double_t threshold=0.5
);

#endif // SIGNIFICATIVE_CELLS
