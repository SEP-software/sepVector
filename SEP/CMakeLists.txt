project(sepVector-python)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)
find_package(PythonInterp 3 REQUIRED)
find_package(NumPy REQUIRED)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../lib")
find_package(pybind11)
if(pybind11_FOUND)

  find_package(Boost 1.40 REQUIRED)

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

else(pybind11_FOUND)
  message("Did not find pybid11")
endif(pybind11_FOUND)
