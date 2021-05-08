# Add Arguments Manager header.
configure_file(args_manager.hpp
  ${CMAKE_BINARY_DIR}/include/args_manager.hpp
)

# Add Arguments Manager source.
file(GLOB SOURCES args_manager.cpp)

# Add Arguments Manager lib.
add_library(args_manager ${SOURCES})

configure_file(
  usage.txt
  usage.txt
  COPYONLY
)
