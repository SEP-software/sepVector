
#include "longTensor.h"

#include "regSpace.h"
#include "sepVectorConfig.h"
#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace SEP
{

     void init_longT(py::module &clsVector)
     {
          /* int hyper */
          py::class_<longTensor1D, longHyper, std::shared_ptr<longTensor1D> >(
              clsVector, "longTensor1D", py::buffer_protocol())
              .def(py::init<const int>(), "Initialize giving size")
              .def(py::init<const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const std::shared_ptr<longTensor6D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 6-D hypercube")
              .def(py::init<const std::shared_ptr<longTensor5D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 5-D hypercube")
              .def(py::init<const std::shared_ptr<longTensor4D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 4-D hypercube")
              .def(py::init<const std::shared_ptr<longTensor3D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 3-D hypercube")
              .def(py::init<const std::shared_ptr<longTensor2D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 2-D hypercube")
              .def(py::init<const std::shared_ptr<longTensor1D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 1-D hypercube")
              .def("clone",
                   (std::shared_ptr<longTensor1D>(longTensor1D::*)() const) &
                       longTensor1D::clone,
                   "Make a copy of the vector")
              .def("window",
                   (std::shared_ptr<longTensor1D>(longTensor1D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       longTensor1D::window,
                   "Window a vector")

              .def("cloneSpace",
                   (std::shared_ptr<longTensor1D>(longTensor1D::*)() const) &
                       longTensor1D::cloneSpace,
                   "Make a copy of the vector space")
              .def("allocate", (void (longTensor1D::*)()) & longTensor1D::allocate,
                   "Allocate the array")

              .def_buffer([](longTensor1D &m) -> py::buffer_info {
                   return py::buffer_info(m.getVals(), sizeof(long long),
                                          py::format_descriptor<int>::format(), 1,
                                          {m.getHyper()->getAxis(1).n}, {sizeof(long long)});
              });
          py::class_<longTensor2D, longHyper, std::shared_ptr<longTensor2D> >(
              clsVector, "longTensor2D", py::buffer_protocol())
              .def(py::init<const int, const int>(), "Initialize giving size")
              .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const std::shared_ptr<longTensor6D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 6-D hypercube")
              .def(py::init<const std::shared_ptr<longTensor5D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 5-D hypercube")
              .def(py::init<const std::shared_ptr<longTensor4D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 4-D hypercube")
              .def(py::init<const std::shared_ptr<longTensor3D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 3-D hypercube")
              .def(py::init<const std::shared_ptr<longTensor2D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 2-D hypercube")
              .def("clone",
                   (std::shared_ptr<longTensor2D>(longTensor2D::*)() const) &
                       longTensor2D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<longTensor2D>(longTensor2D::*)() const) &
                       longTensor2D::cloneSpace,
                   "Make a copy of the vector space")
              .def("allocate", (void (longTensor2D::*)()) & longTensor2D::allocate,
                   "Allocate the array")
              .def("window",
                   (std::shared_ptr<longTensor2D>(longTensor2D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       longTensor2D::window,
                   "Window a vector")

              .def_buffer([](longTensor2D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(long long), py::format_descriptor<int>::format(),
                       2, {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(long long) * m.getHyper()->getAxis(1).n, sizeof(long long)});
              });

          py::class_<longTensor3D, longHyper, std::shared_ptr<longTensor3D> >(
              clsVector, "longTensor3D", py::buffer_protocol())
              .def(py::init<const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def("allocate", (void (longTensor3D::*)()) & longTensor3D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<longTensor3D>(longTensor3D::*)() const) &
                       longTensor3D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<longTensor3D>(longTensor3D::*)() const) &
                       longTensor3D::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<longTensor3D>(longTensor3D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       longTensor3D::window,
                   "Window a vector")

              .def_buffer([](longTensor3D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(long long), py::format_descriptor<int>::format(),
                       3,
                       {m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(long long) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(long long) * m.getHyper()->getAxis(1).n, sizeof(long long)});
              });

          py::class_<longTensor4D, longHyper, std::shared_ptr<longTensor4D> >(
              clsVector, "longTensor4D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (longTensor4D::*)()) & longTensor4D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<longTensor4D>(longTensor4D::*)() const) &
                       longTensor4D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<longTensor4D>(longTensor4D::*)() const) &
                       longTensor4D::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<longTensor4D>(longTensor4D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       longTensor4D::window,
                   "Window a vector")

              .def_buffer([](longTensor4D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(long long), py::format_descriptor<int>::format(),
                       4,
                       {m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(long long) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(long long) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(long long) * m.getHyper()->getAxis(1).n, sizeof(long long)});
              });
          py::class_<longTensor5D, longHyper, std::shared_ptr<longTensor5D> >(
              clsVector, "longTensor5D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (longTensor5D::*)()) & longTensor5D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<longTensor5D>(longTensor5D::*)() const) &
                       longTensor5D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<longTensor5D>(longTensor5D::*)() const) &
                       longTensor5D::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<longTensor5D>(longTensor5D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       longTensor5D::window,
                   "Window a vector")

              .def_buffer([](longTensor5D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(long long), py::format_descriptor<int>::format(),
                       5,
                       {m.getHyper()->getAxis(5).n, m.getHyper()->getAxis(4).n,
                        m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(long long) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(long long) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(long long) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(long long) * m.getHyper()->getAxis(1).n, sizeof(long long)});
              });

          py::class_<longTensor6D, longHyper, std::shared_ptr<longTensor6D> >(
              clsVector, "longTensor6D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (longTensor6D::*)()) & longTensor6D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<longTensor6D>(longTensor6D::*)() const) &
                       longTensor6D::clone,
                   "Make a copy of the vector")
              .def("window",
                   (std::shared_ptr<longTensor6D>(longTensor6D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       longTensor6D::window,
                   "Window a vector")

              .def("cloneSpace",
                   (std::shared_ptr<longTensor6D>(longTensor6D::*)() const) &
                       longTensor6D::cloneSpace,
                   "Make a copy of the vector space")
              .def_buffer([](longTensor6D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(long long), py::format_descriptor<int>::format(),
                       6,
                       {m.getHyper()->getAxis(6).n, m.getHyper()->getAxis(5).n,
                        m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(long long) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n,
                        sizeof(long long) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(long long) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(long long) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(long long) * m.getHyper()->getAxis(1).n, sizeof(long long)});
              });
          py::class_<longTensor7D, longHyper, std::shared_ptr<longTensor7D> >(
              clsVector, "longTensor7D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (longTensor7D::*)()) & longTensor7D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<longTensor7D>(longTensor7D::*)() const) &
                       longTensor7D::clone,
                   "Make a copy of the vector")
              .def("window",
                   (std::shared_ptr<longTensor7D>(longTensor7D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       longTensor7D::window,
                   "Window a vector")

              .def("cloneSpace",
                   (std::shared_ptr<longTensor7D>(longTensor7D::*)() const) &
                       longTensor7D::cloneSpace,
                   "Make a copy of the vector space")
              .def_buffer([](longTensor7D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(long long), py::format_descriptor<int>::format(),
                       7,
                       {m.getHyper()->getAxis(7).n, m.getHyper()->getAxis(6).n, m.getHyper()->getAxis(5).n,
                        m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(long long) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n * m.getHyper()->getAxis(6).n,
                        sizeof(long long) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n,
                        sizeof(long long) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(long long) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(long long) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(long long) * m.getHyper()->getAxis(1).n, sizeof(long long)});
              });
     }

} // namespace SEP
