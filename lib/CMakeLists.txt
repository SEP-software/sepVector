cmake_minimum_required(VERSION 3.4)
project(sepVector-lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/xtensor/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/xtl/include)

# find_package(Boost 1.40 COMPONENTS program_options unit_test_framework
# REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
include_directories(${TBB_INCLUDE_DIRS})

set(SOURCES
    Vector.cc
    float1DReg.cc
    float2DReg.cc
    float3DReg.cc
    floatHyper.cc
    float4DReg.cc
    regVector.cc
    regSpace.cc
    rectFilter.cc
    float5DReg.cc
    float6DReg.cc
    float7DReg.cc
    byteTensor.cc
    complexTensor.cc
    complexDoubleTensor.cc
    doubleTensor.cc
    floatTensor.cc
    intTensor.cc
    shortTensor.cc)

set(SOURCES
    ${SOURCES}
    intHyper.cc
    int1DReg.cc
    int2DReg.cc
    int3DReg.cc
    int4DReg.cc
    int5DReg.cc
    int6DReg.cc)

set(SOURCES
    ${SOURCES}
    byteHyper.cc
    byte1DReg.cc
    byte2DReg.cc
    byte3DReg.cc
    byte4DReg.cc
    byte5DReg.cc
    byte6DReg.cc)

set(SOURCES
    ${SOURCES}
    complexHyper.cc
    complex1DReg.cc
    complex2DReg.cc
    complex3DReg.cc
    complex4DReg.cc
    complex5DReg.cc
    complex6DReg.cc
    complex7DReg.cc)

set(SOURCES
    ${SOURCES}
    doubleHyper.cc
    double1DReg.cc
    double2DReg.cc
    double3DReg.cc
    double4DReg.cc
    double5DReg.cc
    double6DReg.cc
    double7DReg.cc)

set(SOURCES
    ${SOURCES}
    complexDoubleHyper.cc
    complexDouble1DReg.cc
    complexDouble2DReg.cc
    complexDouble3DReg.cc
    complexDouble4DReg.cc
    complexDouble5DReg.cc
    complexDouble6DReg.cc
    complexDouble7DReg.cc)

set(SOURCES ${SOURCES} short1DReg.cc shortHyper.cc)

set(INCLUDES
    Vector.h
    regSpace.h
    rectFilter.h
    floatTensor.h
    byteTensor.h
    complexTensor.h
    complexDoubleTensor.h
    doubleTensor.h
    intTensor.h
    shortTensor.h
    float1DReg.h
    float2DReg.h
    float3DReg.h
    floatHyper.h
    float4DReg.h
    float5DReg.h
    float6DReg.h
    float7DReg.h
    intHyper.h
    int1DReg.h
    int2DReg.h
    int3DReg.h
    int4DReg.h
    int5DReg.h
    int6DReg.h
    byteHyper.h
    byte1DReg.h
    byte2DReg.h
    byte3DReg.h
    byte4DReg.h
    byte5DReg.h
    byte6DReg.h
    complexHyper.h
    complex1DReg.h
    complex2DReg.h
    complex3DReg.h
    complex4DReg.h
    complex5DReg.h
    complex6DReg.h
    complex7DReg.h
    complexDoubleHyper.h
    complexDouble1DReg.h
    complexDouble2DReg.h
    complexDouble3DReg.h
    complexDouble4DReg.h
    complexDouble5DReg.h
    complexDouble6DReg.h
    complexDouble7DReg.h
    doubleHyper.h
    double1DReg.h
    double2DReg.h
    double3DReg.h
    double4DReg.h
    double5DReg.h
    double6DReg.h
    double7DReg.h
    regVector.h
    short1DReg.h
    shortHyper.h)
set(SEPVECTOR_INTERNAL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_library(sepVector ${SOURCES} ${INCLUDES})

target_include_directories(
  sepVector INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/..>

  $<INSTALL_INTERFACE:include>
      
         )

target_link_libraries(sepVector hypercube xtensor ${TBB_LIBRARIES})

install(FILES ${INCLUDES} DESTINATION include)
install(
  TARGETS sepVector
  DESTINATION lib
  EXPORT sepVectorTargets)

if(BUILD_TEST)
  add_executable(testRegSpace testRegSpace.cc)
  target_link_libraries(testRegSpace sepVector gtest gtest_main gtest)
  add_test(NAME testRegSpace COMMAND testRegSpace)

endif(BUILD_TEST)
