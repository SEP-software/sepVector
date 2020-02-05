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
void init_5dbyte(py::module &clsVector){
py::class_<byte5DReg, byteHyper, std::shared_ptr<byte5DReg>>(
      clsVector, "byte5DReg", py::buffer_protocol())
      .def(py::init<const int, const int, const int, const int, const int>(),
           "Initialize giving size")
      .def(py::init<const axis &, const axis &, const axis &, const axis &,
                    const axis &>(),
           "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def("allocate", (void (byte5DReg::*)()) & byte5DReg::allocate,
           "Allocate the array")
      .def(
          "clone",
          (std::shared_ptr<byte5DReg>(byte5DReg::*)() const) & byte5DReg::clone,
          "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<byte5DReg>(byte5DReg::*)() const) &
               byte5DReg::cloneSpace,
           "Make a copy of the vector space")
      .def("window",
           (std::shared_ptr<byte5DReg>(byte5DReg::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &) const) &
               byte5DReg::window,
           "Window a vector")
      .def_buffer([](byte5DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(unsigned char),
            py::format_descriptor<unsigned char>::format(), 5,
            {m.getHyper()->getAxis(5).n, m.getHyper()->getAxis(4).n,
             m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
             m.getHyper()->getAxis(1).n},
            {sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                 m.getHyper()->getAxis(4).n,
             sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
             sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n,
             sizeof(unsigned char) * m.getHyper()->getAxis(1).n,
             sizeof(unsigned char)});
      });

}