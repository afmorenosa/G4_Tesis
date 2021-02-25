configure_file(H4Detector.hpp
  ${CMAKE_BINARY_DIR}/include/H4Detector.hpp
)

configure_file(H4InnerSection.hpp
  ${CMAKE_BINARY_DIR}/include/H4InnerSection.hpp
)

file(GLOB SOURCES H4Detector.cpp H4InnerSection.cpp)
add_library(detector ${SOURCES})
