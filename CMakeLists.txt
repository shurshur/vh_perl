SET(PERLSCRIPT_VERSION_MAJOR 1)
SET(PERLSCRIPT_VERSION_MINOR 1)
SET(PERLSCRIPT_VERSION_PATCH 1)
SET(PERLSCRIPT_VERSION "${PERLSCRIPT_VERSION_MAJOR}.${PERLSCRIPT_VERSION_MINOR}.${PERLSCRIPT_VERSION_PATCH}")

ADD_SUBDIRECTORY(vh)

Find_Package(Perl REQUIRED)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
ADD_DEFINITIONS(-g -DPERLSCRIPT_VERSION="${PERLSCRIPT_VERSION}" `perl -MExtUtils::Embed -e ccopts`)

SET(PERLSCRIPT_HDRS
	cpiperl.h
	cconsole.h
	cperlinterpreter.h
	cperlmulti.h
	callbacks.h
)

SET(PERLSCRIPT_SRCS
	cpiperl.cpp
	cconsole.cpp
	cperlinterpreter.cpp
	cperlmulti.cpp
	callbacks.cpp
)

ADD_LIBRARY(libperl_pi MODULE ${PERLSCRIPT_SRCS})
SET_TARGET_PROPERTIES(libperl_pi PROPERTIES OUTPUT_NAME "perl_pi")
find_library(PERL_LIBRARIES perl)
target_link_libraries(libperl_pi ${PERL_LIBRARIES})

INSTALL(TARGETS libperl_pi LIBRARY DESTINATION lib)
