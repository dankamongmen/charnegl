cmake_minimum_required (VERSION 3.2) # necessary for C++11 support
project (charn)

# Include external CMake config files
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Config++ REQUIRED)

add_library(charn src/libcharn/configfile.cpp)

# Documentation
find_program(XSLT_EXECUTABLE NAMES xsltproc)
set(XSLT_OPTS
  --nonet
)
set(MAN_NAMES charn.1)
set(MAN_FILES)
foreach(m IN LISTS MAN_NAMES)
  set(mf ${CMAKE_BINARY_DIR}/${m})
  set(ms ${CMAKE_SOURCE_DIR}/doc/man/${m}.xml)
  add_custom_command(OUTPUT ${mf}
    COMMAND ${XSLT_EXECUTABLE} ${XSLT_OPTS} ${ms}
    DEPENDS ${ms} ${CMAKE_SOURCE_DIR}/doc/man/${PROJECT_NAME}.ent
    COMMENT "Building manpage ${mf}"
    VERBATIM)
  list(APPEND MAN_FILES ${mf})
endforeach()

add_custom_target(man ALL DEPENDS ${MAN_FILES})
