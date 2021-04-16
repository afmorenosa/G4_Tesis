# Add Actions header.
configure_file(H4Actions.hpp
  ${CMAKE_BINARY_DIR}/include/H4Actions.hpp
)

# Add Actions source.
file(GLOB SOURCES H4Actions.cpp)

# Add the Action lib.
add_library(actions ${SOURCES})

# Link the event generator lib.
target_link_libraries(actions
  primary_generator
  stepping_action
  tracking_action
  run_action
  event_action
)
