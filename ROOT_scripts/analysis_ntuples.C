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

  Int_t X = -1;
  Int_t Y = -1;
  Int_t Z = -1;
  Int_t r = -1;
  Int_t c = -1;

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

  TH2I *calo_photons_counter = new TH2I(
    "Photons Counter",
    "Photons",
    32, 0, 17, 24, 0, 13
  );

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    calo_photons_counter->Fill(X, Y);

  }

  calo_photons_counter->Draw("COL");
  canvas->Print("calo_photons_counter.svg");
  canvas->Clear();
}
