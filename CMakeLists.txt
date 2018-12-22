cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

if(NOT SUBPACKAGE)
  option(BUILD_PYTHON "Build python interfaces" ON)
option(INSTALL_CMAKE_ENV "Install cmake build environment" ON)
endif(NOT SUBPACKAGE)
option(BUILD_DOUBLE "Build double support" ON)
option(BUILD_INT "Build int support" ON)
option(BUILD_COMPLEX "Build complex support" ON)
option(BUILD_BYTE "Build byte support" ON)
option(BUILD_SHORT "Build short support" ON)

if(BUILD_DOUBLE)
    set(USE_DOUBLE true)
endif(BUILD_DOUBLE)


if(BUILD_COMPLEX)
    set(USE_COMPLEX true)
endif(BUILD_COMPLEX)


if(BUILD_INT)
    set(USE_INT true)
endif(BUILD_INT)


if(BUILD_BYTE)
    set(USE_BYTE true)
endif(BUILD_BYTE)
if(BUILD_SHORT)
    set(USE_SHORT true)
endif(BUILD_SHORT)
set(SUBPACKAGE true)

project(sepVector LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE True)

project(sepVector)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# configure a header file to pass some of the CMake settings
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(Boost REQUIRED)
find_package(TBB REQUIRED)
set(sepVector_MAJOR_VERSION 0)
set(sepVector_MINOR_VERSION 2)
set(sepVector_VERSION_STRING
    ${sepVector_MAJOR_VERSION}.${sepVector_MINOR_VERSION})

set(sepVector_DIRNAME_lib "lib")
set(sepVector_DIRNAME_include "include")

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)


if(NOT TARGET hypercube)
  execute_process(COMMAND git submodule update --init --recursive --
                          external/hypercube
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  add_subdirectory(external/hypercube)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/hypercube/lib)
endif(NOT TARGET hypercube)


add_subdirectory(external/pySolver/GenericSolver)


configure_file("${PROJECT_SOURCE_DIR}/sepVectorConfig.h.in"
               "${PROJECT_BINARY_DIR}/sepVectorConfig.h")

include_directories("${PROJECT_BINARY_DIR}")

set(sepVector_DIRNAME_lib "lib")
set(sepVector_DIRNAME_include "include")
set(sepVector_DIRNAME_cmake "lib/cmake")
include(CMakePackageConfigHelpers)

if(NOT SUPPORT_LIBRARIES_BUILD)
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/sepVectorConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/sepVectorConfig.cmake"
  INSTALL_DESTINATION
  ${sepVector_DIRNAME_cmake}
  PATH_VARS
  sepVector_DIRNAME_include
  sepVector_DIRNAME_lib)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/sepVectorConfig.cmake
        DESTINATION lib/cmake)

if(NOT INSTALL_CMAKE_ENV)
install(EXPORT sepVectorExports DESTINATION lib/cmake)
endif(NOT INSTALL_CMAKE_ENV)
add_subdirectory(env-modules)
endif(NOT SUPPORT_LIBRARIES_BUILD)

add_subdirectory(lib)
if(BUILD_PYTHON)
  add_subdirectory(SEP)
endif(BUILD_PYTHON)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${sepVector_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${sepVector_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_NAME "sepVector")
set(CPACK_PACKAGE_CONTACT "Robert Clapp")
include(CPack)
