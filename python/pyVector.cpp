#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "float1DReg.h"
#include "float2DReg.h"
#include "float3DReg.h"
#include "float4DReg.h"
namespace py = pybind11;
namespace giee {
using namespace SEP;

PYBIND11_MODULE(pySepVector, clsVector) {
  py::class_<Vector, std::shared_ptr<Vector>>(clsVector, "Vector")
      .def(py::init<>(), "Initlialize a new Vector (don't use this");

  py::class_<floatHyper, Vector, std::shared_ptr<floatHyper>>(clsVector,
                                                              "floatHyper")  //
      .def(py::init<>(), "Initlialize a new Float Hyper (don't use this")
      .def("getSpaceOnly", (bool (floatHyper::*)()) & floatHyper::getSpaceOnly,
           "Check to see if this only a description of the vector space")

      .def("setData", (void (floatHyper::*)(float *)) & floatHyper::setData,
           "Set the data pointer")
      .def("getVals", (float *(floatHyper::*)()) & floatHyper::getVals,
           "Get the data pointer")
      .def_property("_hyper", &floatHyper::getHyper, &floatHyper::setHyper,
                    py::return_value_policy::reference)

      .def_property("_vals", &floatHyper::getVals, &floatHyper::setData,
                    py::return_value_policy::reference)
      .def(
          "add",
          (void (floatHyper::*)(std::shared_ptr<floatHyper>)) & floatHyper::add,
          "Add two vectors")
      .def("scale",
           (void (floatHyper::*)(const double val)) & floatHyper::scale,
           "Scale a vector")
      .def("scaleAdd",
           (void (floatHyper::*)(const double sc1, std::shared_ptr<floatHyper>,
                                 const double sc2)) &
               floatHyper::scaleAdd,
           "vec=vec*sc1+vec2*sc2")
      .def("random", (void (floatHyper::*)()) & floatHyper::random,
           "Fill a vector with random number")
      .def("dot",
           (double (floatHyper::*)(std::shared_ptr<floatHyper>) const) &
               floatHyper::dot,
           "Calculate dot product")
      .def("checkSame",
           (bool (floatHyper::*)(const std::shared_ptr<floatHyper>,
                                 const bool checkAlloc) const) &
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
}
}  // namespace giee