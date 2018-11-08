cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

if(NOT SUBPACKAGE) 
  option(BUILD_PYTHON "Build python interfaces" ON)
endif(NOT SUBPACKAGE)
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
find_package(NumPy REQUIRED)
find_package(TBB REQUIRED)
set(sepVector_MAJOR_VERSION 0)
set(sepVector_MINOR_VERSION 2)
set(sepVector_VERSION_STRING
    ${sepVector_MAJOR_VERSION}.${sepVector_MINOR_VERSION})

set(sepVector_DIRNAME_lib "lib")
set(sepVector_DIRNAME_include "include")

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

#
if(NOT TARGET hypercube)
  execute_process(COMMAND git submodule update --init --recursive --
                          external/hypercube
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  add_subdirectory(external/hypercube)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/hypercube/lib)
endif(NOT TARGET hypercube)

include_directories("${PROJECT_BINARY_DIR}")

set(sepVector_DIRNAME_lib "lib")
set(sepVector_DIRNAME_include "include")
set(sepVector_DIRNAME_cmake "cmake")
include(CMakePackageConfigHelpers)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/sepVectorConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/sepVectorConfig.cmake"
  INSTALL_DESTINATION
  ${sepVector_DIRNAME_cmake}
  PATH_VARS
  sepVector_DIRNAME_include
  sepVector_DIRNAME_lib)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/sepVectorConfig.cmake
        DESTINATION cmake)

install(EXPORT sepVectorExports DESTINATION cmake)

add_subdirectory(lib)
if(BUILD_PYTHON)
  add_subdirectory(python)
endif(BUILD_PYTHON)
add_subdirectory(env-modules)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${sepVector_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${sepVector_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_NAME "sepVector")
set(CPACK_PACKAGE_CONTACT "Robert Clapp")
include(CPack)
