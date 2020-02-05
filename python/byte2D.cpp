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
void init_2dbyte(py::module &clsVector){
py::class_<byte2DReg, byteHyper, std::shared_ptr<byte2DReg>>(
      clsVector, "byte2DReg", py::buffer_protocol())
      .def(py::init<const int, const int>(), "Initialize giving size")
      .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def(py::init<const std::shared_ptr<byte6DReg>, const int, const bool,
                    const int, const bool, const std::vector<int> &,
                    const std::vector<int> &, std::vector<int> &>(),
           "Create a 2-D slice from 6-D hypercube")
      .def(py::init<const std::shared_ptr<byte5DReg>, const int, const bool,
                    const int, const bool, const std::vector<int> &,
                    const std::vector<int> &, std::vector<int> &>(),
           "Create a 2-D slice from 5-D hypercube")
      .def(py::init<const std::shared_ptr<byte4DReg>, const int, const bool,
                    const int, const bool, const std::vector<int> &,
                    const std::vector<int> &, std::vector<int> &>(),
           "Create a 2-D slice from 4-D hypercube")
      .def(py::init<const std::shared_ptr<byte3DReg>, const int, const bool,
                    const int, const bool, const std::vector<int> &,
                    const std::vector<int> &, std::vector<int> &>(),
           "Create a 2-D slice from 3-D hypercube")
      .def(py::init<const std::shared_ptr<byte2DReg>, const int, const bool,
                    const int, const bool, const std::vector<int> &,
                    const std::vector<int> &, std::vector<int> &>(),
           "Create a 2-D slice from 2-D hypercube")
      .def(
          "clone",
          (std::shared_ptr<byte2DReg>(byte2DReg::*)() const) & byte2DReg::clone,
          "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<byte2DReg>(byte2DReg::*)() const) &
               byte2DReg::cloneSpace,
           "Make a copy of the vector space")
      .def("allocate", (void (byte2DReg::*)()) & byte2DReg::allocate,
           "Allocate the array")
      .def("window",
           (std::shared_ptr<byte2DReg>(byte2DReg::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &) const) &
               byte2DReg::window,
           "Window a vector")
      .def_buffer([](byte2DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(unsigned char),
            py::format_descriptor<unsigned char>::format(), 2,
            {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
            {sizeof(unsigned char) * m.getHyper()->getAxis(1).n,
             sizeof(unsigned char)});
      });
}