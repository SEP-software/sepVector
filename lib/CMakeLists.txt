cmake_minimum_required(VERSION 2.8)
project(sepVector-lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
FIND_PACKAGE( Boost 1.40 COMPONENTS program_options unit_test_framework REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


set(SOURCES Vector.cc float1DReg.cc	float2DReg.cc	float3DReg.cc	floatHyper.cc float4DReg.cc
  )
set(INCLUDES  Vector.h	float1DReg.h	float2DReg.h	float3DReg.h	floatHyper.h float4DReg.h
  )

add_library(sepVector  ${SOURCES} ${INCLUDES})
install(FILES ${INCLUDES} DESTINATION include)
install(TARGETS sepVector DESTINATION lib EXPORT sepVectorExports )
