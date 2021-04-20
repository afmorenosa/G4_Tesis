# Add Plotter headers.
configure_file(hist_plotter.hpp
  ${CMAKE_BINARY_DIR}/include/hist_plotter.hpp
)

# Add Plotter source.
file(GLOB SOURCES hist_plotter.cpp)

# Add Plotter lib.
add_library(plotter ${SOURCES})

# Link the ROOT libs.
target_link_libraries(plotter ${ROOT_LIBRARIES})
