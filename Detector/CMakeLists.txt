configure_file(H4Detector.hpp
  ${CMAKE_BINARY_DIR}/include/H4Detector.hpp
)

configure_file(H4InnerSection.hpp
  ${CMAKE_BINARY_DIR}/include/H4InnerSection.hpp
)

configure_file(H4MiddleSection.hpp
  ${CMAKE_BINARY_DIR}/include/H4MiddleSection.hpp
)

configure_file(H4OuterSection.hpp
  ${CMAKE_BINARY_DIR}/include/H4OuterSection.hpp
)

file(GLOB SOURCES
  H4Detector.cpp H4InnerSection.cpp H4MiddleSection.cpp H4OuterSection.cpp
)

add_library(detector ${SOURCES})
