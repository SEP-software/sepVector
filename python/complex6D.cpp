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
void init_6dcomplex(py::module &clsVector){
py::class_<complex6DReg, complexHyper, std::shared_ptr<complex6DReg>>(
      clsVector, "complex6DReg", py::buffer_protocol())
      .def(py::init<const int, const int, const int, const int, const int,
                    const int>(),
           "Initialize giving size")
      .def(py::init<const axis &, const axis &, const axis &, const axis &,
                    const axis &, const axis &>(),
           "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
      .def("allocate", (void (complex6DReg::*)()) & complex6DReg::allocate,
           "Allocate the array")
      .def("clone",
           (std::shared_ptr<complex6DReg>(complex6DReg::*)() const) &
               complex6DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<complex6DReg>(complex6DReg::*)() const) &
               complex6DReg::cloneSpace,
           "Make a copy of the vector space")
      .def("window",
           (std::shared_ptr<complex6DReg>(complex6DReg::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &) const) &
               complex6DReg::window,
           "Window a vector")
      .def_buffer([](complex6DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(std::complex<float>),
            py::format_descriptor<std::complex<float>>::format(), 6,
            {m.getHyper()->getAxis(6).n, m.getHyper()->getAxis(5).n,
             m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
             m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
            {sizeof(std::complex<float>) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                 m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n,
             sizeof(std::complex<float>) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                 m.getHyper()->getAxis(4).n,
             sizeof(std::complex<float>) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
             sizeof(std::complex<float>) * m.getHyper()->getAxis(1).n *
                 m.getHyper()->getAxis(2).n,
             sizeof(std::complex<float>) * m.getHyper()->getAxis(1).n,
             sizeof(std::complex<float>)});
      });

}