project(sepVector) 
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# configure a header file to pass some of the CMake settings
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(Boost REQUIRED)


find_package(NumPy  REQUIRED)
FIND_PACKAGE(TBB REQUIRED)
set(sepVector_MAJOR_VERSION 0)
set(sepVector_MINOR_VERSION 2)
set(sepVector_VERSION_STRING
  ${sepVector_MAJOR_VERSION}.${sepVector_MINOR_VERSION})

 SET(sepVector_DIRNAME_lib     "lib")
 SET(sepVector_DIRNAME_include "include")

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

#FIND_PACKAGE(hypercube)
#if(hypercube_FOUND)
#  message("Found hypercube")
#  INCLUDE_DIRECTORIES(${hypercube_DIRNAME_include})
#  link_directories(hypercube_DIRNAME_lib)
#else(hypercube_FOUND)
#   message("Unable to find hypercube")

    # we have a submodule setup for foo, assume it is under external/foo
    # now we need to clone this submodule
if(NOT TARGET hypercube)

    execute_process(COMMAND git submodule update --init --recursive -- external/hypercube
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    add_subdirectory(external/hypercube)
    INCLUDE_DIRECTORIES(external/hypercube/lib)
endif(NOT TARGET hypercube)
#endif(hypercube_FOUND)



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






 SET(sepVector_DIRNAME_lib     "lib")
 SET(sepVector_DIRNAME_include "include")
 SET(sepVector_DIRNAME_cmake "cmake")
  INCLUDE(CMakePackageConfigHelpers)

  CONFIGURE_PACKAGE_CONFIG_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/sepVectorConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/sepVectorConfig.cmake"
  INSTALL_DESTINATION
    ${sepVector_DIRNAME_cmake}
  PATH_VARS
    sepVector_DIRNAME_include
    sepVector_DIRNAME_lib
  )
  
  INSTALL(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/sepVectorConfig.cmake
  DESTINATION
    cmake
  )


  INSTALL(
  EXPORT
    sepVectorExports
  DESTINATION
   cmake
  )
  
add_subdirectory(lib)
add_subdirectory(python)
add_subdirectory(env-modules)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${sepVector_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${sepVector_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_NAME "sepVector")
set(CPACK_PACKAGE_CONTACT "Robert Clapp")
include(CPack)

