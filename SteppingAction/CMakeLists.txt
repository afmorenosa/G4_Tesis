# Add Stepping Action header.
configure_file(H4SteppingAction.hpp
  ${CMAKE_BINARY_DIR}/include/H4SteppingAction.hpp
)

# Add Stepping Action source.
file(GLOB SOURCES H4SteppingAction.cpp)

# Add Stepping Action lib.
add_library(stepping_action ${SOURCES})

# Link the event generator lib.
target_link_libraries(stepping_action event_action)
