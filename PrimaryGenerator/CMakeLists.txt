# Add Primary Generator header.
configure_file(H4PrimaryGenerator.hpp
  ${CMAKE_BINARY_DIR}/include/H4PrimaryGenerator.hpp
)

# Add Primary Generator source.
file(GLOB SOURCES H4PrimaryGenerator.cpp)

# Add Primary Generator lib.
add_library(primary_generator ${SOURCES})
