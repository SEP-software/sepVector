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
void init_1dcomplex(py::module &clsVector){
py::class_<complex1DReg, complexHyper, std::shared_ptr<complex1DReg>>(
      clsVector, "complex1DReg", py::buffer_protocol())
      .def(py::init<const int>(), "Initialize giving size")
      .def(py::init<const axis &>(), "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")

      .def("clone",
           (std::shared_ptr<complex1DReg>(complex1DReg::*)() const) &
               complex1DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<complex1DReg>(complex1DReg::*)() const) &
               complex1DReg::cloneSpace,
           "Make a copy of the vector space")
      .def("allocate", (void (complex1DReg::*)()) & complex1DReg::allocate,
           "Allocate the array")
      .def("window",
           (std::shared_ptr<complex1DReg>(complex1DReg::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &) const) &
               complex1DReg::window,
           "Window a vector")

      .def_buffer([](complex1DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(std::complex<float>),
            py::format_descriptor<std::complex<float>>::format(), 1,
            {m.getHyper()->getAxis(1).n}, {sizeof(std::complex<float>)});
      });
}