configure_file(
  ia_train.py
  ${CMAKE_BINARY_DIR}/python_scripts/ia_train.py
  COPYONLY
  )

configure_file(
  run_ia.sh
  ${CMAKE_BINARY_DIR}/python_scripts/run_ia.sh
  COPYONLY
  )

configure_file(
  submit.sub
  ${CMAKE_BINARY_DIR}/python_scripts/submit.sub
  COPYONLY
  )

configure_file(
  data_mng/root_files_mng.py
  ${CMAKE_BINARY_DIR}/python_scripts/root_files_mng.py
  COPYONLY
  )

configure_file(
  data_mng/significative_cells.csv
  ${CMAKE_BINARY_DIR}/python_scripts/significative_cells.csv
  COPYONLY
  )
