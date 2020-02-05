#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "double5DReg.h"
#include "double4DReg.h"
#include "double3DReg.h"
#include "double2DReg.h"
#include "double1DReg.h"
#include "double6DReg.h"
namespace py = pybind11;
using namespace SEP;
void init_3ddouble(py::module &clsVector){
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
      .def("window",
           (std::shared_ptr<double3DReg>(double3DReg::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &) const) &
               double3DReg::window,
           "Window a vector")

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
}