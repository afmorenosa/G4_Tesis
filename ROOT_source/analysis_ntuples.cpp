// C++ includes.
#include <iostream>
#include <map>

// ROOT includes.
#include "TDirectory.h"
#include "TTree.h"
#include "TFile.h"

// Project includes.
#include "hist_plotter.hpp"
#include "args_manager.hpp"

int main(int argc, char *argv[]) {

  std::map<const char *, const char *> arguments = parse_args(argc, argv);

  if (arguments.find("error") != arguments.end()) {
    std::cerr << arguments["error"]
    << "Use -h, --help for more information" << '\n';
    return 1;
  } else if (arguments.find("help") != arguments.end()) {
    print_usage();
    return 0;
  }

  // Open de Root File
  TFile *file = TFile::Open(arguments["file"]);

  // Get the directory of the ntuples.
  TDirectory *dir_ntup = file->GetDirectory("ntuple");

  // Get the Tree from the Root File
  TTree *tree = (TTree*) dir_ntup->Get("Photons");
  tree->Print();

  plot_histograms(tree, arguments["label"]);

  return 0;
}
