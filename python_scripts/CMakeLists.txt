file(GLOB PY_SCRIPTS *.py data_mng/*)

foreach(PY_SCRIPT ${PY_SCRIPTS})
  file(RELATIVE_PATH PY_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR} ${PY_SCRIPT})
  configure_file(
    ${PY_SCRIPT}
    ${CMAKE_BINARY_DIR}/python_scripts/${PY_SCRIPT}
    COPYONLY
  )
endforeach()
