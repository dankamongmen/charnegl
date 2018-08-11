cmake_minimum_required (VERSION 3.12) # 3.12's necessary for OBJECT libraries
project (charn VERSION 0.0.1)
enable_testing()

# Compiler-specific flags. One would think that CMake would somehow abstract
# most of this away...
# FIXME turn on -fvisibility=hidden
set(CHARN_CXX_FLAGS
	-O2 -Wall -W -Wshadow -Wextra
	CACHE STRING "CXXFLAGS used to compiler ${PROJECT_NAME}")

# Include external CMake config files
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# External deps
include(FindPkgConfig)
find_package(Threads REQUIRED)
find_package(Config++ REQUIRED)
find_package(GTest REQUIRED)
pkg_check_modules(LIBINPUT libinput>=1.11.0 REQUIRED)
pkg_check_modules(LIBXDG libxdg-basedir>=1.2.0 REQUIRED)
pkg_check_modules(WAYLAND-SERVER wayland-server>=1.15.0 REQUIRED)

# Libraries / user executables
add_library(charn SHARED src/libcharn/config.cpp)
set_target_properties(charn PROPERTIES
	SOVERSION 1
)
target_compile_options(charn PRIVATE ${CHARN_CXX_FLAGS})
target_include_directories(charn
	PUBLIC ${CONFIG++_INCLUDE_DIR}
	PRIVATE src
)
target_link_libraries(charn
	${CONFIG++_LIBRARY}
)
add_executable(charn-bin src/charn/charn.cpp)
set_target_properties(charn-bin PROPERTIES OUTPUT_NAME charn)
target_compile_options(charn-bin PRIVATE ${CHARN_CXX_FLAGS})
target_include_directories(charn-bin PRIVATE src)
target_link_libraries(charn-bin
	${CMAKE_THREAD_LIBS_INIT}
	${LIBXDG_LDFLAGS}
	charn
)

# Testing
add_executable(charntest src/test/charntest.cpp)
target_compile_options(charntest PRIVATE ${CHARN_CXX_FLAGS})
target_include_directories(charntest PRIVATE src)
target_link_libraries(charntest
	${CMAKE_THREAD_LIBS_INIT}
	${GTEST_BOTH_LIBRARIES}
	charn
)

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
install(TARGETS charn-bin DESTINATION bin)
install(TARGETS charn DESTINATION lib)
