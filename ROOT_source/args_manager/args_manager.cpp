#include "args_manager.hpp"

namespace fs = std::filesystem;

void print_usage() {
  std::cerr << std::endl;
  std::cerr << " Usage: " << std::endl;
  std::cerr << " analysis_ntuples <input_root_file> [-l label]" << std::endl;
  std::cerr << std::endl;
  std::cerr << "   Options:" << std::endl;
  std::cerr << "      -l, --label output_label\t Set a label for the output "
  << "files. If none if given,\n                        \t the inputfile name "
  << "will be used as label." << std::endl;
  std::cerr << "      -h, --help              \t Print the usage." << std::endl;
  std::cerr << std::endl;
}

std::map<const char *, const char *> parse_args(int argc, char *argv[]) {

  std::map<const char *, const char *> arguments;

  for (int i = 1; i < argc; i++) {
    if (
      std::regex_match(argv[i], std::regex("-h")) ||
      std::regex_match(argv[i], std::regex("--help"))
    ) {

      arguments["help"] = "";
      return arguments;

    } else if (
      std::regex_match(argv[i], std::regex("^-l(=.+)?")) ||
      std::regex_match(argv[i], std::regex("^--label(=.+)?"))
    ) {

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

      if (arguments.find("file") != arguments.end()) {
        arguments["error"] = "\nError: Multiple input files given, just one "
        "shuld be given.\n";
        return arguments;
      }

      arguments["file"] = argv[i];

      if( !fs::exists(fs::path(arguments["file"])) ) {
        std::string error_str = "\nError: input file ";
        error_str += std::string(arguments["file"]);
        error_str += " does not exist.\n";

        arguments["error"] = error_str.c_str();
        return arguments;
      }

    }
  }

  if (arguments.find("file") == arguments.end()) {
    arguments["error"] = "\nError: No input file given.\n";
    return arguments;
  }

  if (arguments.find("label") == arguments.end()) {
    arguments["label"] = arguments["file"];
  }

  return arguments;

}

//
// args_manager.cpp ends here.
//
