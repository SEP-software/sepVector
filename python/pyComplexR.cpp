
#include "complex1DReg.h"
#include "complex2DReg.h"
#include "complex3DReg.h"
#include "complex4DReg.h"
#include "complex5DReg.h"
#include "complex6DReg.h"
#include "complex7DReg.h"

#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;
namespace SEP
{

     void init_complexR(py::module &clsVector)
     {

          py::class_<complexHyper, regSpace, std::shared_ptr<complexHyper> >(
              clsVector,
              "complexHyper") //
              .def(py::init<>(), "Initlialize a new complex Hyper (don't use this")
              .def("getSpaceOnly",
                   (bool (complexHyper::*)()) & complexHyper::getSpaceOnly,
                   "Check to see if this only a description of the vector space")

              .def("setData",
                   (void (complexHyper::*)(std::complex<float> *)) &
                       complexHyper::setData,
                   "Set the data pointer")
              .def("getVals",
                   (std::complex<float> * (complexHyper::*)()) & complexHyper::getVals,
                   "Get the data pointer")

              .def("isDifferent",
                   (bool (complexHyper::*)(std::shared_ptr<complexHyper>)) &
                       complexHyper::isDifferent,
                   "Check to  see if two vectors are different")

              .def("mult",
                   (void (complexHyper::*)(std::shared_ptr<complexHyper>)) &
                       complexHyper::mult,
                   "vec=vec*vec2")
              .def("dot",
                   (std::complex<float>(complexHyper::*)(std::shared_ptr<complexHyper>) const) &
                       complexHyper::dot,
                   "Calculate dot product")
              .def_property("_vals", &complexHyper::getVals, &complexHyper::setData,
                            py::return_value_policy::reference)
              .def("scale",
                   (void (complexHyper::*)(const double)) & complexHyper::scale,
                   "Scale a vector")
              .def("scaleAdd",
                   (void (complexHyper::*)(std::shared_ptr<complexHyper>, const double,
                                           const double)) &
                       complexHyper::scaleAdd,
                   "vec=vec*sc1+vec2*sc2")
              .def("calcCheckSum",
                   (unsigned char (complexHyper::*)() const) &
                       complexHyper::calcCheckSum,
                   "Calculate checksum of a vector")
              .def("norm",
                   (double (complexHyper::*)(const int n) const) & complexHyper::norm,
                   "Calculate n-norm of a vector")
              .def("zero", (void (complexHyper::*)()) & complexHyper::zero,
                   "Fill a vector with zero")
              .def("set",
                   (void (complexHyper::*)(const std::complex<float>)) &
                       complexHyper::set,
                   "Fill a vector with a value")
              .def("rand", (void (complexHyper::*)()) & complexHyper::random,
                   "Fill a vector with random number")
              .def("clipVector",
                   (void (complexHyper::*)(const std::shared_ptr<floatHyper>,
                                           const std::shared_ptr<floatHyper>)) &
                       complexHyper::clipVector,
                   "vec=min(max(low,vec),high)")
              .def("clipVector",
                   (void (complexHyper::*)(const std::shared_ptr<complexHyper>,
                                           const std::shared_ptr<complexHyper>)) &
                       complexHyper::clipVector,
                   "vec=min(max(low,vec),high)")
              .def("checkSame",
                   (bool (complexHyper::*)(const std::shared_ptr<complexHyper>) const) &
                       complexHyper::checkSame,
                   "Check to make sure the vectors exist in the same space");

          py::class_<complex1DReg, complexHyper, std::shared_ptr<complex1DReg> >(
              clsVector, "complex1DReg", py::buffer_protocol())
              .def(py::init<const int>(), "Initialize giving size")
              .def(py::init<const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")

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
                       py::format_descriptor<std::complex<float> >::format(), 1,
                       {m.getHyper()->getAxis(1).n}, {sizeof(std::complex<float>)});
              });
          py::class_<complex2DReg, complexHyper, std::shared_ptr<complex2DReg> >(
              clsVector, "complex2DReg", py::buffer_protocol())
              .def(py::init<const int, const int>(), "Initialize giving size")
              .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
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
                       py::format_descriptor<std::complex<float> >::format(), 2,
                       {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(std::complex<float>) * m.getHyper()->getAxis(1).n,
                        sizeof(std::complex<float>)});
              });

          py::class_<complex3DReg, complexHyper, std::shared_ptr<complex3DReg> >(
              clsVector, "complex3DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def("allocate", (void (complex3DReg::*)()) & complex3DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<complex3DReg>(complex3DReg::*)() const) &
                       complex3DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<complex3DReg>(complex3DReg::*)() const) &
                       complex3DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<complex3DReg>(complex3DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       complex3DReg::window,
                   "Window a vector")
              .def_buffer([](complex3DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(std::complex<float>),
                       py::format_descriptor<std::complex<float> >::format(), 3,
                       {m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(std::complex<float>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(std::complex<float>) * m.getHyper()->getAxis(1).n,
                        sizeof(std::complex<float>)});
              });

          py::class_<complex4DReg, complexHyper, std::shared_ptr<complex4DReg> >(
              clsVector, "complex4DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (complex4DReg::*)()) & complex4DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<complex4DReg>(complex4DReg::*)() const) &
                       complex4DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<complex4DReg>(complex4DReg::*)() const) &
                       complex4DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<complex4DReg>(complex4DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       complex4DReg::window,
                   "Window a vector")
              .def_buffer([](complex4DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(std::complex<float>),
                       py::format_descriptor<std::complex<float> >::format(), 4,
                       {m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(std::complex<float>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(std::complex<float>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(std::complex<float>) * m.getHyper()->getAxis(1).n,
                        sizeof(std::complex<float>)});
              });
          py::class_<complex5DReg, complexHyper, std::shared_ptr<complex5DReg> >(
              clsVector, "complex5DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (complex5DReg::*)()) & complex5DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<complex5DReg>(complex5DReg::*)() const) &
                       complex5DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<complex5DReg>(complex5DReg::*)() const) &
                       complex5DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<complex5DReg>(complex5DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       complex5DReg::window,
                   "Window a vector")
              .def_buffer([](complex5DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(std::complex<float>),
                       py::format_descriptor<std::complex<float> >::format(), 5,
                       {m.getHyper()->getAxis(5).n, m.getHyper()->getAxis(4).n,
                        m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(std::complex<float>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(std::complex<float>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(std::complex<float>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(std::complex<float>) * m.getHyper()->getAxis(1).n,
                        sizeof(std::complex<float>)});
              });

          py::class_<complex7DReg, complexHyper, std::shared_ptr<complex7DReg> >(
              clsVector, "complex7DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (complex7DReg::*)()) & complex7DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<complex7DReg>(complex7DReg::*)() const) &
                       complex7DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<complex7DReg>(complex7DReg::*)() const) &
                       complex6DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<complex7DReg>(complex7DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       complex6DReg::window,
                   "Window a vector")
              .def_buffer([](complex7DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(std::complex<float>),
                       py::format_descriptor<std::complex<float> >::format(), 7,
                       {m.getHyper()->getAxis(7).n, m.getHyper()->getAxis(6).n, m.getHyper()->getAxis(5).n,
                        m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(std::complex<float>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n * m.getHyper()->getAxis(6).n,
                        sizeof(std::complex<float>) * m.getHyper()->getAxis(1).n *
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
          py::class_<complex6DReg, complexHyper, std::shared_ptr<complex6DReg> >(
              clsVector, "complex6DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
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
                       py::format_descriptor<std::complex<float> >::format(), 6,
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

     } // namespace SEP
} // namespace SEP
