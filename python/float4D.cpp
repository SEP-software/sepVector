#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "float4DReg.h"

namespace py = pybind11;
using namespace SEP;
void init_4dfloat(py::module &clsVector){
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
      .def("window",
           (std::shared_ptr<float4DReg>(float4DReg::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &) const) &
               float4DReg::window,
           "Window a vector")

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