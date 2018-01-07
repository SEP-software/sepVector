cmake_minimum_required(VERSION 2.8)
project(sepVector-lib))
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCES float1DReg.cc	float2DReg.cc	float3DReg.cc	floatHyper.cc
  )
set(INCLUDES 	float1DReg.h	float2DReg.h	float3DReg.h	floatHyper.h
  )

add_library(gieeBase  ${SOURCES} ${INCLUDES})
install(FILES ${INCLUDES} DESTINATION include)
install(TARGETS sepVector DESTINATION lib)
