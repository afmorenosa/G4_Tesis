# Add Event Action header.
configure_file(H4EventAction.hpp
  ${CMAKE_BINARY_DIR}/include/H4EventAction.hpp
)

# Add Event Action source.
file(GLOB SOURCES H4EventAction.cpp)

# Add Event Action lib.
add_library(event_action ${SOURCES})
