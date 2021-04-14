#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <map>

#include "TDirectory.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"

namespace fs = std::filesystem;

void print_usage() {
  std::cerr << std::endl;
  std::cerr << " Usage: " << std::endl;
  std::cerr << " plot_histo <input_root_file> [-l label]" << std::endl;
  std::cerr << std::endl;
  std::cerr << "   Options:" << std::endl;
  std::cerr << "-l, --label output_label\t Set a label for the output files. "
  << "If none if given,\n the inputfile name will be used as label."
  << std::endl;
  std::cerr << "      -h, --help\t Print the usage." << std::endl;
  std::cerr << std::endl;
}

std::map<const char *, const char *> parse_args(int argc, char *argv[]);
void print_histograms(const char *input_dir, const char *output_path);

int main(int argc, char *argv[]) {

  std::map<const char *, const char *> arguments = parse_args(argc, argv);

  if (arguments.find("error") != arguments.end()) {
    std::cerr << arguments["error"] << '\n';
    return 1;
  } else if (arguments.find("help") != arguments.end()) {
    print_usage();
    return 0;
  }

  print_histograms(arguments["file"], arguments["label"]);

  return 0;
}

std::map<const char *, const char *> parse_args(int argc, char *argv[]) {

  std::map<const char *, const char *> arguments;

  for (int i = 1; i < argc; i++) {
    if (
      std::regex_match(argv[i], std::regex("-h")) ||
      std::regex_match(argv[i], std::regex("--help"))
    ) {

      arguments["help"] = "";
      return arguments;

    } else if (
      std::regex_match(argv[i], std::regex("^-l(=.+)?")) ||
      std::regex_match(argv[i], std::regex("^--label(=.+)?"))
    ) {

      if (arguments.find("label") != arguments.end()) {
        arguments["error"] = "\nError: Label already given.\n";
        return arguments;
      }

      if (TString(argv[i]).Contains("=")) {
        size_t pos_eq = std::string(argv[i]).find('=');

        arguments["label"] = std::string(argv[i]).substr(pos_eq + 1).c_str();

      } else {

        if ( i+1 >= argc || std::regex_match(argv[i+1], std::regex("^-.+")) ) {
          arguments["error"] = "\nError: No valid label given.\n";
          return arguments;
        }

        arguments["label"] = argv[i + 1];
        i++;
      }

    } else {

      if (arguments.find("file") != arguments.end()) {
        arguments["error"] = "\nError: Multiple input files given, just one "
        "shuld be given.\n";
        return arguments;
      }

      arguments["file"] = argv[i];

    }
  }

  if (arguments.find("file") == arguments.end()) {
    arguments["error"] = "\nError: No input file given.\n";
    return arguments;
  }

  if (arguments.find("label") == arguments.end()) {
    arguments["label"] = arguments["label"];
  }

  return arguments;

}

void print_histograms(const char *input_file, const char *output_path) {

  // Open de Root File
  TFile *file = TFile::Open(input_file);

  // Get the directory of the ntuples.
  TDirectory *dir_ntup = file->GetDirectory("ntuple");

  // Get the Tree from the Root File
  TTree *tree = (TTree*) dir_ntup->Get("Photons");
  tree->Print();

  // Initialize variables.
  Int_t primary = -1;
  std::vector<int> *X = {};
  std::vector<int> *Y = {};
  std::vector<int> *Z = {};
  std::vector<int> *r = {};
  std::vector<int> *c = {};

  tree->SetBranchAddress("primary", &primary);
  tree->SetBranchAddress("X", &X);
  tree->SetBranchAddress("Y", &Y);
  tree->SetBranchAddress("Z", &Z);
  tree->SetBranchAddress("r", &r);
  tree->SetBranchAddress("c", &c);

  // Create the canvas to plot the histograms
  TCanvas *canvas = new TCanvas(
    "Canvas",
    "ECAL",
    800,
    600
  );

  // Create histograms.
  TH1I *particle_counter = new TH1I(
    "Primary poarticle",
    "Primary",
    5, -1, 4
  );

  TH2I *calo_photons_counter = new TH2I(
    "Photons Counter",
    "Photons",
    6, 0, 6, 4, 0, 4
  );

  TH3I *calo_photons_counter_3 = new TH3I(
    "Photons Counter",
    "Photons",
    6, 0, 6, 4, 0, 4, 67, 0, 67
  );

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  // Fill histograms.
  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    particle_counter->Fill(primary);

    for (size_t j = 0; j < X->size(); j++) {

      calo_photons_counter->Fill(X->at(j), Y->at(j));
      calo_photons_counter_3->Fill(X->at(j), Y->at(j), Z->at(j));

    }

  }

  // Save histograms.
  std::string output_file;

  particle_counter->Draw();
  output_file =
  std::string(output_path) + "particles.root";

  canvas->Print(output_file.c_str());
  canvas->Clear();


  calo_photons_counter->Draw("COL");
  output_file =
  std::string(output_path) + "calo_photons_counter.root";

  canvas->Print(output_file.c_str());
  canvas->Clear();


  calo_photons_counter_3->Draw("BOX");
  output_file =
  std::string(output_path) + "calo_photons_counter_3.root";

  canvas->Print(output_file.c_str());
  canvas->Clear();

}
