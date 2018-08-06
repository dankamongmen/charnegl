cmake_minimum_required (VERSION 3.10) # necessary for gtest_discover_targets
project (charn VERSION 0.0.1)
enable_testing()

# Include external CMake config files
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# External deps
include(FindPkgConfig)
find_package(Threads REQUIRED)
find_package(Config++ REQUIRED)
find_package(GTest REQUIRED)
pkg_check_modules(LIBXDG libxdg-basedir REQUIRED)

# Libraries / user executables
add_library(charn SHARED src/libcharn/config.cpp)
set_target_properties(charn PROPERTIES
	SOVERSION 1
)
target_include_directories(charn
	PUBLIC ${CONFIG++_INCLUDE_DIR}
	PRIVATE src
)
target_link_libraries(charn
	${CONFIG++_LIBRARY}
)
add_executable(charn-bin src/charn/charn.cpp)
set_target_properties(charn-bin PROPERTIES OUTPUT_NAME charn)
target_link_libraries(charn-bin
	${CMAKE_THREAD_LIBS_INIT}
	${LIBXDG_LDFLAGS}
	charn
)
target_include_directories(charn-bin PRIVATE src)

# Testing
add_executable(charntest src/test/charntest.cpp)
target_link_libraries(charntest
	${CMAKE_THREAD_LIBS_INIT}
	${GTEST_BOTH_LIBRARIES}
	charn
)
target_include_directories(charntest PRIVATE src)

gtest_discover_tests(charntest)

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

# Installation
