
#include "doubleTensor.h"

#include "regSpace.h"
#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace SEP
{

     void init_doubleT(py::module &clsVector)
     {
          /* double hyper */
          py::class_<doubleTensor1D, doubleHyper, std::shared_ptr<doubleTensor1D> >(
              clsVector, "doubleTensor1D", py::buffer_protocol())
              .def(py::init<const int>(), "Initialize giving size")
              .def(py::init<const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const std::shared_ptr<doubleTensor6D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 6-D hypercube")
              .def(py::init<const std::shared_ptr<doubleTensor5D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 5-D hypercube")
              .def(py::init<const std::shared_ptr<doubleTensor4D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 4-D hypercube")
              .def(py::init<const std::shared_ptr<doubleTensor3D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 3-D hypercube")
              .def(py::init<const std::shared_ptr<doubleTensor2D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 2-D hypercube")
              .def(py::init<const std::shared_ptr<doubleTensor1D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 1-D hypercube")
              .def("clone",
                   (std::shared_ptr<doubleTensor1D>(doubleTensor1D::*)() const) &
                       doubleTensor1D::clone,
                   "Make a copy of the vector")
              .def("window",
                   (std::shared_ptr<doubleTensor1D>(doubleTensor1D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       doubleTensor1D::window,
                   "Window a vector")

              .def("cloneSpace",
                   (std::shared_ptr<doubleTensor1D>(doubleTensor1D::*)() const) &
                       doubleTensor1D::cloneSpace,
                   "Make a copy of the vector space")
              .def("allocate", (void (doubleTensor1D::*)()) & doubleTensor1D::allocate,
                   "Allocate the array")

              .def_buffer([](doubleTensor1D &m) -> py::buffer_info {
                   return py::buffer_info(m.getVals(), sizeof(double),
                                          py::format_descriptor<double>::format(), 1,
                                          {m.getHyper()->getAxis(1).n}, {sizeof(double)});
              });
          py::class_<doubleTensor2D, doubleHyper, std::shared_ptr<doubleTensor2D> >(
              clsVector, "doubleTensor2D", py::buffer_protocol())
              .def(py::init<const int, const int>(), "Initialize giving size")
              .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const std::shared_ptr<doubleTensor6D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 6-D hypercube")
              .def(py::init<const std::shared_ptr<doubleTensor5D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 5-D hypercube")
              .def(py::init<const std::shared_ptr<doubleTensor4D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 4-D hypercube")
              .def(py::init<const std::shared_ptr<doubleTensor3D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 3-D hypercube")
              .def(py::init<const std::shared_ptr<doubleTensor2D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 2-D hypercube")
              .def("clone",
                   (std::shared_ptr<doubleTensor2D>(doubleTensor2D::*)() const) &
                       doubleTensor2D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<doubleTensor2D>(doubleTensor2D::*)() const) &
                       doubleTensor2D::cloneSpace,
                   "Make a copy of the vector space")
              .def("allocate", (void (doubleTensor2D::*)()) & doubleTensor2D::allocate,
                   "Allocate the array")
              .def("window",
                   (std::shared_ptr<doubleTensor2D>(doubleTensor2D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       doubleTensor2D::window,
                   "Window a vector")

              .def_buffer([](doubleTensor2D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(double), py::format_descriptor<double>::format(),
                       2, {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(double) * m.getHyper()->getAxis(1).n, sizeof(double)});
              });

          py::class_<doubleTensor3D, doubleHyper, std::shared_ptr<doubleTensor3D> >(
              clsVector, "doubleTensor3D", py::buffer_protocol())
              .def(py::init<const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def("allocate", (void (doubleTensor3D::*)()) & doubleTensor3D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<doubleTensor3D>(doubleTensor3D::*)() const) &
                       doubleTensor3D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<doubleTensor3D>(doubleTensor3D::*)() const) &
                       doubleTensor3D::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<doubleTensor3D>(doubleTensor3D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       doubleTensor3D::window,
                   "Window a vector")

              .def_buffer([](doubleTensor3D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(double), py::format_descriptor<double>::format(),
                       3,
                       {m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(double) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(double) * m.getHyper()->getAxis(1).n, sizeof(double)});
              });

          py::class_<doubleTensor4D, doubleHyper, std::shared_ptr<doubleTensor4D> >(
              clsVector, "doubleTensor4D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (doubleTensor4D::*)()) & doubleTensor4D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<doubleTensor4D>(doubleTensor4D::*)() const) &
                       doubleTensor4D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<doubleTensor4D>(doubleTensor4D::*)() const) &
                       doubleTensor4D::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<doubleTensor4D>(doubleTensor4D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       doubleTensor4D::window,
                   "Window a vector")

              .def_buffer([](doubleTensor4D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(double), py::format_descriptor<double>::format(),
                       4,
                       {m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(double) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(double) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(double) * m.getHyper()->getAxis(1).n, sizeof(double)});
              });
          py::class_<doubleTensor5D, doubleHyper, std::shared_ptr<doubleTensor5D> >(
              clsVector, "doubleTensor5D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (doubleTensor5D::*)()) & doubleTensor5D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<doubleTensor5D>(doubleTensor5D::*)() const) &
                       doubleTensor5D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<doubleTensor5D>(doubleTensor5D::*)() const) &
                       doubleTensor5D::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<doubleTensor5D>(doubleTensor5D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       doubleTensor5D::window,
                   "Window a vector")

              .def_buffer([](doubleTensor5D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(double), py::format_descriptor<double>::format(),
                       5,
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

          py::class_<doubleTensor6D, doubleHyper, std::shared_ptr<doubleTensor6D> >(
              clsVector, "doubleTensor6D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (doubleTensor6D::*)()) & doubleTensor6D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<doubleTensor6D>(doubleTensor6D::*)() const) &
                       doubleTensor6D::clone,
                   "Make a copy of the vector")
              .def("window",
                   (std::shared_ptr<doubleTensor6D>(doubleTensor6D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       doubleTensor6D::window,
                   "Window a vector")

              .def("cloneSpace",
                   (std::shared_ptr<doubleTensor6D>(doubleTensor6D::*)() const) &
                       doubleTensor6D::cloneSpace,
                   "Make a copy of the vector space")
              .def_buffer([](doubleTensor6D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(double), py::format_descriptor<double>::format(),
                       6,
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
          py::class_<doubleTensor7D, doubleHyper, std::shared_ptr<doubleTensor7D> >(
              clsVector, "doubleTensor7D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (doubleTensor7D::*)()) & doubleTensor7D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<doubleTensor7D>(doubleTensor7D::*)() const) &
                       doubleTensor7D::clone,
                   "Make a copy of the vector")
              .def("window",
                   (std::shared_ptr<doubleTensor7D>(doubleTensor7D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       doubleTensor7D::window,
                   "Window a vector")

              .def("cloneSpace",
                   (std::shared_ptr<doubleTensor7D>(doubleTensor7D::*)() const) &
                       doubleTensor7D::cloneSpace,
                   "Make a copy of the vector space")
              .def_buffer([](doubleTensor7D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(double), py::format_descriptor<double>::format(),
                       7,
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
