project(sepVector-python)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# find_package(NumPy REQUIRED)

set(PYTHON_DIR "lib/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../lib")

find_package(Boost 1.40 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

pybind11_add_module(
  pySepVector
  MODULE
  pyBase.cpp
  pyComplexDR.cpp
  pyDoubleR.cpp
  pyFloatT.cpp
  pyIntT.cpp
  pyDoubleT.cpp
  pyComplexT.cpp
  pyComplexDT.cpp
  pyShortT.cpp
  pyRect.cpp
  pyShortR.cpp
  pyByteR.cpp
  pyByteT.cpp
  pyComplexR.cpp
  pyFloatR.cpp
  pyIntR.cpp
  pyReg.cpp
  pyVector.cpp)

target_include_directories(
  pySepVector
  PUBLIC ${PYTHON_INCLUDE_DIR}
         # $<INSTALL_INTERFACE:${pybind11_INCLUDE_DIR}>
         $<INSTALL_INTERFACE:../external/hypercube/external/pybind11/include>
         $<INSTALL_INTERFACE:include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}../src>)
if(BUILD_TEST)
  add_test(
    NAME sepVector
    COMMAND
      ${CMAKE_COMMAND} -E env
      PYTHONPATH=${CMAKE_CURRENT_BINARY_DIR}/../external/hypercube/python:${CMAKE_CURRENT_SOURCE_DIR}/../external/hypercube/python:${CMAKE_CURRENT_BINARY_DIR}:${CMAKE_CURRENT_SOURCE_DIR}/../external/python-solver/GenericSolver/python
      LD_LIBRARY_PATH=${CMAKE_CURRENT_BINARY_DIR}/../external/hypercube/python:${CMAKE_CURRENT_SOURCE_DIR}/../external/hypercube/python:${CMAKE_CURRENT_BINARY_DIR}
      ${PYTHON_EXECUTABLE} -m test_SepVector
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

  add_test(
    NAME sepIrregVector
    COMMAND
      ${CMAKE_COMMAND} -E env
      PYTHONPATH=${CMAKE_CURRENT_BINARY_DIR}/../external/hypercube/python:${CMAKE_CURRENT_SOURCE_DIR}/../external/hypercube/python:${CMAKE_CURRENT_BINARY_DIR}:${CMAKE_CURRENT_SOURCE_DIR}/../external/python-solver/GenericSolver/python
      LD_LIBRARY_PATH=${CMAKE_CURRENT_BINARY_DIR}/../external/hypercube/python:${CMAKE_CURRENT_SOURCE_DIR}/../external/hypercube/python:${CMAKE_CURRENT_BINARY_DIR}
      ${PYTHON_EXECUTABLE} -m test_SepIrregVector
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif(BUILD_TEST)

target_link_libraries(pySepVector PRIVATE sepVector hypercube)
install(
  TARGETS pySepVector
  DESTINATION ${PYTHON_DIR}
  EXPORT sepVectorTargets)
install(FILES SepTensor.py SepVector.py SepIrregVector.py DESTINATION ${PYTHON_DIR})
