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
void init_6ddouble(py::module &clsVector){
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
      .def("window",
           (std::shared_ptr<double6DReg>(double6DReg::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &) const) &
               double6DReg::window,
           "Window a vector")
      .def("clone",
           (std::shared_ptr<double6DReg>(double6DReg::*)() const) &
               double6DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<double6DReg>(double6DReg::*)() const) &
               double6DReg::cloneSpace,
           "Make a copy of the vector space")
      .def("window",
           (std::shared_ptr<double6DReg>(double6DReg::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &) const) &
               double6DReg::window,
           "Window a vector")

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

}