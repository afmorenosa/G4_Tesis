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
  std::vector<int> *X_step = {};
  std::vector<int> *Y_step = {};
  std::vector<int> *Z_step = {};
  std::vector<int> *r_step = {};
  std::vector<int> *c_step = {};
  std::vector<float> *E = {};
  std::vector<float> *SL = {};

  tree->SetBranchAddress("primary", &primary);
  tree->SetBranchAddress("X_" + variable + "_" + material, &X);
  tree->SetBranchAddress("Y_" + variable + "_" + material, &Y);
  tree->SetBranchAddress("Z_" + variable + "_" + material, &Z);
  tree->SetBranchAddress("X_step_" + material, &X_step);
  tree->SetBranchAddress("Y_step_" + material, &Y_step);
  tree->SetBranchAddress("Z_step_" + material, &Z_step);
  tree->SetBranchAddress("E_step_" + material, &E);
  tree->SetBranchAddress("SL_step_" + material, &SL);
  if (material.EqualTo("scintillator")) {
    tree->SetBranchAddress("r_" + variable + "_" + material, &r);
    tree->SetBranchAddress("c_" + variable + "_" + material, &c);
    tree->SetBranchAddress("r_step_" + material, &r_step);
    tree->SetBranchAddress("c_step_" + material, &c_step);
  }

  // Create the canvas to plot the histograms
  TCanvas *canvas = new TCanvas(
    "Canvas",
    "ECAL",
    800,
    600
  );

  canvas->SetRightMargin(0.15);
  canvas->SetLeftMargin(0.09);
  canvas->SetBottomMargin(0.15);

  // Create histograms.
  TH1I *particle_counter = new TH1I(
    "Primary particle",
    "Primary; Particle; Number of Events",
    5, -1, 4
  );

  TH1F *step_lengt_hist = new TH1F(
    "Step Lenght",
    "Step Lenght; Step Lenght [mm]; Number of Events",
    100, 0, 60
  );

  TH1F *energy_hist = new TH1F(
    "Energy deposit",
    "Energy deposit; Energy [MeV]; Number of Events",
    100, 0, 5
  );

  TH1F *step_lengt_hist_significative = new TH1F(
    "Step Lenght (Significative Cell)",
    "Step Lenght; Step Lenght [mm]; Number of Events",
    100, 0, 60
  );

  TH1F *energy_hist_significative = new TH1F(
    "Energy deposit (Significative Cell)",
    "Energy deposit; Energy [MeV]; Number of Events",
    100, 0, 5
  );

  TH1F *step_lengt_hist_not_significative = new TH1F(
    "Step Lenght (Not Significative Cell)",
    "Step Lenght; Step Lenght [mm]; Number of Events",
    100, 0, 60
  );

  TH1F *energy_hist_not_significative = new TH1F(
    "Energy deposit (Not Significative Cell)",
    "Energy deposit; Energy [MeV]; Number of Events",
    100, 0, 5
  );

  int x_dim, y_dim, z_dim;

  if (material.EqualTo("scintillator")) {
    x_dim = 6*3;
    y_dim = 4*3;
    z_dim = 67;
  } else {
    x_dim = 6;
    y_dim = 4;
    z_dim = 66;
  }

  TH2I *calo_photons_counter = new TH2I(
    variable + " counter 2D",
    variable + "; X; Y; Number of Events",
    x_dim, 0, x_dim, y_dim, 0, y_dim
  );

  TH1I *calo_photons_counter_Z = new TH1I(
    variable + " counter Z axis",
    variable + "; Z; Number of Events",
    z_dim, 0, z_dim
  );

  TH1I *calo_photons_counter_significative = new TH1I(
    variable + " counter (Significative Cell)",
    variable + "; Number of photons; Number of Events",
    10, 0, 10
  );

  TH1I *calo_photons_counter_not_significative = new TH1I(
    variable + " counter (Not Significative Cell)",
    variable + "; Number of photons; Number of Events",
    10, 0, 10
  );

  TH3I *calo_photons_counter_3 = new TH3I(
    variable + " counter 3D",
    variable + "; X; Y; Z; Number of Events",
    x_dim, 0, x_dim, y_dim, 0, y_dim, z_dim, 0, z_dim
  );

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  int evt_counter = 0;

  // Fill histograms.
  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    particle_counter->Fill(primary);


    for (size_t j = 0; j < X_step->size(); j++) {

      energy_hist->Fill(E->at(j));
      step_lengt_hist->Fill(SL->at(j));

    }

    int significative_count = 0;
    int not_significative_count = 0;

    for (size_t j = 0; j < X->size(); j++) {

      calo_photons_counter_Z->Fill(
        Z->at(j)
      );

      if (material.EqualTo("scintillator")) {

        calo_photons_counter->Fill(
          3 * X->at(j) + c->at(j), 3 * Y->at(j) + r->at(j)
        );


        calo_photons_counter_3->Fill(
          3 * X->at(j) + c->at(j), 3 * Y->at(j) + r->at(j), Z->at(j)
        );

        if (
          3 * X->at(j) + c->at(j) == 8 &&
          3 * Y->at(j) + r->at(j) == 10 &&
          Z->at(j) == 41
        ) {
          significative_count++;
        } else if  (
          3 * X->at(j) + c->at(j) == 0 &&
          3 * Y->at(j) + r->at(j) == 9 &&
          Z->at(j) == 20
        ) {
          not_significative_count++;
        }

      } else {

        calo_photons_counter->Fill(
          X->at(j), Y->at(j)
        );

        calo_photons_counter_3->Fill(
          X->at(j), Y->at(j), Z->at(j)
        );

        if (
          3 * X->at(j) == 3 &&
          3 * Y->at(j) == 0 &&
          Z->at(j) == 47
        ) {
          significative_count++;
        } else if  (
          3 * X->at(j) == 0 &&
          3 * Y->at(j) == 2 &&
          Z->at(j) == 21
        ) {
          not_significative_count++;
        }

      }

    }

    calo_photons_counter_significative->Fill(significative_count);
    calo_photons_counter_not_significative->Fill(not_significative_count);

    evt_counter += X->size();
    std::cout <<
    "Events: " << X->size() << '\t' <<
    "Variable: " << variable << '\t' <<
    "Material: " << material <<
    '\n';

  }

  std::cout <<
  "Events_avg: " << 1. * evt_counter/ nentries<< '\t' <<
  "Variable: " << variable << '\t' <<
  "Material: " << material <<
  '\n';

  // Save histograms.
  std::string output_file;

  particle_counter->SetFillColor(kYellow);
  particle_counter->Draw();
  output_file =
  std::string(output_label) + "_particles.pdf";

  canvas->Print(output_file.c_str());
  canvas->Clear();

  // calo_photons_counter->SetStats(kFALSE);
  calo_photons_counter->Draw("COLZ");
  output_file =
  std::string(output_label) + "_calo_counter.pdf";

  canvas->Print(output_file.c_str());
  canvas->Clear();

  calo_photons_counter_3->Draw("BOX");
  output_file =
  std::string(output_label) + "_calo_counter_3.pdf";

  canvas->Print(output_file.c_str());
  canvas->Clear();


  canvas->SetLogy();

  calo_photons_counter_Z->SetFillColor(kYellow);
  calo_photons_counter_Z->Draw();
  output_file =
  std::string(output_label) + "_calo_counter_Z.pdf";

  canvas->Print(output_file.c_str());
  canvas->Clear();

  calo_photons_counter_significative->SetFillColor(kYellow);
  calo_photons_counter_significative->Draw();
  output_file =
  std::string(output_label) + "_significative_hist.pdf";

  canvas->Print(output_file.c_str());
  canvas->Clear();

  calo_photons_counter_not_significative->SetFillColor(kYellow);
  calo_photons_counter_not_significative->Draw();
  output_file =
  std::string(output_label) + "_not_significative_hist.pdf";

  canvas->Print(output_file.c_str());
  canvas->Clear();

  step_lengt_hist->SetFillColor(kYellow);
  step_lengt_hist->Draw();
  output_file =
  std::string(output_label) + "_step_lengt_hist.pdf";

  canvas->Print(output_file.c_str());
  canvas->Clear();

  energy_hist->SetFillColor(kYellow);
  energy_hist->Draw();
  output_file =
  std::string(output_label) + "_energy_hist.pdf";

  canvas->Print(output_file.c_str());
  canvas->Clear();

}

//
// hist_plotter.cpp ends here.
//
