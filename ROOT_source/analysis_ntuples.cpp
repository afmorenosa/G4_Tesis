// C++ includes.
#include <iostream>
#include <map>

// ROOT includes.
#include "TDirectory.h"
#include "TTree.h"
#include "TFile.h"

// Project includes.
#include "significative_cells.hpp"
#include "hist_plotter.hpp"
#include "args_manager.hpp"
#include "test.hpp"

int main(int argc, char *argv[]) {

  std::map<std::string, const char *> arguments = parse_args(argc, argv);

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
    // tree->Print();

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

    if (arguments["variable"] == std::string("E")) {

      kolmogorov_test_energy(
        tree_1, tree_2, arguments["material"],
        arguments["label"]
      );

    } else if (arguments["variable"] == std::string("SL")) {

      kolmogorov_test_step_lenght(
        tree_1, tree_2, arguments["material"],
        arguments["label"]
      );

    } else if (arguments["variable"] == std::string("electrons") ||
    arguments["variable"] == std::string("photons")) {

      kolmogorov_test_counter(
        tree_1, tree_2, arguments["variable"], arguments["material"],
        arguments["label"]
      );

    }

  }

  if (arguments.find("scell_file_1") != arguments.end()) {
    std::vector<TFile *> files;
    std::vector<TTree *> trees;

    int file_number = std::atoi(arguments["scell_n_files"]);

    for (int file_index = 1; file_index < file_number; file_index++) {
      std::string key_string =
      std::string("scell_file_") +
      std::to_string(file_index);

      // Open de Root File
      files.push_back(TFile::Open(arguments[key_string]));

      // Get the directory of the ntuples.
      TDirectory *dir_ntup = files[files.size() - 1]->GetDirectory("ntuple");

      // Get the Tree from the Root File
      trees.push_back( (TTree*) dir_ntup->Get("Photons") );

    }
    get_significative_cells(trees, arguments["label"]);

  }


  return 0;
}
