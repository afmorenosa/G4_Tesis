#include "hist_plotter.hpp"

// ***********************************************//
// Plot the histograms for an especific variable. //
//************************************************//
void plot_histograms(TTree *tree, const char *output_label) {

  // Initialize variables.
  Int_t primary = -1;
  std::vector<int> *X = {};
  std::vector<int> *Y = {};
  std::vector<int> *Z = {};
  std::vector<int> *r = {};
  std::vector<int> *c = {};

  tree->SetBranchAddress("primary", &primary);
  tree->SetBranchAddress("X_photons_scintillator", &X);
  tree->SetBranchAddress("Y_photons_scintillator", &Y);
  tree->SetBranchAddress("Z_photons_scintillator", &Z);
  tree->SetBranchAddress("r_photons_scintillator", &r);
  tree->SetBranchAddress("c_photons_scintillator", &c);

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
    6*3, 0, 6*3, 4*3, 0, 4*3
  );

  TH3I *calo_photons_counter_3 = new TH3I(
    "Photons Counter",
    "Photons",
    6*3, 0, 6*3, 4*3, 0, 4*3, 67, 0, 67
  );

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  // Fill histograms.
  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    particle_counter->Fill(primary);

    for (size_t j = 0; j < X->size(); j++) {

      calo_photons_counter->Fill(
        3 * X->at(j) + c->at(j), 3 * Y->at(j) + r->at(j)
      );
      calo_photons_counter_3->Fill(
        3 * X->at(j) + c->at(j), 3 * Y->at(j) + r->at(j), Z->at(j)
      );

    }

  }

  // Save histograms.
  std::string output_file;

  particle_counter->Draw();
  output_file =
  std::string(output_label) + "particles.root";

  canvas->Print(output_file.c_str());
  canvas->Clear();


  calo_photons_counter->Draw("COL");
  output_file =
  std::string(output_label) + "calo_photons_counter.root";

  canvas->Print(output_file.c_str());
  canvas->Clear();


  calo_photons_counter_3->Draw("BOX");
  output_file =
  std::string(output_label) + "calo_photons_counter_3.root";

  canvas->Print(output_file.c_str());
  canvas->Clear();

}

//
// hist_plotter.cpp ends here.
//
