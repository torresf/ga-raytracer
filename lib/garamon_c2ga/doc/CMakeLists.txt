find_package (Doxygen)

message("c2ga_SOURCE_DIR     " ${c2ga_SOURCE_DIR})
message("c2ga_BINARY_DIR     " ${c2ga_BINARY_DIR})
message("DOXYGEN_EXECUTABLE  " ${DOXYGEN_EXECUTABLE})

if(DOXYGEN_FOUND)
  configure_file (${c2ga_SOURCE_DIR}/doc/Doxyfile-html.cmake ${c2ga_BINARY_DIR}/doc/Doxyfile-html)
  add_custom_target (html ${DOXYGEN_EXECUTABLE} ${c2ga_BINARY_DIR}/doc/Doxyfile-html)
endif (DOXYGEN_FOUND)
