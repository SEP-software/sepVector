#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "complex1DReg.h"
#include "complex2DReg.h"
#include "complex3DReg.h"
#include "complex4DReg.h"
#include "complex5DReg.h"
#include "complex6DReg.h"

namespace py = pybind11;
using namespace SEP;
void init_2dcomplex(py::module &clsVector){
  py::class_<complex2DReg, complexHyper, std::shared_ptr<complex2DReg>>(
      clsVector, "complex2DReg", py::buffer_protocol())
      .def(py::init<const int, const int>(), "Initialize giving size")
      .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def("clone",
           (std::shared_ptr<complex2DReg>(complex2DReg::*)() const) &
               complex2DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<complex2DReg>(complex2DReg::*)() const) &
               complex2DReg::cloneSpace,
           "Make a copy of the vector space")
      .def("allocate", (void (complex2DReg::*)()) & complex2DReg::allocate,
           "Allocate the array")
      .def("window",
           (std::shared_ptr<complex2DReg>(complex2DReg::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &) const) &
               complex2DReg::window,
           "Window a vector")
      .def_buffer([](complex2DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(std::complex<float>),
            py::format_descriptor<std::complex<float>>::format(), 2,
            {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
            {sizeof(std::complex<float>) * m.getHyper()->getAxis(1).n,
             sizeof(std::complex<float>)});
      });


}