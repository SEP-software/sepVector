# Install script for directory: /Users/bob/Src/sepVector/src/lib

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/opt/SEP")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/Users/bob/Src/sepVector/src/lib/Vector.h"
    "/Users/bob/Src/sepVector/src/lib/superVec.h"
    "/Users/bob/Src/sepVector/src/lib/regSpace.h"
    "/Users/bob/Src/sepVector/src/lib/float1DReg.h"
    "/Users/bob/Src/sepVector/src/lib/float2DReg.h"
    "/Users/bob/Src/sepVector/src/lib/float3DReg.h"
    "/Users/bob/Src/sepVector/src/lib/floatHyper.h"
    "/Users/bob/Src/sepVector/src/lib/float4DReg.h"
    "/Users/bob/Src/sepVector/src/lib/float5DReg.h"
    "/Users/bob/Src/sepVector/src/lib/float6DReg.h"
    "/Users/bob/Src/sepVector/src/lib/intHyper.h"
    "/Users/bob/Src/sepVector/src/lib/int1DReg.h"
    "/Users/bob/Src/sepVector/src/lib/int2DReg.h"
    "/Users/bob/Src/sepVector/src/lib/int3DReg.h"
    "/Users/bob/Src/sepVector/src/lib/int4DReg.h"
    "/Users/bob/Src/sepVector/src/lib/int5DReg.h"
    "/Users/bob/Src/sepVector/src/lib/int6DReg.h"
    "/Users/bob/Src/sepVector/src/lib/byteHyper.h"
    "/Users/bob/Src/sepVector/src/lib/byte1DReg.h"
    "/Users/bob/Src/sepVector/src/lib/byte2DReg.h"
    "/Users/bob/Src/sepVector/src/lib/byte3DReg.h"
    "/Users/bob/Src/sepVector/src/lib/byte4DReg.h"
    "/Users/bob/Src/sepVector/src/lib/byte5DReg.h"
    "/Users/bob/Src/sepVector/src/lib/byte6DReg.h"
    "/Users/bob/Src/sepVector/src/lib/complexHyper.h"
    "/Users/bob/Src/sepVector/src/lib/complex1DReg.h"
    "/Users/bob/Src/sepVector/src/lib/complex2DReg.h"
    "/Users/bob/Src/sepVector/src/lib/complex3DReg.h"
    "/Users/bob/Src/sepVector/src/lib/complex4DReg.h"
    "/Users/bob/Src/sepVector/src/lib/complex5DReg.h"
    "/Users/bob/Src/sepVector/src/lib/complex6DReg.h"
    "/Users/bob/Src/sepVector/src/lib/doubleHyper.h"
    "/Users/bob/Src/sepVector/src/lib/double1DReg.h"
    "/Users/bob/Src/sepVector/src/lib/double2DReg.h"
    "/Users/bob/Src/sepVector/src/lib/double3DReg.h"
    "/Users/bob/Src/sepVector/src/lib/double4DReg.h"
    "/Users/bob/Src/sepVector/src/lib/double5DReg.h"
    "/Users/bob/Src/sepVector/src/lib/double6DReg.h"
    "/Users/bob/Src/sepVector/src/lib/regVector.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/bob/Src/sepVector/src/lib/libsepVector.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsepVector.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsepVector.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsepVector.a")
  endif()
endif()

