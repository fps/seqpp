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

add_custom_command(
	COMMAND swig -c++ -debug-classes  -o ${PROJECT_BINARY_DIR}/seqpp_lua_wrap.cc -lua ${PROJECT_SOURCE_DIR}/seqpp.i
	OUTPUT ${PROJECT_BINARY_DIR}/seqpp_lua_wrap.cc
	DEPENDS jack_midi_consumer.h consumer.h seqpp.i
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/
)

add_custom_command(
	COMMAND swig -c++ -debug-classes  -o ${PROJECT_BINARY_DIR}/seqpp_python_wrap.cc -python ${PROJECT_SOURCE_DIR}/seqpp.i
	OUTPUT ${PROJECT_BINARY_DIR}/seqpp_python_wrap.cc
	DEPENDS jack_midi_consumer.h consumer.h seqpp.i
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/
)


#add_definitions(-O3 -ffast-math -march=native -mtune=native -funsafe-math-optimizations -funroll-loops)
#add_definitions(-pg)

#set(CMAKE_EXE_LINKER_FLAGS -pg)

find_package(PkgConfig)

find_package(Lua51)
find_package(PythonLibs)
find_package(Boost COMPONENTS thread program_options system REQUIRED)

pkg_check_modules(SAMPLERATE samplerate)
pkg_check_modules(SNDFILE sndfile)
pkg_check_modules(JACK jack)

include_directories(. ${PYTHON_INCLUDE_DIRS} ${Boost_PROGRAM_OPTIONS_INCLUDE_DIRS} ${Boost_SYSTEM_INCLUDE_DIRS} ${Boost_THREAD_INCLUDE_DIRS} ${LUA_INCLUDE_DIR} ${SAMPLERATE_INCLUDE_DIRS} ${SNDFILE_INCLUDE_DIRS} ${JACK_INCLUDE_DIRS})
link_directories(${Boost_THREAD_LIBRARY_DIRS} ${LUA_LIBRARY_DIRS} ${SAMPLERATE_LIBRARY_DIRS} ${SNDFILE_LIBRARY_DIRS} ${JACK_LIBRARY_DIRS})

add_library(lseqpp SHARED ${PROJECT_BINARY_DIR}/seqpp_lua_wrap.cc) 
add_library(pseqpp SHARED ${PROJECT_BINARY_DIR}/seqpp_python_wrap.cc) 

set_target_properties(lseqpp PROPERTIES PREFIX "" SUFFIX ".so")
set_target_properties(pseqpp PROPERTIES PREFIX "" SUFFIX ".so")

target_link_libraries(lseqpp ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY} ${LUA_LIBRARIES} ${SAMPLERATE_LIBRARIES} ${SNDFILE_LIBRARIES} ${JACK_LIBRARIES})
target_link_libraries(pseqpp ${PYTHON_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY} ${LUA_LIBRARIES} ${SAMPLERATE_LIBRARIES} ${SNDFILE_LIBRARIES} ${JACK_LIBRARIES})

include_directories(${JASS_INCLUDE_DIRS})
include_directories(${PROJECT_BINARY_DIR})

install(TARGETS lseqpp LIBRARY DESTINATION lib/lua/5.1/ RENAME seqpp.so)
install(TARGETS lseqpp LIBRARY DESTINATION lib/lua/5.1/ RENAME seqpp.so)

