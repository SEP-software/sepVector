
#include "byteTensor.h"

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

     void init_byteT(py::module &clsVector)
     {
          /* Float hyper */
          py::class_<byteTensor1D, byteHyper, std::shared_ptr<byteTensor1D> >(
              clsVector, "byteTensor1D", py::buffer_protocol())
              .def(py::init<const int>(), "Initialize giving size")
              .def(py::init<const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const std::shared_ptr<byteTensor6D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 6-D hypercube")
              .def(py::init<const std::shared_ptr<byteTensor5D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 5-D hypercube")
              .def(py::init<const std::shared_ptr<byteTensor4D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 4-D hypercube")
              .def(py::init<const std::shared_ptr<byteTensor3D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 3-D hypercube")
              .def(py::init<const std::shared_ptr<byteTensor2D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 2-D hypercube")
              .def(py::init<const std::shared_ptr<byteTensor1D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 1-D hypercube")
              .def("clone",
                   (std::shared_ptr<byteTensor1D>(byteTensor1D::*)() const) &
                       byteTensor1D::clone,
                   "Make a copy of the vector")
              .def("window",
                   (std::shared_ptr<byteTensor1D>(byteTensor1D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       byteTensor1D::window,
                   "Window a vector")

              .def("cloneSpace",
                   (std::shared_ptr<byteTensor1D>(byteTensor1D::*)() const) &
                       byteTensor1D::cloneSpace,
                   "Make a copy of the vector space")
              .def("allocate", (void (byteTensor1D::*)()) & byteTensor1D::allocate,
                   "Allocate the array")

              .def_buffer([](byteTensor1D &m) -> py::buffer_info {
                   return py::buffer_info(m.getVals(), sizeof(float),
                                          py::format_descriptor<float>::format(), 1,
                                          {m.getHyper()->getAxis(1).n}, {sizeof(float)});
              });
          py::class_<byteTensor2D, floatHyper, std::shared_ptr<byteTensor2D> >(
              clsVector, "byteTensor2D", py::buffer_protocol())
              .def(py::init<const int, const int>(), "Initialize giving size")
              .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const std::shared_ptr<byteTensor6D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 6-D hypercube")
              .def(py::init<const std::shared_ptr<byteTensor5D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 5-D hypercube")
              .def(py::init<const std::shared_ptr<byteTensor4D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 4-D hypercube")
              .def(py::init<const std::shared_ptr<byteTensor3D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 3-D hypercube")
              .def(py::init<const std::shared_ptr<byteTensor2D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 2-D hypercube")
              .def("clone",
                   (std::shared_ptr<byteTensor2D>(byteTensor2D::*)() const) &
                       byteTensor2D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<byteTensor2D>(byteTensor2D::*)() const) &
                       byteTensor2D::cloneSpace,
                   "Make a copy of the vector space")
              .def("allocate", (void (byteTensor2D::*)()) & byteTensor2D::allocate,
                   "Allocate the array")
              .def("window",
                   (std::shared_ptr<byteTensor2D>(byteTensor2D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       byteTensor2D::window,
                   "Window a vector")

              .def_buffer([](byteTensor2D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(float), py::format_descriptor<float>::format(),
                       2, {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(float) * m.getHyper()->getAxis(1).n, sizeof(float)});
              });

          py::class_<byteTensor3D, floatHyper, std::shared_ptr<byteTensor3D> >(
              clsVector, "byteTensor3D", py::buffer_protocol())
              .def(py::init<const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def("allocate", (void (byteTensor3D::*)()) & byteTensor3D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<byteTensor3D>(byteTensor3D::*)() const) &
                       byteTensor3D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<byteTensor3D>(byteTensor3D::*)() const) &
                       byteTensor3D::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<byteTensor3D>(byteTensor3D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       byteTensor3D::window,
                   "Window a vector")

              .def_buffer([](byteTensor3D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(float), py::format_descriptor<float>::format(),
                       3,
                       {m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(float) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(float) * m.getHyper()->getAxis(1).n, sizeof(float)});
              });

          py::class_<byteTensor4D, floatHyper, std::shared_ptr<byteTensor4D> >(
              clsVector, "byteTensor4D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (byteTensor4D::*)()) & byteTensor4D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<byteTensor4D>(byteTensor4D::*)() const) &
                       byteTensor4D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<byteTensor4D>(byteTensor4D::*)() const) &
                       byteTensor4D::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<byteTensor4D>(byteTensor4D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       byteTensor4D::window,
                   "Window a vector")

              .def_buffer([](byteTensor4D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(float), py::format_descriptor<float>::format(),
                       4,
                       {m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(float) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(float) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(float) * m.getHyper()->getAxis(1).n, sizeof(float)});
              });
          py::class_<byteTensor5D, floatHyper, std::shared_ptr<byteTensor5D> >(
              clsVector, "byteTensor5D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (byteTensor5D::*)()) & byteTensor5D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<byteTensor5D>(byteTensor5D::*)() const) &
                       byteTensor5D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<byteTensor5D>(byteTensor5D::*)() const) &
                       byteTensor5D::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<byteTensor5D>(byteTensor5D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       byteTensor5D::window,
                   "Window a vector")

              .def_buffer([](byteTensor5D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(float), py::format_descriptor<float>::format(),
                       5,
                       {m.getHyper()->getAxis(5).n, m.getHyper()->getAxis(4).n,
                        m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(float) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(float) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(float) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(float) * m.getHyper()->getAxis(1).n, sizeof(float)});
              });

          py::class_<byteTensor6D, floatHyper, std::shared_ptr<byteTensor6D> >(
              clsVector, "byteTensor6D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (byteTensor6D::*)()) & byteTensor6D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<byteTensor6D>(byteTensor6D::*)() const) &
                       byteTensor6D::clone,
                   "Make a copy of the vector")
              .def("window",
                   (std::shared_ptr<byteTensor6D>(byteTensor6D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       byteTensor6D::window,
                   "Window a vector")

              .def("cloneSpace",
                   (std::shared_ptr<byteTensor6D>(byteTensor6D::*)() const) &
                       byteTensor6D::cloneSpace,
                   "Make a copy of the vector space")
              .def_buffer([](byteTensor6D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(float), py::format_descriptor<float>::format(),
                       6,
                       {m.getHyper()->getAxis(6).n, m.getHyper()->getAxis(5).n,
                        m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(float) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n,
                        sizeof(float) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(float) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(float) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(float) * m.getHyper()->getAxis(1).n, sizeof(float)});
              });
          py::class_<byteTensor7D, floatHyper, std::shared_ptr<byteTensor7D> >(
              clsVector, "byteTensor7D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (byteTensor7D::*)()) & byteTensor7D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<byteTensor7D>(byteTensor7D::*)() const) &
                       byteTensor7D::clone,
                   "Make a copy of the vector")
              .def("window",
                   (std::shared_ptr<byteTensor7D>(byteTensor7D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       byteTensor7D::window,
                   "Window a vector")

              .def("cloneSpace",
                   (std::shared_ptr<byteTensor7D>(byteTensor7D::*)() const) &
                       byteTensor7D::cloneSpace,
                   "Make a copy of the vector space")
              .def_buffer([](byteTensor7D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(float), py::format_descriptor<float>::format(),
                       7,
                       {m.getHyper()->getAxis(7).n, m.getHyper()->getAxis(6).n, m.getHyper()->getAxis(5).n,
                        m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(float) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n * m.getHyper()->getAxis(6).n,
                        sizeof(float) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n,
                        sizeof(float) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(float) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(float) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(float) * m.getHyper()->getAxis(1).n, sizeof(float)});
              });
     }

} // namespace SEP
