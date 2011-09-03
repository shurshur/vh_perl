#cmake_minimum_required (VERSION 2.6)
#PROJECT(PERLSCRIPT)
SET(PERLSCRIPT_VERSION_MAJOR 1)
SET(PERLSCRIPT_VERSION_MINOR 1)
SET(PERLSCRIPT_VERSION_PATCH 1)
SET(PERLSCRIPT_VERSION "${PERLSCRIPT_VERSION_MAJOR}.${PERLSCRIPT_VERSION_MINOR}.${PERLSCRIPT_VERSION_PATCH}")

#SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)
#INCLUDE (CheckIncludeFiles)

#Find_Package(MySQL REQUIRED)
#Find_Package(VerliHub REQUIRED)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${MYSQL_INCLUDE_DIR}
#  ${VERLIHUB_INCLUDE_DIRS})
ADD_DEFINITIONS(-g -DPERLSCRIPT_VERSION="${PERLSCRIPT_VERSION}" `perl -MExtUtils::Embed -e ccopts`)

SET(PERLSCRIPT_HDRS
	cpiperl.h
	cconsole.h
	cperlinterpreter.h
	cperlmulti.h
)

SET(PERLSCRIPT_SRCS
	cpiperl.cpp
	cconsole.cpp
	cperlinterpreter.cpp
	cperlmulti.cpp
)

ADD_LIBRARY(libperl_pi MODULE ${PERLSCRIPT_SRCS})
SET_TARGET_PROPERTIES(libperl_pi PROPERTIES OUTPUT_NAME "perl_pi")
find_library(PERL_LIBRARIES perl)
target_link_libraries(libperl_pi ${PERL_LIBRARIES})

add_custom_target(vh_make)
add_custom_command(TARGET vh_make
  COMMAND perl Makefile.PL
  COMMAND make
  WORKING_DIRECTORY "plugins/perl/vh")
add_dependencies(libperl_pi vh_make)

INSTALL(TARGETS libperl_pi LIBRARY DESTINATION lib)
