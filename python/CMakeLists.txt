project(sepVector-python)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)
find_package(PythonInterp 3 REQUIRED)
find_package (Python3 COMPONENTS Interpreter Development )

#find_package(NumPy REQUIRED)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../lib")

find_package(Boost 1.40 REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR})

pybind11_add_module(pySepVector MODULE pyVector.cpp)

target_include_directories(
  pySepVector
  PUBLIC ${PYTHON_INCLUDE_DIR}
         ${pybind11_INCLUDE_DIR}
         ${PYTHON_INCLUDE_PATH}
         $<INSTALL_INTERFACE:include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}../src>)

target_link_libraries(pySepVector PRIVATE sepVector)
install(TARGETS pySepVector DESTINATION lib/python EXPORT sepVectorTargets)
install(FILES SepVector.py DESTINATION lib/python)
