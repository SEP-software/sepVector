project(sepVector-python)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)



# This is a CMake example for Python

FIND_PACKAGE(SWIG REQUIRED)
if(SWIG_FOUND)
MESSAGE("found SWIG building python interface")
INCLUDE(${SWIG_USE_FILE})

FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
FIND_PACKAGE( Boost 1.40 COMPONENTS program_options unit_test_framework REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
INCLUDE_DIRECTORIES(${PYTHON_NUMPY_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
INCLUDE_DIRECTORIES(${GENERIC_EXPORT_INC_DIRS})

SET(CMAKE_SWIG_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(numPyVec_int.i PROPERTIES CPLUSPLUS ON)
SWIG_ADD_MODULE(numPyVec_int  python  numPyVec_int.i numPyVec.cc)




SWIG_LINK_LIBRARIES(numPyVec_int sepVector hypercube  ${PYTHON_LIBRARIES})



add_library(numPyVec numPyVec.cc numPyVec.h)



install( TARGETS _numPyVec_int DESTINATION lib/python)

install( TARGETS numPyVec DESTINATION lib)


install( FILES  ${CMAKE_CURRENT_BINARY_DIR}/numPyVec_int.py  DESTINATION lib/python)



else(SWIG_FOUND)
MESSAGE("Did not find SWIG, not building python interface")
endif(SWIG_FOUND)
