cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

### Require out-of-source builds.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR
    "You cannot build in a source directory (or any directory with a CMakeLists.txt file).\n"
    "Please make a build subdirectory.\n"
    "Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

### Set Project name.
project(calo_ECAL VERSION 0.1.0)

### Sets C++ 11 standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

### Find Geant4 Library with UI and Vis drivers.
find_package(Geant4 REQUIRED ui_all vis_all)

### Include Geant4 Use file.
include(${Geant4_USE_FILE})

### Find Root Library.
find_package(ROOT 6.22 REQUIRED COMPONENTS Core Graf3d Graf RIO Net Geom)

### Include Root Use file.
include(${ROOT_USE_FILE})

### Add include compiler flags.
include_directories(${CMAKE_BINARY_DIR}/include)

### Add subdirectories.
add_subdirectory(include)
add_subdirectory(Detector)
add_subdirectory(PrimaryGenerator)
add_subdirectory(EventAction)
add_subdirectory(TrackingAction)
add_subdirectory(SteppingAction)
add_subdirectory(RunAction)
add_subdirectory(Actions)
add_subdirectory(python_scripts)
add_subdirectory(ROOT_source)

### Add an executable.
add_executable(calo_ECAL main.cpp)

### Link libraries.
target_link_libraries(calo_ECAL
  ${Geant4_LIBRARIES}
  detector
  actions
  primary_generator
  tracking_action
  run_action
  event_action
)

set(geant_scripts
  G4Macros/init_vis.mac
  G4Macros/vis.mac
  G4Macros/gen_dataset.mac
)

### Add macro files.
foreach(script ${geant_scripts})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${script}
    ${PROJECT_BINARY_DIR}/${script}
    COPYONLY
  )
endforeach()

### Add bash scripts.
configure_file(
  ${PROJECT_SOURCE_DIR}/bash_scripts/merge_ntuples.sh
  ${PROJECT_BINARY_DIR}/bash_scripts/merge_ntuples.sh
  COPYONLY
)
