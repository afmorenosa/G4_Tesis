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
#include "test.hpp"

int main(int argc, char *argv[]) {

  std::map<const char *, const char *> arguments = parse_args(argc, argv);

  if (arguments.find("error") != arguments.end()) {
    std::cerr << arguments["error"]
    << "Use -h, --help for more information\n" << '\n';
    return 1;
  } else if (arguments.find("help") != arguments.end()) {
    print_usage();
    return 0;
  }

  if (arguments.find("histos_file") != arguments.end()) {
    // Open de Root File
    TFile *file = TFile::Open(arguments["histos_file"]);

    // Get the directory of the ntuples.
    TDirectory *dir_ntup = file->GetDirectory("ntuple");

    // Get the Tree from the Root File
    TTree *tree = (TTree*) dir_ntup->Get("Photons");
    tree->Print();

    plot_counter(tree, arguments["label"],
    arguments["variable"], arguments["material"]);
  }

  if (arguments.find("test_file_1") != arguments.end()) {
    // Open de Root File
    TFile *file_1 = TFile::Open(arguments["test_file_1"]);
    TFile *file_2 = TFile::Open(arguments["test_file_2"]);

    // Get the directory of the ntuples.
    TDirectory *dir_ntup_1 = file_1->GetDirectory("ntuple");
    TDirectory *dir_ntup_2 = file_2->GetDirectory("ntuple");

    // Get the Tree from the Root File
    TTree *tree_1 = (TTree*) dir_ntup_1->Get("Photons");
    TTree *tree_2 = (TTree*) dir_ntup_2->Get("Photons");

    std::vector<Double_t> test_result;

    if (arguments["variable"] == std::string("E")) {

      test_result = kolmogorov_test_energy(
        tree_1, tree_2, arguments["material"],
        arguments["label"]
      );

    } else if (arguments["variable"] == std::string("SL")) {

      test_result = kolmogorov_test_step_lenght(
        tree_1, tree_2, arguments["material"],
        arguments["label"]
      );

    } else if (arguments["variable"] == std::string("electrons") ||
    arguments["variable"] == std::string("photons")) {

      test_result = kolmogorov_test_counter(
        tree_1, tree_2, arguments["variable"], arguments["material"],
        arguments["label"]
      );

    }

    for (size_t i = 0; i < test_result.size(); i++) {

      if (test_result[i] != -1500) {
        std::cout << test_result[i] << '\t';
      }

    }
    std::cout << '\n';

  }


  return 0;
}
