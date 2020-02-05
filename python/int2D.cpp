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
void init_2dint(py::module &clsVector){
py::class_<int2DReg, intHyper, std::shared_ptr<int2DReg>>(
      clsVector, "int2DReg", py::buffer_protocol())
      .def(py::init<const int, const int>(), "Initialize giving size")
      .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def(py::init<const std::shared_ptr<int6DReg>, const int, const bool,
                    const int, const bool, const std::vector<int> &,
                    const std::vector<int> &, std::vector<int> &>(),
           "Create a 2-D slice from 6-D hypercube")
      .def(py::init<const std::shared_ptr<int5DReg>, const int, const bool,
                    const int, const bool, const std::vector<int> &,
                    const std::vector<int> &, std::vector<int> &>(),
           "Create a 2-D slice from 5-D hypercube")
      .def(py::init<const std::shared_ptr<int4DReg>, const int, const bool,
                    const int, const bool, const std::vector<int> &,
                    const std::vector<int> &, std::vector<int> &>(),
           "Create a 2-D slice from 4-D hypercube")
      .def(py::init<const std::shared_ptr<int3DReg>, const int, const bool,
                    const int, const bool, const std::vector<int> &,
                    const std::vector<int> &, std::vector<int> &>(),
           "Create a 2-D slice from 3-D hypercube")
      .def(py::init<const std::shared_ptr<int2DReg>, const int, const bool,
                    const int, const bool, const std::vector<int> &,
                    const std::vector<int> &, std::vector<int> &>(),
           "Create a 2-D slice from 2-D hypercube")
      .def("clone",
           (std::shared_ptr<int2DReg>(int2DReg::*)() const) & int2DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<int2DReg>(int2DReg::*)() const) &
               int2DReg::cloneSpace,
           "Make a copy of the vector space")
      .def("allocate", (void (int2DReg::*)()) & int2DReg::allocate,
           "Allocate the array")
      .def("window",
           (std::shared_ptr<int2DReg>(int2DReg::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &) const) &
               int2DReg::window,
           "Window a vector")

      .def_buffer([](int2DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(int), py::format_descriptor<int>::format(), 2,
            {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
            {sizeof(int) * m.getHyper()->getAxis(1).n, sizeof(int)});
      });

}