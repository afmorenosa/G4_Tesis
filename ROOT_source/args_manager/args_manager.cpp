#include "args_manager.hpp"

// Use the namespace fs for filesystem lib.
namespace fs = std::filesystem;

//************************************//
// Print the usage of the executable. //
//************************************//
void print_usage() {

  std::string line;

  std::ifstream usage_file("ROOT_source/args_manager/usage.txt");

  while (getline (usage_file, line)) {
    std::cout << line << "\n";
  }
  std::cout << '\n';

  usage_file.close();

}

//**********************************//
// Parse console arguments acording //
// the useage of the executable.    //
//**********************************//
std::map<std::string, const char *> parse_args(int argc, char *argv[]) {

  // Create a map for the parsed arguments.
  std::map<std::string, const char *> arguments;

  for (int i = 1; i < argc; i++) {

    if (
      std::regex_match(argv[i], std::regex("-h")) ||
      std::regex_match(argv[i], std::regex("--help"))
    ) {
      // Check if help is called. If so, return.

      arguments["help"] = "";
      return arguments;

    } else if (
      std::regex_match(argv[i], std::regex("^--plot_histos(=.+)?"))
    ) {

      if (arguments.find("histos_file") != arguments.end()) {
        arguments["error"] = "\nError: Multiple input files given, just one "
        "shuld be given.\n";
        return arguments;
      }

      if (TString(argv[i]).Contains("=")) {
        size_t pos_eq = std::string(argv[i]).find('=');

        arguments["histos_file"] =
        std::string(argv[i]).substr(pos_eq + 1).c_str();

      } else {

        if ( i+1 >= argc || std::regex_match(argv[i+1], std::regex("^-.+")) ) {
          arguments["error"] = "\nError: No valid file given.\n";
          return arguments;
        }

        arguments["histos_file"] = argv[i + 1];
        i++;
      }

      if( !fs::exists(fs::path(arguments["histos_file"])) ) {
        std::string error_msg = "\nInput file ";
        error_msg += std::string(arguments["histos_file"]);
        error_msg += " does not exist.\n";

        std::cout << error_msg;

        arguments["error"] = "Error: Invalid input file\n";
        return arguments;
      }

    } else if (
      std::regex_match(argv[i], std::regex("^-t(=.+)?")) ||
      std::regex_match(argv[i], std::regex("^--test(=.+)?"))
    ) {

      if (arguments.find("test_file_1") != arguments.end()) {
        arguments["error"] = "\nError: Multiple test arguments given, just one "
        "is allowed.\n";
        return arguments;
      }

      if (TString(argv[i]).Contains("=")) {
        size_t pos_eq = std::string(argv[i]).find('=');
        size_t pos_comma = std::string(argv[i]).find(',', pos_eq + 1);

        arguments["test_file_1"] =
        std::string(argv[i]).substr(pos_eq + 1, pos_comma - pos_eq - 1).c_str();

        arguments["test_file_2"] =
        std::string(argv[i]).substr(pos_comma + 1).c_str();

      } else {

        if ( i+2 >= argc || std::regex_match(argv[i+1], std::regex("^-.+")) ||
        std::regex_match(argv[i+2], std::regex("^-.+"))) {
          arguments["error"] = "\nError: No valid arguments given.\n";
          return arguments;
        }

        arguments["test_file_1"] = argv[i + 1];
        arguments["test_file_2"] = argv[i + 2];
        i += 2;

      }

      if( !fs::exists(fs::path(arguments["test_file_1"])) ) {
        std::string error_msg = "\nInput file ";
        error_msg += std::string(arguments["test_file_1"]);
        error_msg += " does not exist.\n";

        std::cout << error_msg;

        arguments["error"] = "Error: Invalid input file\n";
        return arguments;
      }

      if( !fs::exists(fs::path(arguments["test_file_2"])) ) {
        std::string error_msg = "\nInput file ";
        error_msg += std::string(arguments["test_file_2"]);
        error_msg += " does not exist.\n";

        std::cout << error_msg;

        arguments["error"] = "Error: Invalid input file\n";
        return arguments;
      }

    } else if (
      std::regex_match(argv[i], std::regex("^-s(=.+)?")) ||
      std::regex_match(argv[i], std::regex("^--scell(=.+)?"))
    ) {

      if (arguments.find("scell_file_1") != arguments.end()) {
        arguments["error"] = "\nError: Multiple calls to significative cells "
        "proccess, just one is allowed.\n";
        return arguments;
      }

      int file_number = 1;

      if (TString(argv[i]).Contains("=")) {
        size_t pos_eq = std::string(argv[i]).find('=');

        size_t pos_comma = std::string(argv[i]).find(',', pos_eq + 1);

        while (pos_comma) {
          std::string key_string =
          std::string("scell_file_") +
          std::to_string(file_number);

          arguments[key_string] =
          std::string(argv[i]).substr(pos_eq + 1, pos_comma - pos_eq - 1).c_str();

          pos_eq = pos_comma;
          pos_comma = std::string(argv[i]).find(',', pos_eq + 1);

          file_number++;
        }

      } else {
        if ( i+2 >= argc) {
          arguments["error"] = "\nError: No valid arguments given.\n";
          return arguments;
        }

        while ( !(std::regex_match(argv[i+file_number], std::regex("^-.+"))) ){
          std::string key_string =
          std::string("scell_file_") +
          std::to_string(file_number);

          arguments[key_string] = argv[i + file_number];

          file_number++;
        }

        i += file_number - 1;

      }

      for (int file_index = 1; file_index < file_number; file_index++) {
        std::string key_string =
        std::string("scell_file_") +
        std::to_string(file_index);


        if( !fs::exists(fs::path(arguments[key_string])) ) {
          std::string error_msg = "\nInput file ";
          error_msg += std::string(arguments[key_string]);
          error_msg += " does not exist.\n";

          std::cout << error_msg;

          arguments["error"] = "Error: Invalid input file\n";
          return arguments;
        }
      }

      const char *buffer =  std::to_string(file_number).c_str();
      arguments["scell_n_files"] = buffer;

    } else if (
      std::regex_match(argv[i], std::regex("^-v(=.+)?")) ||
      std::regex_match(argv[i], std::regex("^--variable(=.+)?"))
    ) {

      if (arguments.find("variable") != arguments.end()) {
        arguments["error"] = "\nError: Multiple variable arguments given, "
        "just one is allowed.\n";
        return arguments;
      }

      if (TString(argv[i]).Contains("=")) {
        size_t pos_eq = std::string(argv[i]).find('=');

        arguments["variable"] = std::string(argv[i]).substr(pos_eq + 1).c_str();

      } else {

        if ( i+1 >= argc || std::regex_match(argv[i+1], std::regex("^-.+")) ) {
          arguments["error"] = "\nError: No valid arguments given.\n";
          return arguments;
        }

        arguments["variable"] = argv[i + 1];
        i += 1;

      }

      if ( arguments["variable"] != std::string("electrons") &&
      arguments["variable"] != std::string("photons") &&
      arguments["variable"] != std::string("E") &&
      arguments["variable"] != std::string("SL") ) {
        arguments["error"] = "No valid variable argument.";
        return arguments;
      }

    } else if (
      std::regex_match(argv[i], std::regex("^-m(=.+)?")) ||
      std::regex_match(argv[i], std::regex("^--material(=.+)?"))
    ) {

      if (arguments.find("material") != arguments.end()) {
        arguments["error"] = "\nError: Multiple material arguments given, "
        "just one is allowed.\n";
        return arguments;
      }

      if (TString(argv[i]).Contains("=")) {
        size_t pos_eq = std::string(argv[i]).find('=');

        arguments["material"] = std::string(argv[i]).substr(pos_eq + 1).c_str();

      } else {

        if ( i+1 >= argc || std::regex_match(argv[i+1], std::regex("^-.+")) ) {
          arguments["error"] = "\nError: No valid arguments given.\n";
          return arguments;
        }

        arguments["material"] = argv[i + 1];
        i += 1;

      }

      if ( arguments["material"] != std::string("scintillator") &&
      arguments["material"] != std::string("lead") ) {
        arguments["error"] = "No valid material argument.";
        return arguments;
      }

    } else if (
      std::regex_match(argv[i], std::regex("^-l(=.+)?")) ||
      std::regex_match(argv[i], std::regex("^--label(=.+)?"))
    ) {

      // Add argument for output label.

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
      std::string error_msg = std::string("\nThe argument ") +
      std::string(argv[i]) + std::string(" is not recognized.\n");

      std::cout << error_msg;

      arguments["error"] = "Error: No valid argument.\n";

      return arguments;
    }

  }

  if (arguments.find("label") == arguments.end()) {
    arguments["label"] = "output";
  }

  if (arguments.find("variable") == arguments.end()) {
    arguments["variable"] = "photons";
  }

  if (arguments.find("material") == arguments.end()) {
    arguments["material"] = "scintillator";
  }

  return arguments;

}

//
// args_manager.cpp ends here.
//
