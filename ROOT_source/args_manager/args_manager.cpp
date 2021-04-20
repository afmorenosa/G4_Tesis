#include "args_manager.hpp"

// Use the namespace fs for filesystem lib.
namespace fs = std::filesystem;

//************************************//
// Print the usage of the executable. //
//************************************//
void print_usage() {
  std::cerr << std::endl;
  std::cerr << " Usage: " << std::endl;
  std::cerr << " analysis_ntuples [--plot_histos file] [-t file_1 file_2 "
  << "variable material] [-l label]" << std::endl;
  std::cerr << std::endl;
  std::cerr << "   Options:" << std::endl;
  std::cerr << "      --plot_histos file\t\t Print the histograms for the file "
  << "given." << std::endl;
  std::cerr << "      -t --test file_1 file_2 variable material\t\t Get the "
  << "Kolmogorov test." << std::endl;
  std::cerr << "      -l, --label output_label\t\t Set a label for the output "
  << "files. If none if given,\n                        \t\t it will be 'output'."
  << std::endl;
  std::cerr << "      -h, --help              \t\t Print the usage." << std::endl;
  std::cerr << std::endl;
}

//**********************************//
// Parse console arguments acording //
// the useage of the executable.    //
//**********************************//
std::map<const char *, const char *> parse_args(int argc, char *argv[]) {

  // Create a map for the parsed arguments.
  std::map<const char *, const char *> arguments;

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

        arguments["histos_file"] = std::string(argv[i]).substr(pos_eq + 1).c_str();

      } else {

        if ( i+1 >= argc || std::regex_match(argv[i+1], std::regex("^-.+")) ) {
          arguments["error"] = "\nError: No valid file given.\n";
          return arguments;
        }

        arguments["histos_file"] = argv[i + 1];
        i++;
      }

      if( !fs::exists(fs::path(arguments["histos_file"])) ) {
        std::string error_str = "\nError: input file ";
        error_str += std::string(arguments["file"]);
        error_str += " does not exist.\n";

        arguments["error"] = error_str.c_str();
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

        arguments["test_file_1"] = std::string(argv[i]).substr(pos_eq + 1).c_str();

        size_t pos_comma = std::string(argv[i]).find(',', pos_eq + 1);
        arguments["test_file_2"] = std::string(argv[i]).substr(pos_comma + 1).c_str();

        pos_comma = std::string(argv[i]).find(',', pos_comma + 1);
        arguments["test_variable"] = std::string(argv[i]).substr(pos_comma + 1).c_str();

        pos_comma = std::string(argv[i]).find(',', pos_comma + 1);
        arguments["test_material"] = std::string(argv[i]).substr(pos_comma + 1).c_str();

      } else {

        if ( i+4 >= argc || std::regex_match(argv[i+1], std::regex("^-.+")) ||
        std::regex_match(argv[i+2], std::regex("^-.+")) ||
        std::regex_match(argv[i+3], std::regex("^-.+")) ||
        std::regex_match(argv[i+4], std::regex("^-.+")) ) {
          arguments["error"] = "\nError: No valid arguments given.\n";
          return arguments;
        }

        arguments["test_file_1"] = argv[i + 1];
        arguments["test_file_2"] = argv[i + 2];
        arguments["test_variable"] = argv[i + 3];
        arguments["test_material"] = argv[i + 4];
        i += 4;

      }

      if( !fs::exists(fs::path(arguments["test_file_1"])) ) {
        std::string error_str = "\nError: input file ";
        error_str += std::string(arguments["test_file_1"]);
        error_str += " does not exist.\n";

        arguments["error"] = error_str.c_str();
        return arguments;
      }

      if( !fs::exists(fs::path(arguments["test_file_2"])) ) {
        std::string error_str = "\nError: input file ";
        error_str += std::string(arguments["test_file_2"]);
        error_str += " does not exist.\n";

        arguments["error"] = error_str.c_str();
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

    }

  }

  if (arguments.find("label") == arguments.end()) {
    arguments["label"] = "output";
  }

  return arguments;

}

//
// args_manager.cpp ends here.
//
