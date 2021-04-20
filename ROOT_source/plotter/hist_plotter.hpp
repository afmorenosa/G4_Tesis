#ifndef HIST_PLOTTER
#define HIST_PLOTTER

// C++ includes.
#include <vector>
#include <string>

// ROOT includes.
#include "TCanvas.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"

void plot_histograms(TTree *tree, const char *output_label);

#endif // HIST_PLOTTER
