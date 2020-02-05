#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "int1DReg.h"
#include "int2DReg.h"
#include "int3DReg.h"
#include "int4DReg.h"
#include "int5DReg.h"
#include "int6DReg.h"

namespace py = pybind11;
using namespace SEP;
void init_4dint(py::module &clsVector){
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
      .def("window",
           (std::shared_ptr<int4DReg>(int4DReg::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &) const) &
               int4DReg::window,
           "Window a vector")
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

}