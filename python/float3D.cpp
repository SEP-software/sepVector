#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "float3DReg.h"
#include "float1DReg.h"
namespace py = pybind11;
using namespace SEP;
void init_3dfloat(py::module &clsVector){
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
      .def("window",
           (std::shared_ptr<float1DReg>(float3DReg::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &) const) &
               float3DReg::window,
           "Window a vector")

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
}