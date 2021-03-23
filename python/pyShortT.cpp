
#include "shortTensor.h"

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

     void init_shortT(py::module &clsVector)
     {
          /* short hyper */
          py::class_<shortTensor1D, shortHyper, std::shared_ptr<shortTensor1D> >(
              clsVector, "shortTensor1D", py::buffer_protocol())
              .def(py::init<const int>(), "Initialize giving size")
              .def(py::init<const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const std::shared_ptr<shortTensor6D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 6-D hypercube")
              .def(py::init<const std::shared_ptr<shortTensor5D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 5-D hypercube")
              .def(py::init<const std::shared_ptr<shortTensor4D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 4-D hypercube")
              .def(py::init<const std::shared_ptr<shortTensor3D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 3-D hypercube")
              .def(py::init<const std::shared_ptr<shortTensor2D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 2-D hypercube")
              .def(py::init<const std::shared_ptr<shortTensor1D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 1-D hypercube")
              .def("clone",
                   (std::shared_ptr<shortTensor1D>(shortTensor1D::*)() const) &
                       shortTensor1D::clone,
                   "Make a copy of the vector")
              .def("window",
                   (std::shared_ptr<shortTensor1D>(shortTensor1D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       shortTensor1D::window,
                   "Window a vector")

              .def("cloneSpace",
                   (std::shared_ptr<shortTensor1D>(shortTensor1D::*)() const) &
                       shortTensor1D::cloneSpace,
                   "Make a copy of the vector space")
              .def("allocate", (void (shortTensor1D::*)()) & shortTensor1D::allocate,
                   "Allocate the array")

              .def_buffer([](shortTensor1D &m) -> py::buffer_info {
                   return py::buffer_info(m.getVals(), sizeof(short),
                                          py::format_descriptor<short>::format(), 1,
                                          {m.getHyper()->getAxis(1).n}, {sizeof(short)});
              });
          py::class_<shortTensor2D, shortHyper, std::shared_ptr<shortTensor2D> >(
              clsVector, "shortTensor2D", py::buffer_protocol())
              .def(py::init<const int, const int>(), "Initialize giving size")
              .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const std::shared_ptr<shortTensor6D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 6-D hypercube")
              .def(py::init<const std::shared_ptr<shortTensor5D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 5-D hypercube")
              .def(py::init<const std::shared_ptr<shortTensor4D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 4-D hypercube")
              .def(py::init<const std::shared_ptr<shortTensor3D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 3-D hypercube")
              .def(py::init<const std::shared_ptr<shortTensor2D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 2-D hypercube")
              .def("clone",
                   (std::shared_ptr<shortTensor2D>(shortTensor2D::*)() const) &
                       shortTensor2D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<shortTensor2D>(shortTensor2D::*)() const) &
                       shortTensor2D::cloneSpace,
                   "Make a copy of the vector space")
              .def("allocate", (void (shortTensor2D::*)()) & shortTensor2D::allocate,
                   "Allocate the array")
              .def("window",
                   (std::shared_ptr<shortTensor2D>(shortTensor2D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       shortTensor2D::window,
                   "Window a vector")

              .def_buffer([](shortTensor2D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(short), py::format_descriptor<short>::format(),
                       2, {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(short) * m.getHyper()->getAxis(1).n, sizeof(short)});
              });

          py::class_<shortTensor3D, shortHyper, std::shared_ptr<shortTensor3D> >(
              clsVector, "shortTensor3D", py::buffer_protocol())
              .def(py::init<const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def("allocate", (void (shortTensor3D::*)()) & shortTensor3D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<shortTensor3D>(shortTensor3D::*)() const) &
                       shortTensor3D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<shortTensor3D>(shortTensor3D::*)() const) &
                       shortTensor3D::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<shortTensor3D>(shortTensor3D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       shortTensor3D::window,
                   "Window a vector")

              .def_buffer([](shortTensor3D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(short), py::format_descriptor<short>::format(),
                       3,
                       {m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(short) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(short) * m.getHyper()->getAxis(1).n, sizeof(short)});
              });

          py::class_<shortTensor4D, shortHyper, std::shared_ptr<shortTensor4D> >(
              clsVector, "shortTensor4D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (shortTensor4D::*)()) & shortTensor4D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<shortTensor4D>(shortTensor4D::*)() const) &
                       shortTensor4D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<shortTensor4D>(shortTensor4D::*)() const) &
                       shortTensor4D::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<shortTensor4D>(shortTensor4D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       shortTensor4D::window,
                   "Window a vector")

              .def_buffer([](shortTensor4D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(short), py::format_descriptor<short>::format(),
                       4,
                       {m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(short) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(short) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(short) * m.getHyper()->getAxis(1).n, sizeof(short)});
              });
          py::class_<shortTensor5D, shortHyper, std::shared_ptr<shortTensor5D> >(
              clsVector, "shortTensor5D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (shortTensor5D::*)()) & shortTensor5D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<shortTensor5D>(shortTensor5D::*)() const) &
                       shortTensor5D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<shortTensor5D>(shortTensor5D::*)() const) &
                       shortTensor5D::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<shortTensor5D>(shortTensor5D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       shortTensor5D::window,
                   "Window a vector")

              .def_buffer([](shortTensor5D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(short), py::format_descriptor<short>::format(),
                       5,
                       {m.getHyper()->getAxis(5).n, m.getHyper()->getAxis(4).n,
                        m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(short) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(short) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(short) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(short) * m.getHyper()->getAxis(1).n, sizeof(short)});
              });

          py::class_<shortTensor6D, shortHyper, std::shared_ptr<shortTensor6D> >(
              clsVector, "shortTensor6D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (shortTensor6D::*)()) & shortTensor6D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<shortTensor6D>(shortTensor6D::*)() const) &
                       shortTensor6D::clone,
                   "Make a copy of the vector")
              .def("window",
                   (std::shared_ptr<shortTensor6D>(shortTensor6D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       shortTensor6D::window,
                   "Window a vector")

              .def("cloneSpace",
                   (std::shared_ptr<shortTensor6D>(shortTensor6D::*)() const) &
                       shortTensor6D::cloneSpace,
                   "Make a copy of the vector space")
              .def_buffer([](shortTensor6D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(short), py::format_descriptor<short>::format(),
                       6,
                       {m.getHyper()->getAxis(6).n, m.getHyper()->getAxis(5).n,
                        m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(short) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n,
                        sizeof(short) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(short) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(short) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(short) * m.getHyper()->getAxis(1).n, sizeof(short)});
              });
          py::class_<shortTensor7D, shortHyper, std::shared_ptr<shortTensor7D> >(
              clsVector, "shortTensor7D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (shortTensor7D::*)()) & shortTensor7D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<shortTensor7D>(shortTensor7D::*)() const) &
                       shortTensor7D::clone,
                   "Make a copy of the vector")
              .def("window",
                   (std::shared_ptr<shortTensor7D>(shortTensor7D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       shortTensor7D::window,
                   "Window a vector")

              .def("cloneSpace",
                   (std::shared_ptr<shortTensor7D>(shortTensor7D::*)() const) &
                       shortTensor7D::cloneSpace,
                   "Make a copy of the vector space")
              .def_buffer([](shortTensor7D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(short), py::format_descriptor<short>::format(),
                       7,
                       {m.getHyper()->getAxis(7).n, m.getHyper()->getAxis(6).n, m.getHyper()->getAxis(5).n,
                        m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(short) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n * m.getHyper()->getAxis(6).n,
                        sizeof(short) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n,
                        sizeof(short) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(short) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(short) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(short) * m.getHyper()->getAxis(1).n, sizeof(short)});
              });
     }

} // namespace SEP
