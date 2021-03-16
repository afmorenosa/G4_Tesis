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
#include <regex>

namespace {
  void PrintUsage() {
    G4cerr << G4endl;
    G4cerr << " Usage: " << G4endl;
    G4cerr << " exampleB4a [run mode] [options]" << G4endl;
    G4cerr << G4endl;
    G4cerr << "   Run mode:" << G4endl;
    G4cerr << "      -c, --compiled\t Run whit the configuration given by the"
    << " compiled program [default]" << G4endl;
    G4cerr << "      -g, --graphics\t Run with the graphical interface"
    << G4endl;
    G4cerr << "      -m, --macro [macro]\t Run a macro" << G4endl;
    G4cerr << G4endl;
    G4cerr << "Just use one run mode per run." << G4endl;
    G4cerr << G4endl;
    G4cerr << G4endl;
    G4cerr << "   Options:" << G4endl;
    G4cerr << "      -t, --threads [number of threads]\t Set the number of"
    << " threads" << G4endl;
    G4cerr << "      -h, --help\t Print the usage" << G4endl;
    G4cerr << G4endl;

  }
}

int main(int argc, char *argv[]) {
  // Evaluate arguments
  //
  if ( argc > 5 ) {

    PrintUsage();
    return 1;

  }

  // Number of threads.
  G4int n_threads = 1;

  // Run modes.
  G4bool is_compiled = true;
  G4bool is_graphics = false;
  G4bool is_macro = false;
  G4bool mode = false;

  // Macro file name, in case of macro run mode.
  G4String macro_file = "";

  for (int arg_index = 1; arg_index < argc; arg_index++) {
    if ( G4String(argv[arg_index]) == "-h" ||
    G4String(argv[arg_index]) == "--help" ) {

      PrintUsage();
      return 0;

    } else if ( G4String(argv[arg_index]) == "-t" ||
    G4String(argv[arg_index]) == "--threads" ) {


      if (arg_index + 1 >= argc) {

        G4cerr << G4endl;
        G4cerr << "Error Threads: give the number of thread."
        << G4endl << G4endl;

        return 1;
      } else if (G4String(argv[arg_index + 1][0]) == "-") {

        G4cerr << G4endl;
        G4cerr << "Error Threads: give the number of thread."
        << G4endl << G4endl;

        return 1;
      }

      n_threads = atoi(argv[arg_index + 1]);

      if ( std::regex_match(
        G4String(argv[arg_index + 1][0]),
        std::regex("[^0-9]")
      ) ) {

        G4cerr << G4endl;
        G4cerr << "Error Threads: give a number."
        << G4endl << G4endl;

        return 1;

      }

      arg_index++;

    } else if ( G4String(argv[arg_index]) == "-c" ||
    G4String(argv[arg_index]) == "--compiled" ) {

      if ( mode ) {

        G4cerr << G4endl;
        G4cerr << "Error Runner: two methods give, select just one." << G4endl;

        PrintUsage();
        return 1;

      } else {

        mode = true;

      }

    } else if ( G4String(argv[arg_index]) == "-g" ||
    G4String(argv[arg_index]) == "--graphics" ) {

      if ( mode ) {

        G4cerr << G4endl;
        G4cerr << "Error Runner: two methods give, select just one." << G4endl;

        PrintUsage();
        return 1;

      } else {

        mode = is_graphics = true;
        is_compiled = false;

      }

    } else if ( G4String(argv[arg_index]) == "-m" ||
    G4String(argv[arg_index]) == "--macro" ) {

      if ( mode ) {

        G4cerr << G4endl;
        G4cerr << "Error Runner: two methods give, select just one." << G4endl;

        PrintUsage();
        return 1;

      } else {

        try {
          mode = is_macro = true;
          is_compiled = false;

          macro_file = G4String(argv[arg_index + 1]);
          arg_index++;

        } catch (...) {

          G4cerr << G4endl;
          G4cerr << "Error Macro: there is a problem with the macro file name."
          << G4endl << G4endl;

          return 1;

        }

      }

    } else {

        G4cerr << G4endl;
        G4cerr << "Error Option: option not recognized." << G4endl;

        PrintUsage();
        return 1;

    }

  }

  // Construct the default run manager.
#ifdef G4MULTITHREADED
  std::cout << "INFO: Multithreaded, threads=" << n_threads << '\n';

  G4MTRunManager *run_manager = new G4MTRunManager;

  G4RootAnalysisManager::Instance();
  if ( n_threads > 0 ) {

    run_manager->SetNumberOfThreads(n_threads);

  }
#else
  G4RunManager *run_manager = new G4RunManager;
#endif

  run_manager->SetVerboseLevel(0);

  // Set mandatory initialization  classes.
  run_manager->SetUserInitialization(new H4Detector);

  auto physicsList = new QGSP_BERT;
  run_manager->SetUserInitialization(physicsList);

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

  if (is_compiled) {

    // Start a run.
    int number_of_events = 5;
    run_manager->BeamOn(number_of_events);

  } else if (is_graphics) {

    // Initialize vis manager for vis commands.
    G4VisManager* vis_manager = new G4VisExecutive;
    vis_manager->Initialize();
    // interactive mode : define UI session.
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    UImanager->ApplyCommand("/control/execute G4Macros/init_vis.mac");
    ui->SessionStart();
    delete ui;

  } else if (is_macro) {

    // batch mode.
    G4String command = "/control/execute ";
    UImanager->ApplyCommand(command+macro_file);

  }

  // Job termination.
  delete run_manager;
  return 0;
}
