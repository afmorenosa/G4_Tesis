configure_file(H4Detector.hpp
  ${CMAKE_BINARY_DIR}/include/H4Detector.hpp
)

file(GLOB SOURCES H4Detector.cpp H4Module.cpp)
add_library(detector ${SOURCES})
