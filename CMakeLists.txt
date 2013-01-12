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
)

# cpiperl.cpp will be appended below
SET(PERLSCRIPT_SRCS
	cconsole.cpp
	cperlinterpreter.cpp
	cperlmulti.cpp
)

CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/cpiperl.cpp" "${CMAKE_CURRENT_BINARY_DIR}/cpiperl.cpp" @ONLY)
LIST(APPEND PERLSCRIPT_SRCS "${CMAKE_CURRENT_BINARY_DIR}/cpiperl.cpp")

ADD_LIBRARY(libperl_pi MODULE ${PERLSCRIPT_SRCS})
SET_TARGET_PROPERTIES(libperl_pi PROPERTIES OUTPUT_NAME "perl_pi")
find_library(PERL_LIBRARIES perl)
target_link_libraries(libperl_pi ${PERL_LIBRARIES})

ADD_LIBRARY(libvh_perl_wrapper MODULE "wrapper.cpp")
SET_TARGET_PROPERTIES(libvh_perl_wrapper PROPERTIES OUTPUT_NAME "vh_perl_wrapper")
target_link_libraries(libvh_perl_wrapper ${PERL_LIBRARIES})

INSTALL(TARGETS libperl_pi libvh_perl_wrapper LIBRARY DESTINATION lib)
