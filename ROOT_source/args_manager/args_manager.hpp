#ifndef ARGS_MANAGER
#define ARGS_MANAGER

// C++ includes.
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>

// ROOT includes.
#include "TString.h"

void print_usage();

std::map<std::string, const char *> parse_args(int argc, char *argv[]);

#endif // ARGS_MANAGER
