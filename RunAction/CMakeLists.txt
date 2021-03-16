# Add Run Action header.
configure_file(H4RunAction.hpp
  ${CMAKE_BINARY_DIR}/include/H4RunAction.hpp
)

# Add Run Action source.
file(GLOB SOURCES H4RunAction.cpp)

# Add Run Action lib.
add_library(run_action ${SOURCES})

# Link the event generator lib.
target_link_libraries(run_action event_action)
