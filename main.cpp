// Geant 4.
#include "G4UImanager.hh"
// Visual Interface.
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "g4root.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

// Project Libraries.
#include "H4Detector.hpp"
#include "H4Actions.hpp"

namespace {
  void PrintUsage() {
    G4cerr << G4endl;
    G4cerr << " Usage: " << G4endl;
    G4cerr << " exampleB4a [option]" << G4endl;
    G4cerr << G4endl;
    G4cerr << "   Options:" << G4endl;
    G4cerr << "      -h, --help\t Print the usage" << G4endl;
    G4cerr << "      -g, --graphics\t Run with the graphical interface"
    << G4endl;
    G4cerr << "      -m, --macro [macro]\t Run a macro" << G4endl;
    G4cerr << G4endl;
    G4cerr << "Just use one option per run." << G4endl;
    G4cerr << G4endl;

  }
}

int main(int argc, char **argv) {
  // Evaluate arguments
  //
  if (
    argc > 3 || (argc > 2 &&
      (
        G4String(argv[1]) == "-h" || G4String(argv[1]) == "--help" ||
      G4String(argv[1]) == "-g" || G4String(argv[1]) == "--graphics"
    ) )
  ) {

    PrintUsage();
    return 1;

  }

  // Print the usage.
  if ( argc > 1 &&
    (G4String(argv[1]) == "-h" || G4String(argv[1]) == "--help")
  ) {

    PrintUsage();
    return 0;

  }

  // Construct the default run manager.
#ifdef G4MULTITHREADED
  std::cout << "INFO: Multithreaded" << '\n';

  G4MTRunManager *run_manager = new G4MTRunManager;

  G4RootAnalysisManager::Instance();
  // if ( nThreads > 0 ) {

  //   runManager->SetNumberOfThreads(nThreads);
  // }
#else
  G4RunManager *run_manager = new G4RunManager;
#endif

  run_manager->SetVerboseLevel(0);

  //** Set mandatory initialization  classes.
  // Detector Geometry.
  run_manager->SetUserInitialization(new H4Detector);

  // Physics List.
  auto physicsList = new QGSP_BERT;
  run_manager->SetUserInitialization(physicsList);

  // Actions Initialization.
  run_manager->SetUserInitialization(new H4Actions);

  // Initialize Genat 4 kernel.
  run_manager->Initialize();

  // Get the current pointer to the UI manager and set the verbosities.
  G4UImanager *UI = G4UImanager::GetUIpointer();
  UI->ApplyCommand("/run/verbose 1");
  UI->ApplyCommand("/event/verbose 1");
  UI->ApplyCommand("/tracking/verbose 1");

  // Get the pointer to the User Interface manager.
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (argc == 1) {

    // Start a run.
    int number_of_events = 5;
    run_manager->BeamOn(number_of_events);

  } else if (G4String(argv[1]) == "-g" || G4String(argv[1]) == "--graphics") {

    // Initialize vis manager for vis commands.
    G4VisManager* vis_manager = new G4VisExecutive;
    vis_manager->Initialize();
    // interactive mode : define UI session.
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    UImanager->ApplyCommand("/control/execute G4Macros/init_vis.mac");
    ui->SessionStart();
    delete ui;

  } else if (G4String(argv[1]) == "-m" || G4String(argv[1]) == "--macro") {

    if (argc < 3) {

      G4cerr << G4endl;
      G4cerr << "Error: please give the path to a macro file" << G4endl;

      PrintUsage();
      return 1;

    }

    // batch mode.
    G4String command = "/control/execute ";
    G4String fileName = argv[2];
    UImanager->ApplyCommand(command+fileName);

  } else {

    G4cerr << G4endl;
    G4cerr << "Error: option not recognized" << G4endl;

    PrintUsage();
    return 1;

  }

  // Job termination.
  delete run_manager;
  return 0;
}
