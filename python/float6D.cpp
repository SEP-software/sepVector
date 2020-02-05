#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "float6DReg.h"

namespace py = pybind11;
using namespace SEP;
void init_6dfloat(py::module &clsVector){
py::class_<float6DReg, floatHyper, std::shared_ptr<float6DReg>>(
      clsVector, "float6DReg", py::buffer_protocol())
      .def(py::init<const int, const int, const int, const int, const int,
                    const int>(),
           "Initialize giving size")
      .def(py::init<const axis &, const axis &, const axis &, const axis &,
                    const axis &, const axis &>(),
           "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def("allocate", (void (float6DReg::*)()) & float6DReg::allocate,
           "Allocate the array")
      .def("clone",
           (std::shared_ptr<float6DReg>(float6DReg::*)() const) &
               float6DReg::clone,
           "Make a copy of the vector")
      .def("window",
           (std::shared_ptr<float6DReg>(float6DReg::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &) const) &
               float6DReg::window,
           "Window a vector")

      .def("cloneSpace",
           (std::shared_ptr<float6DReg>(float6DReg::*)() const) &
               float6DReg::cloneSpace,
           "Make a copy of the vector space")
      .def_buffer([](float6DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(float), py::format_descriptor<float>::format(),
            6,
            {m.getHyper()->getAxis(6).n, m.getHyper()->getAxis(5).n,
             m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
             m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
            {sizeof(float) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                 m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n,
             sizeof(float) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                 m.getHyper()->getAxis(4).n,
             sizeof(float) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
             sizeof(float) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n,
             sizeof(float) * m.getHyper()->getAxis(1).n, sizeof(float)});
      });
}