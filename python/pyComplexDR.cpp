
#include "complexDouble1DReg.h"
#include "complexDouble2DReg.h"
#include "complexDouble3DReg.h"
#include "complexDouble4DReg.h"
#include "complexDouble5DReg.h"
#include "complexDouble6DReg.h"
#include "complexDouble7DReg.h"

#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;
namespace SEP
{

     void init_complexDR(py::module &clsVector)
     {

          py::class_<complexDoubleHyper, regSpace, std::shared_ptr<complexDoubleHyper> >(
              clsVector,
              "complexDoubleHyper") //
              .def(py::init<>(), "Initlialize a new complex Hyper (don't use this")
              .def("getSpaceOnly",
                   (bool (complexDoubleHyper::*)()) & complexDoubleHyper::getSpaceOnly,
                   "Check to see if this only a description of the vector space")

              .def("setData",
                   (void (complexDoubleHyper::*)(std::complex<double> *)) &
                       complexDoubleHyper::setData,
                   "Set the data pointer")
              .def("getVals",
                   (std::complex<double> * (complexDoubleHyper::*)()) &
                       complexDoubleHyper::getVals,
                   "Get the data pointer")

              .def("isDifferent",
                   (bool (complexDoubleHyper::*)(std::shared_ptr<complexDoubleHyper>)) &
                       complexDoubleHyper::isDifferent,
                   "Check to  see if two vectors are different")

              .def("mult",
                   (void (complexDoubleHyper::*)(std::shared_ptr<complexDoubleHyper>)) &
                       complexDoubleHyper::mult,
                   "vec=vec*vec2")
              .def("dot",
                   (std::complex<double>(complexDoubleHyper::*)(std::shared_ptr<complexDoubleHyper>)
                        const) &
                       complexDoubleHyper::dot,
                   "Calculate dot product")
              .def_property("_vals", &complexDoubleHyper::getVals,
                            &complexDoubleHyper::setData,
                            py::return_value_policy::reference)
              .def("scale",
                   (void (complexDoubleHyper::*)(const double)) &
                       complexDoubleHyper::scale,
                   "Scale a vector")
              .def("scaleAdd",
                   (void (complexDoubleHyper::*)(std::shared_ptr<complexDoubleHyper>,
                                                 const double, const double)) &
                       complexDoubleHyper::scaleAdd,
                   "vec=vec*sc1+vec2*sc2")
              .def("calcCheckSum",
                   (unsigned char (complexDoubleHyper::*)() const) &
                       complexDoubleHyper::calcCheckSum,
                   "Calculate checksum of a vector")
              .def("norm",
                   (double (complexDoubleHyper::*)(const int n) const) &
                       complexDoubleHyper::norm,
                   "Calculate n-norm of a vector")
              .def("zero", (void (complexDoubleHyper::*)()) & complexDoubleHyper::zero,
                   "Fill a vector with zero")
              .def("set",
                   (void (complexDoubleHyper::*)(const std::complex<double>)) &
                       complexDoubleHyper::set,
                   "Fill a vector with a value")
              .def("rand",
                   (void (complexDoubleHyper::*)()) & complexDoubleHyper::random,
                   "Fill a vector with random number")
              .def("clipVector",
                   (void (complexDoubleHyper::*)(const std::shared_ptr<doubleHyper>,
                                                 const std::shared_ptr<doubleHyper>)) &
                       complexDoubleHyper::clipVector,
                   "vec=min(max(low,vec),high)")
              .def("clipVector",
                   (void (complexDoubleHyper::*)(
                       const std::shared_ptr<complexDoubleHyper>,
                       const std::shared_ptr<complexDoubleHyper>)) &
                       complexDoubleHyper::clipVector,
                   "vec=min(max(low,vec),high)")
              .def("checkSame",
                   (bool (complexDoubleHyper::*)(
                       const std::shared_ptr<complexDoubleHyper>) const) &
                       complexDoubleHyper::checkSame,
                   "Check to make sure the vectors exist in the same space");

          py::class_<complexDouble1DReg, complexDoubleHyper,
                     std::shared_ptr<complexDouble1DReg> >(
              clsVector, "complexDouble1DReg", py::buffer_protocol())
              .def(py::init<const int>(), "Initialize giving size")
              .def(py::init<const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")

              .def(
                  "clone",
                  (std::shared_ptr<complexDouble1DReg>(complexDouble1DReg::*)() const) &
                      complexDouble1DReg::clone,
                  "Make a copy of the vector")
              .def(
                  "cloneSpace",
                  (std::shared_ptr<complexDouble1DReg>(complexDouble1DReg::*)() const) &
                      complexDouble1DReg::cloneSpace,
                  "Make a copy of the vector space")
              .def("allocate",
                   (void (complexDouble1DReg::*)()) & complexDouble1DReg::allocate,
                   "Allocate the array")
              .def("window",
                   (std::shared_ptr<complexDouble1DReg>(complexDouble1DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       complexDouble1DReg::window,
                   "Window a vector")

              .def_buffer([](complexDouble1DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(std::complex<double>),
                       py::format_descriptor<std::complex<double> >::format(), 1,
                       {m.getHyper()->getAxis(1).n}, {sizeof(std::complex<double>)});
              });
          py::class_<complexDouble2DReg, complexDoubleHyper,
                     std::shared_ptr<complexDouble2DReg> >(
              clsVector, "complexDouble2DReg", py::buffer_protocol())
              .def(py::init<const int, const int>(), "Initialize giving size")
              .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(
                  "clone",
                  (std::shared_ptr<complexDouble2DReg>(complexDouble2DReg::*)() const) &
                      complexDouble2DReg::clone,
                  "Make a copy of the vector")
              .def(
                  "cloneSpace",
                  (std::shared_ptr<complexDouble2DReg>(complexDouble2DReg::*)() const) &
                      complexDouble2DReg::cloneSpace,
                  "Make a copy of the vector space")
              .def("allocate",
                   (void (complexDouble2DReg::*)()) & complexDouble2DReg::allocate,
                   "Allocate the array")
              .def("window",
                   (std::shared_ptr<complexDouble2DReg>(complexDouble2DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       complexDouble2DReg::window,
                   "Window a vector")
              .def_buffer([](complexDouble2DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(std::complex<double>),
                       py::format_descriptor<std::complex<double> >::format(), 2,
                       {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n,
                        sizeof(std::complex<double>)});
              });

          py::class_<complexDouble3DReg, complexDoubleHyper,
                     std::shared_ptr<complexDouble3DReg> >(
              clsVector, "complexDouble3DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def("allocate",
                   (void (complexDouble3DReg::*)()) & complexDouble3DReg::allocate,
                   "Allocate the array")
              .def(
                  "clone",
                  (std::shared_ptr<complexDouble3DReg>(complexDouble3DReg::*)() const) &
                      complexDouble3DReg::clone,
                  "Make a copy of the vector")
              .def(
                  "cloneSpace",
                  (std::shared_ptr<complexDouble3DReg>(complexDouble3DReg::*)() const) &
                      complexDouble3DReg::cloneSpace,
                  "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<complexDouble3DReg>(complexDouble3DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       complexDouble3DReg::window,
                   "Window a vector")
              .def_buffer([](complexDouble3DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(std::complex<double>),
                       py::format_descriptor<std::complex<double> >::format(), 3,
                       {m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n,
                        sizeof(std::complex<double>)});
              });

          py::class_<complexDouble4DReg, complexDoubleHyper,
                     std::shared_ptr<complexDouble4DReg> >(
              clsVector, "complexDouble4DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate",
                   (void (complexDouble4DReg::*)()) & complexDouble4DReg::allocate,
                   "Allocate the array")
              .def(
                  "clone",
                  (std::shared_ptr<complexDouble4DReg>(complexDouble4DReg::*)() const) &
                      complexDouble4DReg::clone,
                  "Make a copy of the vector")
              .def(
                  "cloneSpace",
                  (std::shared_ptr<complexDouble4DReg>(complexDouble4DReg::*)() const) &
                      complexDouble4DReg::cloneSpace,
                  "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<complexDouble4DReg>(complexDouble4DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       complexDouble4DReg::window,
                   "Window a vector")
              .def_buffer([](complexDouble4DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(std::complex<double>),
                       py::format_descriptor<std::complex<double> >::format(), 4,
                       {m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n,
                        sizeof(std::complex<double>)});
              });
          py::class_<complexDouble5DReg, complexDoubleHyper,
                     std::shared_ptr<complexDouble5DReg> >(
              clsVector, "complexDouble5DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate",
                   (void (complexDouble5DReg::*)()) & complexDouble5DReg::allocate,
                   "Allocate the array")
              .def(
                  "clone",
                  (std::shared_ptr<complexDouble5DReg>(complexDouble5DReg::*)() const) &
                      complexDouble5DReg::clone,
                  "Make a copy of the vector")
              .def(
                  "cloneSpace",
                  (std::shared_ptr<complexDouble5DReg>(complexDouble5DReg::*)() const) &
                      complexDouble5DReg::cloneSpace,
                  "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<complexDouble5DReg>(complexDouble5DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       complexDouble5DReg::window,
                   "Window a vector")
              .def_buffer([](complexDouble5DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(std::complex<double>),
                       py::format_descriptor<std::complex<double> >::format(), 5,
                       {m.getHyper()->getAxis(5).n, m.getHyper()->getAxis(4).n,
                        m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n,
                        sizeof(std::complex<double>)});
              });

          py::class_<complexDouble6DReg, complexDoubleHyper,
                     std::shared_ptr<complexDouble6DReg> >(
              clsVector, "complexDouble6DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate",
                   (void (complexDouble6DReg::*)()) & complexDouble6DReg::allocate,
                   "Allocate the array")
              .def(
                  "clone",
                  (std::shared_ptr<complexDouble6DReg>(complexDouble6DReg::*)() const) &
                      complexDouble6DReg::clone,
                  "Make a copy of the vector")
              .def(
                  "cloneSpace",
                  (std::shared_ptr<complexDouble6DReg>(complexDouble6DReg::*)() const) &
                      complexDouble6DReg::cloneSpace,
                  "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<complexDouble6DReg>(complexDouble6DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       complexDouble6DReg::window,
                   "Window a vector")
              .def_buffer([](complexDouble6DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(std::complex<double>),
                       py::format_descriptor<std::complex<double> >::format(), 6,
                       {m.getHyper()->getAxis(6).n, m.getHyper()->getAxis(5).n,
                        m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n,
                        sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n,
                        sizeof(std::complex<double>)});
              });

          py::class_<complexDouble7DReg, complexDoubleHyper,
                     std::shared_ptr<complexDouble7DReg> >(
              clsVector, "complexDouble7DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate",
                   (void (complexDouble7DReg::*)()) & complexDouble7DReg::allocate,
                   "Allocate the array")
              .def(
                  "clone",
                  (std::shared_ptr<complexDouble7DReg>(complexDouble7DReg::*)() const) &
                      complexDouble7DReg::clone,
                  "Make a copy of the vector")
              .def(
                  "cloneSpace",
                  (std::shared_ptr<complexDouble7DReg>(complexDouble7DReg::*)() const) &
                      complexDouble7DReg::cloneSpace,
                  "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<complexDouble7DReg>(complexDouble7DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       complexDouble7DReg::window,
                   "Window a vector")
              .def_buffer([](complexDouble7DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(std::complex<double>),
                       py::format_descriptor<std::complex<double> >::format(), 7,
                       {m.getHyper()->getAxis(7).n, m.getHyper()->getAxis(6).n, m.getHyper()->getAxis(5).n,
                        m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n * m.getHyper()->getAxis(6).n,
                        sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n,
                        sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(std::complex<double>) * m.getHyper()->getAxis(1).n,
                        sizeof(std::complex<double>)});
              });
     }
} // namespace SEP
