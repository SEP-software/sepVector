

#include "double1DReg.h"
#include "double2DReg.h"
#include "double3DReg.h"
#include "double4DReg.h"
#include "double5DReg.h"
#include "double6DReg.h"
#include "double7DReg.h"

#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;
namespace SEP
{

     void init_doubleR(py::module &clsVector)
     {

          py::class_<doubleHyper, regSpace, std::shared_ptr<doubleHyper> >(
              clsVector,
              "doubleHyper") //
              .def(py::init<>(), "Initlialize a new double Hyper (don't use this")
              .def("getSpaceOnly",
                   (bool (doubleHyper::*)()) & doubleHyper::getSpaceOnly,
                   "Check to see if this only a description of the vector space")

              .def("setData", (void (doubleHyper::*)(double *)) & doubleHyper::setData,
                   "Set the data pointer")
              .def("getVals", (double *(doubleHyper::*)()) & doubleHyper::getVals,
                   "Get the data pointer")
              .def("clip",
                   (void (doubleHyper::*)(const double, const double)) &
                       doubleHyper::clip,
                   "Clip a dataset given minumum and maximum value")
              .def("cent",
                   (double (doubleHyper::*)(const float pct, const int jsamp) const) &
                       doubleHyper::cent,
                   "Calculate  the percentile of a dataset")
              .def("calcHisto",
                   (void (doubleHyper::*)(std::shared_ptr<int1DReg>, float, float)) &
                       doubleHyper::calcHisto,
                   "Calculate histogram")
              .def("clipVector",
                   (void (doubleHyper::*)(const std::shared_ptr<doubleHyper>,
                                          const std::shared_ptr<doubleHyper>)) &
                       doubleHyper::clipVector,
                   "vec=min(max(low,vec),high)")
              .def("isDifferent",
                   (bool (doubleHyper::*)(std::shared_ptr<doubleHyper>)) &
                       doubleHyper::isDifferent,
                   "Check to  see if two vectors are different")

              .def_property("_vals", &doubleHyper::getVals, &doubleHyper::setData,
                            py::return_value_policy::reference)

              .def("createMask",
                   (void (doubleHyper::*)(const double, const double)) &
                       doubleHyper::createMask,
                   "Create a mask weight")
              .def("add",
                   (void (doubleHyper::*)(std::shared_ptr<doubleHyper>)) &
                       doubleHyper::add,
                   "Add two vectors")
              .def("scale", (void (doubleHyper::*)(const double)) & doubleHyper::scale,
                   "Scale a vector")

              .def("scaleAdd",
                   (void (doubleHyper::*)(std::shared_ptr<doubleHyper>, const double,
                                          const double)) &
                       doubleHyper::scaleAdd,
                   "vec=vec*sc1+vec2*sc2")
              .def("calcCheckSum",
                   (double (doubleHyper::*)() const) & doubleHyper::calcCheckSum,
                   "Calculate checksum of a vector")

              .def("norm",
                   (double (doubleHyper::*)(const int n) const) & doubleHyper::norm,
                   "Calculate n-norm of a vector")
              .def("zero", (void (doubleHyper::*)()) & doubleHyper::zero,
                   "Fill a vector with zero")
              .def("set", (void (doubleHyper::*)(const double)) & doubleHyper::set,
                   "Fill a vector with a value")
              .def("signum", (void (doubleHyper::*)()) & doubleHyper::signum,
                   "Fill a vector with it's signum")
              .def("rand", (void (doubleHyper::*)()) & doubleHyper::random,
                   "Fill a vector with random number")

              .def("mult",
                   (void (doubleHyper::*)(std::shared_ptr<doubleHyper>)) &
                       doubleHyper::mult,
                   "vec=vec*vec2")
              .def("dot",
                   (double (doubleHyper::*)(std::shared_ptr<doubleHyper>) const) &
                       doubleHyper::dot,
                   "Calculate dot product")
              .def("checkSame",
                   (bool (doubleHyper::*)(const std::shared_ptr<doubleHyper>) const) &
                       doubleHyper::checkSame,
                   "Check to make sure the vectors exist in the same space");

          py::class_<double1DReg, doubleHyper, std::shared_ptr<double1DReg> >(
              clsVector, "double1DReg", py::buffer_protocol())
              .def(py::init<const int>(), "Initialize giving size")
              .def(py::init<const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const std::shared_ptr<double6DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 6-D hypercube")
              .def(py::init<const std::shared_ptr<double5DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 5-D hypercube")
              .def(py::init<const std::shared_ptr<double4DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 4-D hypercube")
              .def(py::init<const std::shared_ptr<double3DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 3-D hypercube")
              .def(py::init<const std::shared_ptr<double2DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 2-D hypercube")
              .def(py::init<const std::shared_ptr<double1DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 1-D hypercube")
              .def("clone",
                   (std::shared_ptr<double1DReg>(double1DReg::*)() const) &
                       double1DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<double1DReg>(double1DReg::*)() const) &
                       double1DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("allocate", (void (double1DReg::*)()) & double1DReg::allocate,
                   "Allocate the array")
              .def("window",
                   (std::shared_ptr<double1DReg>(double1DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       double1DReg::window,
                   "Window a vector")

              .def_buffer([](double1DReg &m) -> py::buffer_info {
                   return py::buffer_info(m.getVals(), sizeof(double),
                                          py::format_descriptor<double>::format(), 1,
                                          {m.getHyper()->getAxis(1).n}, {sizeof(double)});
              });
          py::class_<double2DReg, doubleHyper, std::shared_ptr<double2DReg> >(
              clsVector, "double2DReg", py::buffer_protocol())
              .def(py::init<const int, const int>(), "Initialize giving size")
              .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
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

          py::class_<double3DReg, doubleHyper, std::shared_ptr<double3DReg> >(
              clsVector, "double3DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def("allocate", (void (double3DReg::*)()) & double3DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<double3DReg>(double3DReg::*)() const) &
                       double3DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<double3DReg>(double3DReg::*)() const) &
                       double3DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<double3DReg>(double3DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       double3DReg::window,
                   "Window a vector")

              .def_buffer([](double3DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(double),
                       py::format_descriptor<double>::format(), 3,
                       {m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(double) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(double) * m.getHyper()->getAxis(1).n, sizeof(double)});
              });

          py::class_<double4DReg, doubleHyper, std::shared_ptr<double4DReg> >(
              clsVector, "double4DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (double4DReg::*)()) & double4DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<double4DReg>(double4DReg::*)() const) &
                       double4DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<double4DReg>(double4DReg::*)() const) &
                       double4DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<double4DReg>(double4DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       double4DReg::window,
                   "Window a vector")
              .def_buffer([](double4DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(double),
                       py::format_descriptor<double>::format(), 4,
                       {m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(double) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(double) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(double) * m.getHyper()->getAxis(1).n, sizeof(double)});
              });
          py::class_<double5DReg, doubleHyper, std::shared_ptr<double5DReg> >(
              clsVector, "double5DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (double5DReg::*)()) & double5DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<double5DReg>(double5DReg::*)() const) &
                       double5DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<double5DReg>(double5DReg::*)() const) &
                       double5DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<double5DReg>(double5DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       double5DReg::window,
                   "Window a vector")
              .def_buffer([](double5DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(double),
                       py::format_descriptor<double>::format(), 5,
                       {m.getHyper()->getAxis(5).n, m.getHyper()->getAxis(4).n,
                        m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(double) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(double) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(double) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(double) * m.getHyper()->getAxis(1).n, sizeof(double)});
              });

          py::class_<double6DReg, doubleHyper, std::shared_ptr<double6DReg> >(
              clsVector, "double6DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (double6DReg::*)()) & double6DReg::allocate,
                   "Allocate the array")
              .def("window",
                   (std::shared_ptr<double6DReg>(double6DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       double6DReg::window,
                   "Window a vector")
              .def("clone",
                   (std::shared_ptr<double6DReg>(double6DReg::*)() const) &
                       double6DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<double6DReg>(double6DReg::*)() const) &
                       double6DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<double6DReg>(double6DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       double6DReg::window,
                   "Window a vector")

              .def_buffer([](double6DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(double),
                       py::format_descriptor<double>::format(), 6,
                       {m.getHyper()->getAxis(6).n, m.getHyper()->getAxis(5).n,
                        m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(double) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n,
                        sizeof(double) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(double) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(double) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(double) * m.getHyper()->getAxis(1).n, sizeof(double)});
              });

          py::class_<double7DReg, doubleHyper, std::shared_ptr<double7DReg> >(
              clsVector, "double7DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (double7DReg::*)()) & double7DReg::allocate,
                   "Allocate the array")
              .def("window",
                   (std::shared_ptr<double7DReg>(double7DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       double6DReg::window,
                   "Window a vector")
              .def("clone",
                   (std::shared_ptr<double7DReg>(double7DReg::*)() const) &
                       double6DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<double7DReg>(double7DReg::*)() const) &
                       double6DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<double7DReg>(double7DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       double6DReg::window,
                   "Window a vector")

              .def_buffer([](double7DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(double),
                       py::format_descriptor<double>::format(), 6,
                       {m.getHyper()->getAxis(7).n, m.getHyper()->getAxis(6).n, m.getHyper()->getAxis(5).n,
                        m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(double) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n * m.getHyper()->getAxis(6).n,
                        sizeof(double) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n,
                        sizeof(double) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(double) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(double) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(double) * m.getHyper()->getAxis(1).n, sizeof(double)});
              });
     }
} // namespace SEP
