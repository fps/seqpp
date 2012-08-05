cmake_minimum_required (VERSION 2.6)
#set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_BUILD_TYPE Release)
project (pseqpp)

cmake_policy(SET CMP0002 OLD)

set(PROJECT_VERSION "0.1.0")

add_custom_command(
	COMMAND swig -c++ -debug-classes  -o ${PROJECT_BINARY_DIR}/seqpp_python_wrap.cc -python ${PROJECT_SOURCE_DIR}/../seqpp.i
	OUTPUT ${PROJECT_BINARY_DIR}/seqpp_python_wrap.cc
	DEPENDS ../seqpp/jack_midi_consumer.h ../seqpp/consumer.h ../seqpp.i
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/
)


#add_definitions(-O3 -ffast-math -march=native -mtune=native -funsafe-math-optimizations -funroll-loops)
#add_definitions(-pg)

#set(CMAKE_EXE_LINKER_FLAGS -pg)

find_package(PkgConfig)

find_package(PythonLibs)
find_package(Boost COMPONENTS thread program_options system REQUIRED)

pkg_check_modules(SAMPLERATE samplerate)
pkg_check_modules(SNDFILE sndfile)
pkg_check_modules(JACK jack)

include_directories(../seqpp ../ ${PROJECT_SOURCE_DIR}/seqpp ${PYTHON_INCLUDE_DIRS} ${Boost_PROGRAM_OPTIONS_INCLUDE_DIRS} ${Boost_SYSTEM_INCLUDE_DIRS} ${Boost_THREAD_INCLUDE_DIRS} ${LUA_INCLUDE_DIR} ${SAMPLERATE_INCLUDE_DIRS} ${SNDFILE_INCLUDE_DIRS} ${JACK_INCLUDE_DIRS})
link_directories(${Boost_THREAD_LIBRARY_DIRS} ${LUA_LIBRARY_DIRS} ${SAMPLERATE_LIBRARY_DIRS} ${SNDFILE_LIBRARY_DIRS} ${JACK_LIBRARY_DIRS})

add_library(seqpp SHARED ${PROJECT_BINARY_DIR}/seqpp_python_wrap.cc) 

set_target_properties(seqpp PROPERTIES PREFIX "" SUFFIX ".so")

target_link_libraries(seqpp ${PYTHON_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY} ${LUA_LIBRARIES} ${SAMPLERATE_LIBRARIES} ${SNDFILE_LIBRARIES} ${JACK_LIBRARIES})

include_directories(${JASS_INCLUDE_DIRS})
include_directories(${PROJECT_BINARY_DIR})

install(TARGETS seqpp LIBRARY DESTINATION lib/lua/5.1/)

