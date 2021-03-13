# Add Tracking Action header.
configure_file(H4TrackingAction.hpp
  ${CMAKE_BINARY_DIR}/include/H4TrackingAction.hpp
)

# Add Tracking Action source.
file(GLOB SOURCES H4TrackingAction.cpp)

# Add Tracking Action lib.
add_library(tracking_action ${SOURCES})

# Link the event generator lib.
target_link_libraries(tracking_action event_action)
