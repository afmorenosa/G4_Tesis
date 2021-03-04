# Add the headers files.
# The header for the Detector Geometry.
configure_file(H4Detector.hpp
  ${CMAKE_BINARY_DIR}/include/H4Detector.hpp
)

# The header for the modules class.
configure_file(H4Module.hpp
  ${CMAKE_BINARY_DIR}/include/H4Module.hpp
)

# The headers for the inner, middle and outer modules.
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
  H4Detector.cpp
  H4Module.cpp
  H4InnerSection.cpp H4MiddleSection.cpp H4OuterSection.cpp
)

# Add the Detector lib.
add_library(detector ${SOURCES})
