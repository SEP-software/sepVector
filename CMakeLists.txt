project(sepVector) 
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# configure a header file to pass some of the CMake settings
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(sepVector_MAJOR_VERSION 0)
set(sepVector_MINOR_VERSION 1)
set(sepVector_VERSION_STRING
  ${sepVector_MAJOR_VERSION}.${sepVector_MINOR_VERSION})

 SET(sepVector_DIRNAME_lib     "lib")
 SET(sepVector_DIRNAME_include "include")




# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")


include(CheckCXXCompilerFlag)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

enable_language(C CXX)


FIND_PACKAGE(hypercube NO_MODULE REQUIRED)
INCLUDE_DIRECTORIES(${hypercube_DIRNAME_include})




 SET(sepVector_DIRNAME_lib     "lib")
 SET(sepVector_DIRNAME_include "include")
  INCLUDE(CMakePackageConfigHelpers)

  CONFIGURE_PACKAGE_CONFIG_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/sepVectorConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/sepVectorConfig.cmake"
  INSTALL_DESTINATION
    ${sepVector_DIRNAME_lib}
  PATH_VARS
    sepVector_DIRNAME_include
  )
  
  INSTALL(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/sepVectorConfig.cmake
  DESTINATION
    lib
  )


  INSTALL(
  EXPORT
    sepVectorExports
  DESTINATION
    ${sepVector_DIRNAME_lib}
  )
  
add_subdirectory(lib)
#add_subdirectory(python)
#add_subdirectory(env-modules)
