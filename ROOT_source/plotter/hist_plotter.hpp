#ifndef HIST_PLOTTER
#define HIST_PLOTTER

// C++ includes.
#include <iostream>
#include <vector>
#include <string>

// ROOT includes.
#include "TCanvas.h"
#include "TString.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"

void plot_counter(
  TTree *tree, const char *output_label,
  TString variable, TString material
);

#endif // HIST_PLOTTER
