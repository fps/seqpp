cmake_minimum_required (VERSION 2.6)
#set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_BUILD_TYPE Release)
project (seqpp)

set(PROJECT_VERSION "0.1.0")
set(ARCHIVE_NAME ${CMAKE_PROJECT_NAME}-${PROJECT_VERSION})
add_custom_target(dist
    COMMAND git archive --prefix=${ARCHIVE_NAME}/ HEAD
        | bzip2 > ${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.bz2
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

#add_custom_command(
#	COMMAND xsdcxx cxx-tree --generate-serialization --generate-ostream --output-dir ${PROJECT_BINARY_DIR}/ ${PROJECT_SOURCE_DIR}/seqpp.xsd
#	OUTPUT ${PROJECT_BINARY_DIR}/seqpp.hxx ${PROJECT_BINARY_DIR}/seqpp.cxx
#	DEPENDS ${PROJECT_SOURCE_DIR}/seqpp.xsd
#	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/
#)

add_custom_command(
	COMMAND swig -c++ -lua -external-runtime ${PROJECT_BINARY_DIR}/luarun.h
	OUTPUT ${PROJECT_BINARY_DIR}/luarun.h
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/
)

add_custom_command(
	COMMAND swig -c++ -debug-classes  -o ${PROJECT_BINARY_DIR}/seqpp_wrap.cc -lua ${PROJECT_SOURCE_DIR}/seqpp.i
	OUTPUT ${PROJECT_BINARY_DIR}/seqpp_wrap.cc
	DEPENDS jack_midi_consumer.h consumer.h seqpp.i
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/
)

#add_definitions(-O3 -ffast-math -march=native -mtune=native -funsafe-math-optimizations -funroll-loops)
#add_definitions(-pg)

#set(CMAKE_EXE_LINKER_FLAGS -pg)

find_package(PkgConfig)

find_package(Lua51)
find_package(Boost COMPONENTS program_options)

pkg_check_modules(SAMPLERATE samplerate)
pkg_check_modules(SNDFILE sndfile)
pkg_check_modules(JACK jack)

include_directories(. ${LUA_INCLUDE_DIR} ${SAMPLERATE_INCLUDE_DIRS} ${SNDFILE_INCLUDE_DIRS} ${JACK_INCLUDE_DIRS})
link_directories(${LUA_LIBRARY_DIRS} ${SAMPLERATE_LIBRARY_DIRS} ${SNDFILE_LIBRARY_DIRS} ${JACK_LIBRARY_DIRS})


add_executable(test_seqpp main.cc)
add_library(seqpp SHARED ${PROJECT_BINARY_DIR}/seqpp_wrap.cc) 
set_target_properties(seqpp PROPERTIES PREFIX "")

target_link_libraries(seqpp ${Boost_PROGRAM_OPTIONS_LIBRARY} ${LUA_LIBRARIES} ${SAMPLERATE_LIBRARIES} ${SNDFILE_LIBRARIES} ${JACK_LIBRARIES})
target_link_libraries(test_seqpp  ${Boost_PROGRAM_OPTIONS_LIBRARY} ${LUA_LIBRARIES} ${SAMPLERATE_LIBRARIES} ${SNDFILE_LIBRARIES} ${JACK_LIBRARIES})

include_directories(${JASS_INCLUDE_DIRS})
include_directories(${PROJECT_BINARY_DIR})

install(TARGETS seqpp LIBRARY DESTINATION lib)

