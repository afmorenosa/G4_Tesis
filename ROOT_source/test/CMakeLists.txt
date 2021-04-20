# Add Data test header.
file(GLOB HEADERS *.hpp)
foreach(HEADER ${HEADERS})
  file(RELATIVE_PATH HEADER ${CMAKE_CURRENT_SOURCE_DIR} ${HEADER})
  configure_file("${HEADER}" "${CMAKE_BINARY_DIR}/include/${HEADER}")
endforeach()


configure_file(test.hpp
  ${CMAKE_BINARY_DIR}/include/test.hpp
)

# Add Data test source.
file(GLOB SOURCES *.cpp)

# Add Data test lib.
add_library(data_test ${SOURCES})

# Link the ROOT libs.
target_link_libraries(data_test ${ROOT_LIBRARIES})
