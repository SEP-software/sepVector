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
void init_2ddouble(py::module &clsVector){
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
      .def(py::init<const std::shared_ptr<double6DReg>, const int, const bool,
                    const int, const bool, const std::vector<int> &,
                    const std::vector<int> &, std::vector<int> &>(),
           "Create a 2-D slice from 6-D hypercube")
      .def(py::init<const std::shared_ptr<double5DReg>, const int, const bool,
                    const int, const bool, const std::vector<int> &,
                    const std::vector<int> &, std::vector<int> &>(),
           "Create a 2-D slice from 5-D hypercube")
      .def(py::init<const std::shared_ptr<double4DReg>, const int, const bool,
                    const int, const bool, const std::vector<int> &,
                    const std::vector<int> &, std::vector<int> &>(),
           "Create a 2-D slice from 4-D hypercube")
      .def(py::init<const std::shared_ptr<double3DReg>, const int, const bool,
                    const int, const bool, const std::vector<int> &,
                    const std::vector<int> &, std::vector<int> &>(),
           "Create a 2-D slice from 3-D hypercube")
      .def(py::init<const std::shared_ptr<double2DReg>, const int, const bool,
                    const int, const bool, const std::vector<int> &,
                    const std::vector<int> &, std::vector<int> &>(),
           "Create a 2-D slice from 2-D hypercube")
      .def("window",
           (std::shared_ptr<double2DReg>(double2DReg::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &) const) &
               double2DReg::window,
           "Window a vector")

      .def_buffer([](double2DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(double),
            py::format_descriptor<double>::format(), 2,
            {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
            {sizeof(double) * m.getHyper()->getAxis(1).n, sizeof(double)});
      });

}