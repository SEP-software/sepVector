project(sepVector-python)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)




include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../lib")
find_package(pybind11)  
if (pybind11_FOUND)
MESSAGE("found pybind")
include_directories(${PYTHON_INCLUDE_DIR})
include_directories(${pybind11_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
FIND_PACKAGE( Boost 1.40 COMPONENTS program_options unit_test_framework REQUIRED )


pybind11_add_module(pySepVector MODULE pyVector.cpp)
target_link_libraries(pySepVector PRIVATE  sepVector hypercube)
install( TARGETS pySepVector DESTINATION lib/python)
install(FILES SepVector.py DESTINATION lib/python)



else(pybind11_FOUND)
MESSAGE("Did not find pybid11")
endif(pybind11_FOUND)
