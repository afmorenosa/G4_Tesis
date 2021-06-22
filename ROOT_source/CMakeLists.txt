
add_subdirectory(args_manager)
add_subdirectory(plotter)
add_subdirectory(test)

### Add an executable.
add_executable(analysis_ntuples analysis_ntuples.cpp)

### Link libraries.
target_link_libraries(analysis_ntuples
  ${ROOT_LIBRARIES} ${ROOT_EXE_LINKER_FLAGS} args_manager plotter data_test
)
