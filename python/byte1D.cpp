#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "byte1DReg.h"
#include "byte2DReg.h"
#include "byte3DReg.h"
#include "byte4DReg.h"
#include "byte5DReg.h"
#include "byte6DReg.h"


namespace py = pybind11;
using namespace SEP;
void init_1dbyte(py::module &clsVector){
py::class_<byte1DReg, byteHyper, std::shared_ptr<byte1DReg>>(
      clsVector, "byte1DReg", py::buffer_protocol())
      .def(py::init<const int>(), "Initialize giving size")
      .def(py::init<const axis &>(), "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def(py::init<const std::shared_ptr<byte6DReg>, const int, const bool,
                    const std::vector<int> &, const std::vector<int> &,
                    std::vector<int> &>(),
           "Create a 1-D slice from 6-D hypercube")
      .def(py::init<const std::shared_ptr<byte5DReg>, const int, const bool,
                    const std::vector<int> &, const std::vector<int> &,
                    std::vector<int> &>(),
           "Create a 1-D slice from 5-D hypercube")
      .def(py::init<const std::shared_ptr<byte4DReg>, const int, const bool,
                    const std::vector<int> &, const std::vector<int> &,
                    std::vector<int> &>(),
           "Create a 1-D slice from 4-D hypercube")
      .def(py::init<const std::shared_ptr<byte3DReg>, const int, const bool,
                    const std::vector<int> &, const std::vector<int> &,
                    std::vector<int> &>(),
           "Create a 1-D slice from 3-D hypercube")
      .def(py::init<const std::shared_ptr<byte2DReg>, const int, const bool,
                    const std::vector<int> &, const std::vector<int> &,
                    std::vector<int> &>(),
           "Create a 1-D slice from 2-D hypercube")
      .def(py::init<const std::shared_ptr<byte1DReg>, const int, const bool,
                    const std::vector<int> &, const std::vector<int> &,
                    std::vector<int> &>(),
           "Create a 1-D slice from 1-D hypercube")
      .def(
          "clone",
          (std::shared_ptr<byte1DReg>(byte1DReg::*)() const) & byte1DReg::clone,
          "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<byte1DReg>(byte1DReg::*)() const) &
               byte1DReg::cloneSpace,
           "Make a copy of the vector space")
      .def("allocate", (void (byte1DReg::*)()) & byte1DReg::allocate,
           "Allocate the array")
      .def("window",
           (std::shared_ptr<byte1DReg>(byte1DReg::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &) const) &
               byte1DReg::window,
           "Window a vector")

      .def_buffer([](byte1DReg &m) -> py::buffer_info {
        return py::buffer_info(m.getVals(), sizeof(unsigned char),
                               py::format_descriptor<unsigned char>::format(),
                               1, {m.getHyper()->getAxis(1).n},
                               {sizeof(unsigned char)});
      });
}