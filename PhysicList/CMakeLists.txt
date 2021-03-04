# Add Physics List header.
configure_file(H4PhysicList.hpp
  ${CMAKE_BINARY_DIR}/include/H4PhysicList.hpp
)

# Add Physics List source.
file(GLOB SOURCES H4PhysicList.cpp)

# Add the Physics List lib.
add_library(physics_list ${SOURCES})
