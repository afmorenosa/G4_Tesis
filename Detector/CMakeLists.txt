# Add the headers Files.
# The header for the Detector Geometry.
configure_file(H4Detector.hpp
  ${CMAKE_BINARY_DIR}/include/H4Detector.hpp
)

# The headers for the inner, middle and outer modules
configure_file(H4InnerSection.hpp
  ${CMAKE_BINARY_DIR}/include/H4InnerSection.hpp
)
configure_file(H4MiddleSection.hpp
  ${CMAKE_BINARY_DIR}/include/H4MiddleSection.hpp
)
configure_file(H4OuterSection.hpp
  ${CMAKE_BINARY_DIR}/include/H4OuterSection.hpp
)

# Add Detector sources.
file(GLOB SOURCES
  H4Detector.cpp H4InnerSection.cpp H4MiddleSection.cpp H4OuterSection.cpp
)

# Add the Detector lib.
add_library(detector ${SOURCES})
