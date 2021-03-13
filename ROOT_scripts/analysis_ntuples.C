#include <iostream>
#include <string>

void analysis_ntuples() {
  // Open de Root File
  TFile *file = TFile::Open("calo_Ecal.root");

  // Get the directory of the ntuples.
  TDirectory *dir_ntup = file->GetDirectory("ntuple");

  // Get the Tree from the Root File
  TTree *tree = (TTree*) dir_ntup->Get("Photons");
  tree->Print();

  Int_t primary = -1;
  vector<int> *X = {};
  vector<int> *Y = {};
  vector<int> *Z = {};
  vector<int> *r = {};
  vector<int> *c = {};

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

  TH1I *particle_counter = new TH1I(
    "Primary poarticle",
    "Primary",
    5, -1, 5
  );

  TH2I *calo_photons_counter = new TH2I(
    "Photons Counter",
    "Photons",
    32, 0, 17, 24, 0, 13
  );

  TH3I *calo_photons_counter_3 = new TH3I(
    "Photons Counter",
    "Photons",
    32, 0, 17, 24, 0, 13, 67, 0, 67
  );

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    particle_counter->Fill(primary);

    for (size_t j = 0; j < X->size(); j++) {

      calo_photons_counter->Fill(X->at(i), Y->at(i));
      calo_photons_counter_3->Fill(X->at(i), Y->at(i), Z->at(i));
    }

  }

  particle_counter->Draw();
  canvas->Print("particles.svg");
  canvas->Clear();

  calo_photons_counter->Draw("COL");
  canvas->Print("calo_photons_counter.svg");
  canvas->Clear();

  calo_photons_counter_3->Draw("BOX");
  canvas->Print("calo_photons_counter_3.root");
  canvas->Clear();
}
