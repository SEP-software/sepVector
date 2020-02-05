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
void init_6dint(py::module &clsVector){
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
      .def("window",
           (std::shared_ptr<int6DReg>(int6DReg::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &) const) &
               int6DReg::window,
           "Window a vector")
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


}