cmake_minimum_required (VERSION 2.6)
#set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_BUILD_TYPE Release)
project (seqpp)

cmake_policy(SET CMP0002 OLD)

set(PROJECT_VERSION "0.1.0")
set(ARCHIVE_NAME ${CMAKE_PROJECT_NAME}-${PROJECT_VERSION})
add_custom_target(dist
    COMMAND git archive --prefix=${ARCHIVE_NAME}/ HEAD
        | bzip2 > ${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.bz2
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_subdirectory(lua)
add_subdirectory(python)

#add_definitions(-O3 -ffast-math -march=native -mtune=native -funsafe-math-optimizations -funroll-loops)
#add_definitions(-pg)

#set(CMAKE_EXE_LINKER_FLAGS -pg)

find_package(PkgConfig)
find_package(Boost COMPONENTS thread program_options system REQUIRED)

pkg_check_modules(SAMPLERATE samplerate)
pkg_check_modules(SNDFILE sndfile)
pkg_check_modules(JACK jack)

include_directories(. ${PROJECT_SOURCE_DIR}/seqpp ${PYTHON_INCLUDE_DIRS} ${Boost_PROGRAM_OPTIONS_INCLUDE_DIRS} ${Boost_SYSTEM_INCLUDE_DIRS} ${Boost_THREAD_INCLUDE_DIRS} ${LUA_INCLUDE_DIR} ${SAMPLERATE_INCLUDE_DIRS} ${SNDFILE_INCLUDE_DIRS} ${JACK_INCLUDE_DIRS})
link_directories(${Boost_THREAD_LIBRARY_DIRS} ${LUA_LIBRARY_DIRS} ${SAMPLERATE_LIBRARY_DIRS} ${SNDFILE_LIBRARY_DIRS} ${JACK_LIBRARY_DIRS})

include_directories(${JASS_INCLUDE_DIRS})
include_directories(${PROJECT_BINARY_DIR})

