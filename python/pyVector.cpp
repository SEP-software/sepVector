#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "byte1DReg.h"
#include "byte2DReg.h"
#include "byte3DReg.h"
#include "byte4DReg.h"
#include "byte5DReg.h"
#include "byte6DReg.h"
#include "double1DReg.h"
#include "double2DReg.h"
#include "double3DReg.h"
#include "double4DReg.h"
#include "double5DReg.h"
#include "double6DReg.h"
#include "float1DReg.h"
#include "float2DReg.h"
#include "float3DReg.h"
#include "float4DReg.h"
#include "float5DReg.h"
#include "float6DReg.h"
#include "int1DReg.h"
#include "int2DReg.h"
#include "int3DReg.h"
#include "int4DReg.h"
#include "int5DReg.h"
#include "int6DReg.h"
#include "regSpace.h"
namespace py = pybind11;
namespace SEP {
using namespace SEP;

PYBIND11_MODULE(pySepVector, clsVector) {
  py::class_<Vector, std::shared_ptr<Vector>>(clsVector, "Vector")
      .def(py::init<>(), "Initlialize a new Vector (don't use this");

  py::class_<regSpace, std::shared_ptr<regSpace>>(clsVector, "regSpace")
      .def(py::init<>(), "Initlialize a new regSpace (don't use this")
      .def("getHyper",
           (std::shared_ptr<hypercube>(regSpace::*)()) & regSpace::getHyper,
           "Get the hypercube")
      .def_property("_hyper", &regSpace::getHyper, &regSpace::setHyper,
                    py::return_value_policy::reference)
      .def("getVoidPtr", (void *(regSpace::*)()) & regSpace::getVoidPtr,
           "Get a void ptr")
      .def("getEsize", (int (regSpace::*)()) & regSpace::getEsize,
           "Get the element size");

  py::class_<floatHyper, Vector, regSpace, std::shared_ptr<floatHyper>>(
      clsVector,
      "floatHyper")  //
      .def(py::init<>(), "Initlialize a new Float Hyper (don't use this")
      .def("getSpaceOnly", (bool (floatHyper::*)()) & floatHyper::getSpaceOnly,
           "Check to see if this only a description of the vector space")

      .def("setData", (void (floatHyper::*)(float *)) & floatHyper::setData,
           "Set the data pointer")
      .def("getVals", (float *(floatHyper::*)()) & floatHyper::getVals,
           "Get the data pointer")

      .def("isDifferent",
           (bool (floatHyper::*)(std::shared_ptr<floatHyper>)) &
               floatHyper::isDifferent,
           "Check to  see if two vectors are different")

      .def_property("_vals", &floatHyper::getVals, &floatHyper::setData,
                    py::return_value_policy::reference)

      .def("createMask",
           (void (floatHyper::*)(const float, const float)) &
               floatHyper::createMask,
           "Create a mask weight")
      .def(
          "add",
          (void (floatHyper::*)(std::shared_ptr<floatHyper>)) & floatHyper::add,
          "Add two vectors")
      .def("scale", (void (floatHyper::*)(const double)) & floatHyper::scale,
           "Scale a vector")

      .def("scaleAdd",
           (void (floatHyper::*)(std::shared_ptr<floatHyper>, const double,
                                 const double)) &
               floatHyper::scaleAdd,
           "vec=vec*sc1+vec2*sc2")
      .def("calcCheckSum",
           (double (floatHyper::*)() const) & floatHyper::calcCheckSum,
           "Calculate checksum of a vector")

      .def("norm",
           (double (floatHyper::*)(const int n) const) & floatHyper::norm,
           "Calculate n-norm of a vector")
      .def("zero", (void (floatHyper::*)()) & floatHyper::zero,
           "Fill a vector with zero")

      .def("signum", (void (floatHyper::*)()) & floatHyper::signum,
           "Fill a vector with it's signum")
      .def("rand", (void (floatHyper::*)()) & floatHyper::random,
           "Fill a vector with random number")

      .def("mult",
           (void (floatHyper::*)(std::shared_ptr<floatHyper>)) &
               floatHyper::mult,
           "vec=vec*vec2")
      .def("dot",
           (double (floatHyper::*)(std::shared_ptr<floatHyper>) const) &
               floatHyper::dot,
           "Calculate dot product")
      .def("checkSame",
           (bool (floatHyper::*)(const std::shared_ptr<floatHyper>) const) &
               floatHyper::checkSame,
           "Check to make sure the vectors exist in the same space");

  py::class_<float1DReg, floatHyper, std::shared_ptr<float1DReg>>(
      clsVector, "float1DReg", py::buffer_protocol())
      .def(py::init<const int>(), "Initialize giving size")
      .def(py::init<const axis &>(), "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")

      .def("clone",
           (std::shared_ptr<float1DReg>(float1DReg::*)() const) &
               float1DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<float1DReg>(float1DReg::*)() const) &
               float1DReg::cloneSpace,
           "Make a copy of the vector space")
      .def("allocate", (void (float1DReg::*)()) & float1DReg::allocate,
           "Allocate the array")

      .def_buffer([](float1DReg &m) -> py::buffer_info {
        return py::buffer_info(m.getVals(), sizeof(float),
                               py::format_descriptor<float>::format(), 1,
                               {m.getHyper()->getAxis(1).n}, {sizeof(float)});
      });
  py::class_<float2DReg, floatHyper, std::shared_ptr<float2DReg>>(
      clsVector, "float2DReg", py::buffer_protocol())
      .def(py::init<const int, const int>(), "Initialize giving size")
      .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def("clone",
           (std::shared_ptr<float2DReg>(float2DReg::*)() const) &
               float2DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<float2DReg>(float2DReg::*)() const) &
               float2DReg::cloneSpace,
           "Make a copy of the vector space")
      .def("allocate", (void (float2DReg::*)()) & float2DReg::allocate,
           "Allocate the array")

      .def_buffer([](float2DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(float), py::format_descriptor<float>::format(),
            2, {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
            {sizeof(float) * m.getHyper()->getAxis(1).n, sizeof(float)});
      });

  py::class_<float3DReg, floatHyper, std::shared_ptr<float3DReg>>(
      clsVector, "float3DReg", py::buffer_protocol())
      .def(py::init<const int, const int, const int>(),
           "Initialize giving size")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def(py::init<const axis &, const axis &, const axis &>(),
           "Initialize from an axis")
      .def("allocate", (void (float3DReg::*)()) & float3DReg::allocate,
           "Allocate the array")
      .def("clone",
           (std::shared_ptr<float3DReg>(float3DReg::*)() const) &
               float3DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<float3DReg>(float3DReg::*)() const) &
               float3DReg::cloneSpace,
           "Make a copy of the vector space")
      .def_buffer([](float3DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(float), py::format_descriptor<float>::format(),
            3,
            {m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
             m.getHyper()->getAxis(1).n},
            {sizeof(float) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n,
             sizeof(float) * m.getHyper()->getAxis(1).n, sizeof(float)});
      });

  py::class_<float4DReg, floatHyper, std::shared_ptr<float4DReg>>(
      clsVector, "float4DReg", py::buffer_protocol())
      .def(py::init<const int, const int, const int, const int>(),
           "Initialize giving size")
      .def(py::init<const axis &, const axis &, const axis &, const axis &>(),
           "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def("allocate", (void (float4DReg::*)()) & float4DReg::allocate,
           "Allocate the array")
      .def("clone",
           (std::shared_ptr<float4DReg>(float4DReg::*)() const) &
               float4DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<float4DReg>(float4DReg::*)() const) &
               float4DReg::cloneSpace,
           "Make a copy of the vector space")
      .def_buffer([](float4DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(float), py::format_descriptor<float>::format(),
            4,
            {m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
             m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
            {sizeof(float) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
             sizeof(float) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n,
             sizeof(float) * m.getHyper()->getAxis(1).n, sizeof(float)});
      });
  py::class_<doubleHyper, regSpace, std::shared_ptr<doubleHyper>>(
      clsVector,
      "doubleHyper")  //
      .def(py::init<>(), "Initlialize a new double Hyper (don't use this")
      .def("getSpaceOnly",
           (bool (doubleHyper::*)()) & doubleHyper::getSpaceOnly,
           "Check to see if this only a description of the vector space")

      .def("setData", (void (doubleHyper::*)(double *)) & doubleHyper::setData,
           "Set the data pointer")
      .def("getVals", (double *(doubleHyper::*)()) & doubleHyper::getVals,
           "Get the data pointer")

      .def("isDifferent",
           (bool (doubleHyper::*)(std::shared_ptr<doubleHyper>)) &
               doubleHyper::isDifferent,
           "Check to  see if two vectors are different")

      .def_property("_vals", &doubleHyper::getVals, &doubleHyper::setData,
                    py::return_value_policy::reference)

      .def("createMask",
           (void (doubleHyper::*)(const double, const double)) &
               doubleHyper::createMask,
           "Create a mask weight")
      .def("add",
           (void (doubleHyper::*)(std::shared_ptr<doubleHyper>)) &
               doubleHyper::add,
           "Add two vectors")
      .def("scale", (void (doubleHyper::*)(const double)) & doubleHyper::scale,
           "Scale a vector")

      .def("scaleAdd",
           (void (doubleHyper::*)(std::shared_ptr<doubleHyper>, const double,
                                  const double)) &
               doubleHyper::scaleAdd,
           "vec=vec*sc1+vec2*sc2")
      .def("calcCheckSum",
           (double (doubleHyper::*)() const) & doubleHyper::calcCheckSum,
           "Calculate checksum of a vector")

      .def("norm",
           (double (doubleHyper::*)(const int n) const) & doubleHyper::norm,
           "Calculate n-norm of a vector")
      .def("zero", (void (doubleHyper::*)()) & doubleHyper::zero,
           "Fill a vector with zero")

      .def("signum", (void (doubleHyper::*)()) & doubleHyper::signum,
           "Fill a vector with it's signum")
      .def("rand", (void (doubleHyper::*)()) & doubleHyper::random,
           "Fill a vector with random number")

      .def("mult",
           (void (doubleHyper::*)(std::shared_ptr<doubleHyper>)) &
               doubleHyper::mult,
           "vec=vec*vec2")
      .def("dot",
           (double (doubleHyper::*)(std::shared_ptr<doubleHyper>) const) &
               doubleHyper::dot,
           "Calculate dot product")
      .def("checkSame",
           (bool (doubleHyper::*)(const std::shared_ptr<doubleHyper>) const) &
               doubleHyper::checkSame,
           "Check to make sure the vectors exist in the same space");

  py::class_<double1DReg, doubleHyper, std::shared_ptr<double1DReg>>(
      clsVector, "double1DReg", py::buffer_protocol())
      .def(py::init<const int>(), "Initialize giving size")
      .def(py::init<const axis &>(), "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")

      .def("clone",
           (std::shared_ptr<double1DReg>(double1DReg::*)() const) &
               double1DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<double1DReg>(double1DReg::*)() const) &
               double1DReg::cloneSpace,
           "Make a copy of the vector space")
      .def("allocate", (void (double1DReg::*)()) & double1DReg::allocate,
           "Allocate the array")

      .def_buffer([](double1DReg &m) -> py::buffer_info {
        return py::buffer_info(m.getVals(), sizeof(double),
                               py::format_descriptor<double>::format(), 1,
                               {m.getHyper()->getAxis(1).n}, {sizeof(double)});
      });
  py::class_<double2DReg, doubleHyper, std::shared_ptr<double2DReg>>(
      clsVector, "double2DReg", py::buffer_protocol())
      .def(py::init<const int, const int>(), "Initialize giving size")
      .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def("clone",
           (std::shared_ptr<double2DReg>(double2DReg::*)() const) &
               double2DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<double2DReg>(double2DReg::*)() const) &
               double2DReg::cloneSpace,
           "Make a copy of the vector space")
      .def("allocate", (void (double2DReg::*)()) & double2DReg::allocate,
           "Allocate the array")

      .def_buffer([](double2DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(double),
            py::format_descriptor<double>::format(), 2,
            {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
            {sizeof(double) * m.getHyper()->getAxis(1).n, sizeof(double)});
      });

  py::class_<double3DReg, doubleHyper, std::shared_ptr<double3DReg>>(
      clsVector, "double3DReg", py::buffer_protocol())
      .def(py::init<const int, const int, const int>(),
           "Initialize giving size")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def(py::init<const axis &, const axis &, const axis &>(),
           "Initialize from an axis")
      .def("allocate", (void (double3DReg::*)()) & double3DReg::allocate,
           "Allocate the array")
      .def("clone",
           (std::shared_ptr<double3DReg>(double3DReg::*)() const) &
               double3DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<double3DReg>(double3DReg::*)() const) &
               double3DReg::cloneSpace,
           "Make a copy of the vector space")
      .def_buffer([](double3DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(double),
            py::format_descriptor<double>::format(), 3,
            {m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
             m.getHyper()->getAxis(1).n},
            {sizeof(double) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n,
             sizeof(double) * m.getHyper()->getAxis(1).n, sizeof(double)});
      });

  py::class_<double4DReg, doubleHyper, std::shared_ptr<double4DReg>>(
      clsVector, "double4DReg", py::buffer_protocol())
      .def(py::init<const int, const int, const int, const int>(),
           "Initialize giving size")
      .def(py::init<const axis &, const axis &, const axis &, const axis &>(),
           "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def("allocate", (void (double4DReg::*)()) & double4DReg::allocate,
           "Allocate the array")
      .def("clone",
           (std::shared_ptr<double4DReg>(double4DReg::*)() const) &
               double4DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<double4DReg>(double4DReg::*)() const) &
               double4DReg::cloneSpace,
           "Make a copy of the vector space")
      .def_buffer([](double4DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(double),
            py::format_descriptor<double>::format(), 4,
            {m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
             m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
            {sizeof(double) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
             sizeof(double) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n,
             sizeof(double) * m.getHyper()->getAxis(1).n, sizeof(double)});
      });
  py::class_<double5DReg, doubleHyper, std::shared_ptr<double5DReg>>(
      clsVector, "double5DReg", py::buffer_protocol())
      .def(py::init<const int, const int, const int, const int, const int>(),
           "Initialize giving size")
      .def(py::init<const axis &, const axis &, const axis &, const axis &,
                    const axis &>(),
           "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def("allocate", (void (double5DReg::*)()) & double5DReg::allocate,
           "Allocate the array")
      .def("clone",
           (std::shared_ptr<double5DReg>(double5DReg::*)() const) &
               double5DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<double5DReg>(double5DReg::*)() const) &
               double5DReg::cloneSpace,
           "Make a copy of the vector space")
      .def_buffer([](double5DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(double),
            py::format_descriptor<double>::format(), 5,
            {m.getHyper()->getAxis(5).n, m.getHyper()->getAxis(4).n,
             m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
             m.getHyper()->getAxis(1).n},
            {sizeof(double) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                 m.getHyper()->getAxis(4).n,
             sizeof(double) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
             sizeof(double) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n,
             sizeof(double) * m.getHyper()->getAxis(1).n, sizeof(double)});
      });

  py::class_<double6DReg, doubleHyper, std::shared_ptr<double6DReg>>(
      clsVector, "double6DReg", py::buffer_protocol())
      .def(py::init<const int, const int, const int, const int, const int,
                    const int>(),
           "Initialize giving size")
      .def(py::init<const axis &, const axis &, const axis &, const axis &,
                    const axis &, const axis &>(),
           "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def("allocate", (void (double6DReg::*)()) & double6DReg::allocate,
           "Allocate the array")
      .def("clone",
           (std::shared_ptr<double6DReg>(double6DReg::*)() const) &
               double6DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<double6DReg>(double6DReg::*)() const) &
               double6DReg::cloneSpace,
           "Make a copy of the vector space")
      .def_buffer([](double6DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(double),
            py::format_descriptor<double>::format(), 6,
            {m.getHyper()->getAxis(6).n, m.getHyper()->getAxis(5).n,
             m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
             m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
            {sizeof(double) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                 m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n,
             sizeof(double) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                 m.getHyper()->getAxis(4).n,
             sizeof(double) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
             sizeof(double) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n,
             sizeof(double) * m.getHyper()->getAxis(1).n, sizeof(double)});
      });

  py::class_<intHyper, regSpace, std::shared_ptr<intHyper>>(clsVector,
                                                            "intHyper")  //
      .def(py::init<>(), "Initlialize a new int Hyper (don't use this")
      .def("getSpaceOnly", (bool (intHyper::*)()) & intHyper::getSpaceOnly,
           "Check to see if this only a description of the vector space")

      .def("setData", (void (intHyper::*)(int *)) & intHyper::setData,
           "Set the data pointer")
      .def("getVals", (int *(intHyper::*)()) & intHyper::getVals,
           "Get the data pointer")

      .def("isDifferent",
           (bool (intHyper::*)(std::shared_ptr<intHyper>)) &
               intHyper::isDifferent,
           "Check to  see if two vectors are different")

      .def_property("_vals", &intHyper::getVals, &intHyper::setData,
                    py::return_value_policy::reference)

      .def("add",
           (void (intHyper::*)(std::shared_ptr<intHyper>)) & intHyper::add,
           "Add two vectors")
      .def("scale", (void (intHyper::*)(const int)) & intHyper::scale,
           "Scale a vector")
      .def("scaleAdd",
           (void (intHyper::*)(std::shared_ptr<intHyper>, const int,
                               const int)) &
               intHyper::scaleAdd,
           "vec=vec*sc1+vec2*sc2")
      .def("calcCheckSum", (int (intHyper::*)() const) & intHyper::calcCheckSum,
           "Calculate checksum of a vector")
      .def("zero", (void (intHyper::*)()) & intHyper::zero,
           "Fill a vector with zero")

      .def("signum", (void (intHyper::*)()) & intHyper::signum,
           "Fill a vector with it's signum")
      .def("rand", (void (intHyper::*)()) & intHyper::random,
           "Fill a vector with random number")
      .def("mult",
           (void (intHyper::*)(std::shared_ptr<intHyper>)) & intHyper::mult,
           "vec=vec*vec2")
      .def("checkSame",
           (bool (intHyper::*)(const std::shared_ptr<intHyper>) const) &
               intHyper::checkSame,
           "Check to make sure the vectors exist in the same space");

  py::class_<int1DReg, intHyper, std::shared_ptr<int1DReg>>(
      clsVector, "int1DReg", py::buffer_protocol())
      .def(py::init<const int>(), "Initialize giving size")
      .def(py::init<const axis &>(), "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")

      .def("clone",
           (std::shared_ptr<int1DReg>(int1DReg::*)() const) & int1DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<int1DReg>(int1DReg::*)() const) &
               int1DReg::cloneSpace,
           "Make a copy of the vector space")
      .def("allocate", (void (int1DReg::*)()) & int1DReg::allocate,
           "Allocate the array")

      .def_buffer([](int1DReg &m) -> py::buffer_info {
        return py::buffer_info(m.getVals(), sizeof(int),
                               py::format_descriptor<int>::format(), 1,
                               {m.getHyper()->getAxis(1).n}, {sizeof(int)});
      });
  py::class_<int2DReg, intHyper, std::shared_ptr<int2DReg>>(
      clsVector, "int2DReg", py::buffer_protocol())
      .def(py::init<const int, const int>(), "Initialize giving size")
      .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def("clone",
           (std::shared_ptr<int2DReg>(int2DReg::*)() const) & int2DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<int2DReg>(int2DReg::*)() const) &
               int2DReg::cloneSpace,
           "Make a copy of the vector space")
      .def("allocate", (void (int2DReg::*)()) & int2DReg::allocate,
           "Allocate the array")

      .def_buffer([](int2DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(int), py::format_descriptor<int>::format(), 2,
            {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
            {sizeof(int) * m.getHyper()->getAxis(1).n, sizeof(int)});
      });

  py::class_<int3DReg, intHyper, std::shared_ptr<int3DReg>>(
      clsVector, "int3DReg", py::buffer_protocol())
      .def(py::init<const int, const int, const int>(),
           "Initialize giving size")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def(py::init<const axis &, const axis &, const axis &>(),
           "Initialize from an axis")
      .def("allocate", (void (int3DReg::*)()) & int3DReg::allocate,
           "Allocate the array")
      .def("clone",
           (std::shared_ptr<int3DReg>(int3DReg::*)() const) & int3DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<int3DReg>(int3DReg::*)() const) &
               int3DReg::cloneSpace,
           "Make a copy of the vector space")
      .def_buffer([](int3DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(int), py::format_descriptor<int>::format(), 3,
            {m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
             m.getHyper()->getAxis(1).n},
            {sizeof(int) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n,
             sizeof(int) * m.getHyper()->getAxis(1).n, sizeof(int)});
      });

  py::class_<int4DReg, intHyper, std::shared_ptr<int4DReg>>(
      clsVector, "int4DReg", py::buffer_protocol())
      .def(py::init<const int, const int, const int, const int>(),
           "Initialize giving size")
      .def(py::init<const axis &, const axis &, const axis &, const axis &>(),
           "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def("allocate", (void (int4DReg::*)()) & int4DReg::allocate,
           "Allocate the array")
      .def("clone",
           (std::shared_ptr<int4DReg>(int4DReg::*)() const) & int4DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<int4DReg>(int4DReg::*)() const) &
               int4DReg::cloneSpace,
           "Make a copy of the vector space")
      .def_buffer([](int4DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(int), py::format_descriptor<int>::format(), 4,
            {m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
             m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
            {sizeof(int) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
             sizeof(int) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n,
             sizeof(int) * m.getHyper()->getAxis(1).n, sizeof(int)});
      });
  py::class_<int5DReg, intHyper, std::shared_ptr<int5DReg>>(
      clsVector, "int5DReg", py::buffer_protocol())
      .def(py::init<const int, const int, const int, const int, const int>(),
           "Initialize giving size")
      .def(py::init<const axis &, const axis &, const axis &, const axis &,
                    const axis &>(),
           "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def("allocate", (void (int5DReg::*)()) & int5DReg::allocate,
           "Allocate the array")
      .def("clone",
           (std::shared_ptr<int5DReg>(int5DReg::*)() const) & int5DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<int5DReg>(int5DReg::*)() const) &
               int5DReg::cloneSpace,
           "Make a copy of the vector space")
      .def_buffer([](int5DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(int), py::format_descriptor<int>::format(), 5,
            {m.getHyper()->getAxis(5).n, m.getHyper()->getAxis(4).n,
             m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
             m.getHyper()->getAxis(1).n},
            {sizeof(int) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                 m.getHyper()->getAxis(4).n,
             sizeof(int) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
             sizeof(int) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n,
             sizeof(int) * m.getHyper()->getAxis(1).n, sizeof(int)});
      });

  py::class_<int6DReg, intHyper, std::shared_ptr<int6DReg>>(
      clsVector, "int6DReg", py::buffer_protocol())
      .def(py::init<const int, const int, const int, const int, const int,
                    const int>(),
           "Initialize giving size")
      .def(py::init<const axis &, const axis &, const axis &, const axis &,
                    const axis &, const axis &>(),
           "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def("allocate", (void (int6DReg::*)()) & int6DReg::allocate,
           "Allocate the array")
      .def("clone",
           (std::shared_ptr<int6DReg>(int6DReg::*)() const) & int6DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<int6DReg>(int6DReg::*)() const) &
               int6DReg::cloneSpace,
           "Make a copy of the vector space")
      .def_buffer([](int6DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(int), py::format_descriptor<int>::format(), 6,
            {m.getHyper()->getAxis(6).n, m.getHyper()->getAxis(5).n,
             m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
             m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
            {sizeof(int) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                 m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n,
             sizeof(int) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                 m.getHyper()->getAxis(4).n,
             sizeof(int) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
             sizeof(int) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n,
             sizeof(int) * m.getHyper()->getAxis(1).n, sizeof(int)});
      });

  py::class_<byteHyper, regSpace, std::shared_ptr<byteHyper>>(clsVector,
                                                              "byteHyper")  //
      .def(py::init<>(), "Initlialize a new byte Hyper (don't use this")
      .def("getSpaceOnly", (bool (byteHyper::*)()) & byteHyper::getSpaceOnly,
           "Check to see if this only a description of the vector space")

      .def("setData",
           (void (byteHyper::*)(unsigned char *)) & byteHyper::setData,
           "Set the data pointer")
      .def("getVals", (unsigned char *(byteHyper::*)()) & byteHyper::getVals,
           "Get the data pointer")

      .def("isDifferent",
           (bool (byteHyper::*)(std::shared_ptr<byteHyper>)) &
               byteHyper::isDifferent,
           "Check to  see if two vectors are different")

      .def_property("_vals", &byteHyper::getVals, &byteHyper::setData,
                    py::return_value_policy::reference)

      .def("calcCheckSum",
           (unsigned char (byteHyper::*)() const) & byteHyper::calcCheckSum,
           "Calculate checksum of a vector")

      .def("zero", (void (byteHyper::*)()) & byteHyper::zero,
           "Fill a vector with zero")

      .def("rand", (void (byteHyper::*)()) & byteHyper::random,
           "Fill a vector with random number")

      .def("checkSame",
           (bool (byteHyper::*)(const std::shared_ptr<byteHyper>) const) &
               byteHyper::checkSame,
           "Check to make sure the vectors exist in the same space");

  py::class_<byte1DReg, byteHyper, std::shared_ptr<byte1DReg>>(
      clsVector, "byte1DReg", py::buffer_protocol())
      .def(py::init<const int>(), "Initialize giving size")
      .def(py::init<const axis &>(), "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")

      .def(
          "clone",
          (std::shared_ptr<byte1DReg>(byte1DReg::*)() const) & byte1DReg::clone,
          "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<byte1DReg>(byte1DReg::*)() const) &
               byte1DReg::cloneSpace,
           "Make a copy of the vector space")
      .def("allocate", (void (byte1DReg::*)()) & byte1DReg::allocate,
           "Allocate the array")

      .def_buffer([](byte1DReg &m) -> py::buffer_info {
        return py::buffer_info(m.getVals(), sizeof(unsigned char),
                               py::format_descriptor<unsigned char>::format(),
                               1, {m.getHyper()->getAxis(1).n},
                               {sizeof(unsigned char)});
      });
  py::class_<byte2DReg, byteHyper, std::shared_ptr<byte2DReg>>(
      clsVector, "byte2DReg", py::buffer_protocol())
      .def(py::init<const int, const int>(), "Initialize giving size")
      .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def(
          "clone",
          (std::shared_ptr<byte2DReg>(byte2DReg::*)() const) & byte2DReg::clone,
          "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<byte2DReg>(byte2DReg::*)() const) &
               byte2DReg::cloneSpace,
           "Make a copy of the vector space")
      .def("allocate", (void (byte2DReg::*)()) & byte2DReg::allocate,
           "Allocate the array")

      .def_buffer([](byte2DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(unsigned char),
            py::format_descriptor<unsigned char>::format(), 2,
            {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
            {sizeof(unsigned char) * m.getHyper()->getAxis(1).n,
             sizeof(unsigned char)});
      });

  py::class_<byte3DReg, byteHyper, std::shared_ptr<byte3DReg>>(
      clsVector, "byte3DReg", py::buffer_protocol())
      .def(py::init<const int, const int, const int>(),
           "Initialize giving size")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def(py::init<const axis &, const axis &, const axis &>(),
           "Initialize from an axis")
      .def("allocate", (void (byte3DReg::*)()) & byte3DReg::allocate,
           "Allocate the array")
      .def(
          "clone",
          (std::shared_ptr<byte3DReg>(byte3DReg::*)() const) & byte3DReg::clone,
          "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<byte3DReg>(byte3DReg::*)() const) &
               byte3DReg::cloneSpace,
           "Make a copy of the vector space")
      .def_buffer([](byte3DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(unsigned char),
            py::format_descriptor<unsigned char>::format(), 3,
            {m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
             m.getHyper()->getAxis(1).n},
            {sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n,
             sizeof(unsigned char) * m.getHyper()->getAxis(1).n,
             sizeof(unsigned char)});
      });

  py::class_<byte4DReg, byteHyper, std::shared_ptr<byte4DReg>>(
      clsVector, "byte4DReg", py::buffer_protocol())
      .def(py::init<const int, const int, const int, const int>(),
           "Initialize giving size")
      .def(py::init<const axis &, const axis &, const axis &, const axis &>(),
           "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def("allocate", (void (byte4DReg::*)()) & byte4DReg::allocate,
           "Allocate the array")
      .def(
          "clone",
          (std::shared_ptr<byte4DReg>(byte4DReg::*)() const) & byte4DReg::clone,
          "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<byte4DReg>(byte4DReg::*)() const) &
               byte4DReg::cloneSpace,
           "Make a copy of the vector space")
      .def_buffer([](byte4DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(unsigned char),
            py::format_descriptor<unsigned char>::format(), 4,
            {m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
             m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
            {sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
             sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n,
             sizeof(unsigned char) * m.getHyper()->getAxis(1).n,
             sizeof(unsigned char)});
      });
  py::class_<byte5DReg, byteHyper, std::shared_ptr<byte5DReg>>(
      clsVector, "byte5DReg", py::buffer_protocol())
      .def(py::init<const int, const int, const int, const int, const int>(),
           "Initialize giving size")
      .def(py::init<const axis &, const axis &, const axis &, const axis &,
                    const axis &>(),
           "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def("allocate", (void (byte5DReg::*)()) & byte5DReg::allocate,
           "Allocate the array")
      .def(
          "clone",
          (std::shared_ptr<byte5DReg>(byte5DReg::*)() const) & byte5DReg::clone,
          "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<byte5DReg>(byte5DReg::*)() const) &
               byte5DReg::cloneSpace,
           "Make a copy of the vector space")
      .def_buffer([](byte5DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(unsigned char),
            py::format_descriptor<unsigned char>::format(), 5,
            {m.getHyper()->getAxis(5).n, m.getHyper()->getAxis(4).n,
             m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
             m.getHyper()->getAxis(1).n},
            {sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                 m.getHyper()->getAxis(4).n,
             sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
             sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n,
             sizeof(unsigned char) * m.getHyper()->getAxis(1).n,
             sizeof(unsigned char)});
      });

  py::class_<byte6DReg, byteHyper, std::shared_ptr<byte6DReg>>(
      clsVector, "byte6DReg", py::buffer_protocol())
      .def(py::init<const int, const int, const int, const int, const int,
                    const int>(),
           "Initialize giving size")
      .def(py::init<const axis &, const axis &, const axis &, const axis &,
                    const axis &, const axis &>(),
           "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def("allocate", (void (byte6DReg::*)()) & byte6DReg::allocate,
           "Allocate the array")
      .def(
          "clone",
          (std::shared_ptr<byte6DReg>(byte6DReg::*)() const) & byte6DReg::clone,
          "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<byte6DReg>(byte6DReg::*)() const) &
               byte6DReg::cloneSpace,
           "Make a copy of the vector space")
      .def_buffer([](byte6DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(unsigned char),
            py::format_descriptor<unsigned char>::format(), 6,
            {m.getHyper()->getAxis(6).n, m.getHyper()->getAxis(5).n,
             m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
             m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
            {sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                 m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n,
             sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                 m.getHyper()->getAxis(4).n,
             sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
             sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n,
             sizeof(unsigned char) * m.getHyper()->getAxis(1).n,
             sizeof(unsigned char)});
      });
}
}  // namespace SEP
