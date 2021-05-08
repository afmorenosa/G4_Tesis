#ifndef RESULTS
#define RESULTS

// C++ includes
#include <fstream>
#include <vector>

// ROOT includes.
#include "TString.h"

void save_scintillator_values (std::vector<Double_t> data, TString output_file);
void save_lead_values (std::vector<Double_t> data, TString output_file);

void save_significative_cells (std::vector<TString> data, TString output_file);

#endif // RESULTS
