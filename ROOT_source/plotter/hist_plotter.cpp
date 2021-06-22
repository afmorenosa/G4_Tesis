#include "hist_plotter.hpp"

// ***********************************************//
// Plot the histograms for an especific variable. //
//************************************************//
void plot_counter(
  TTree *tree, const char *output_label,
  TString variable, TString material
) {

  // Initialize variables.
  Int_t primary = -1;
  std::vector<int> *X = {};
  std::vector<int> *Y = {};
  std::vector<int> *Z = {};
  std::vector<int> *r = {};
  std::vector<int> *c = {};

  tree->SetBranchAddress("primary", &primary);
  tree->SetBranchAddress("X_" + variable + "_" + material, &X);
  tree->SetBranchAddress("Y_" + variable + "_" + material, &Y);
  tree->SetBranchAddress("Z_" + variable + "_" + material, &Z);
  if (material.EqualTo("scintillator")) {
    tree->SetBranchAddress("r_" + variable + "_" + material, &r);
    tree->SetBranchAddress("c_" + variable + "_" + material, &c);
  }

  // Create the canvas to plot the histograms
  TCanvas *canvas = new TCanvas(
    "Canvas",
    "ECAL",
    800,
    600
  );

  // Create histograms.
  TH1I *particle_counter = new TH1I(
    "Primary particle",
    "Primary",
    5, -1, 4
  );

  TH2I *calo_photons_counter = new TH2I(
    variable + " counter 2D",
    variable,
    6*3, 0, 6*3, 4*3, 0, 4*3
  );

  TH3I *calo_photons_counter_3 = new TH3I(
    variable + " counter 3D",
    variable,
    6*3, 0, 6*3, 4*3, 0, 4*3, 67, 0, 67
  );

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  // Fill histograms.
  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    particle_counter->Fill(primary);

    for (size_t j = 0; j < X->size(); j++) {

      if (material.EqualTo("scintillator")) {

        calo_photons_counter->Fill(
          3 * X->at(j) + c->at(j), 3 * Y->at(j) + r->at(j)
        );
        calo_photons_counter_3->Fill(
          3 * X->at(j) + c->at(j), 3 * Y->at(j) + r->at(j), Z->at(j)
        );

      } else {

        calo_photons_counter->Fill(
          X->at(j), Y->at(j)
        );
        calo_photons_counter_3->Fill(
          X->at(j), Y->at(j), Z->at(j)
        );

      }

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
