#include <filesystem>
#include <iostream>
#include <vector>
#include <string>

#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"

namespace fs = std::filesystem;

void print_histograms(char *input_dir, char *output_path);

int main(int argc, char *argv[]) {

  print_histograms(argv[1], argv[2]);

  return 0;
}

void print_histograms(char *input_file, char *output_path) {

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
