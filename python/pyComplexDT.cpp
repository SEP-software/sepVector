
#include "complexDoubleTensor.h"

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

     void init_complexDoubleT(py::module &clsVector)
     {
          /* Float hyper */
          py::class_<complexDoubleTensor1D, complexDoubleHyper, std::shared_ptr<complexDoubleTensor1D> >(
              clsVector, "complexDoubleTensor1D", py::buffer_protocol())
              .def(py::init<const int>(), "Initialize giving size")
              .def(py::init<const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const std::shared_ptr<complexDoubleTensor6D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 6-D hypercube")
              .def(py::init<const std::shared_ptr<complexDoubleTensor5D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 5-D hypercube")
              .def(py::init<const std::shared_ptr<complexDoubleTensor4D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 4-D hypercube")
              .def(py::init<const std::shared_ptr<complexDoubleTensor3D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 3-D hypercube")
              .def(py::init<const std::shared_ptr<complexDoubleTensor2D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 2-D hypercube")
              .def(py::init<const std::shared_ptr<complexDoubleTensor1D>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 1-D hypercube")
              .def("clone",
                   (std::shared_ptr<complexDoubleTensor1D>(complexDoubleTensor1D::*)() const) &
                       complexDoubleTensor1D::clone,
                   "Make a copy of the vector")
              .def("window",
                   (std::shared_ptr<complexDoubleTensor1D>(complexDoubleTensor1D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       complexDoubleTensor1D::window,
                   "Window a vector")

              .def("cloneSpace",
                   (std::shared_ptr<complexDoubleTensor1D>(complexDoubleTensor1D::*)() const) &
                       complexDoubleTensor1D::cloneSpace,
                   "Make a copy of the vector space")
              .def("allocate", (void (complexDoubleTensor1D::*)()) & complexDoubleTensor1D::allocate,
                   "Allocate the array")

              .def_buffer([](complexDoubleTensor1D &m) -> py::buffer_info {
                   return py::buffer_info(m.getVals(), sizeof(float),
                                          py::format_descriptor<float>::format(), 1,
                                          {m.getHyper()->getAxis(1).n}, {sizeof(float)});
              });
          py::class_<complexDoubleTensor2D, floatHyper, std::shared_ptr<complexDoubleTensor2D> >(
              clsVector, "complexDoubleTensor2D", py::buffer_protocol())
              .def(py::init<const int, const int>(), "Initialize giving size")
              .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const std::shared_ptr<complexDoubleTensor6D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 6-D hypercube")
              .def(py::init<const std::shared_ptr<complexDoubleTensor5D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 5-D hypercube")
              .def(py::init<const std::shared_ptr<complexDoubleTensor4D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 4-D hypercube")
              .def(py::init<const std::shared_ptr<complexDoubleTensor3D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 3-D hypercube")
              .def(py::init<const std::shared_ptr<complexDoubleTensor2D>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 2-D hypercube")
              .def("clone",
                   (std::shared_ptr<complexDoubleTensor2D>(complexDoubleTensor2D::*)() const) &
                       complexDoubleTensor2D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<complexDoubleTensor2D>(complexDoubleTensor2D::*)() const) &
                       complexDoubleTensor2D::cloneSpace,
                   "Make a copy of the vector space")
              .def("allocate", (void (complexDoubleTensor2D::*)()) & complexDoubleTensor2D::allocate,
                   "Allocate the array")
              .def("window",
                   (std::shared_ptr<complexDoubleTensor2D>(complexDoubleTensor2D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       complexDoubleTensor2D::window,
                   "Window a vector")

              .def_buffer([](complexDoubleTensor2D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(float), py::format_descriptor<float>::format(),
                       2, {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(float) * m.getHyper()->getAxis(1).n, sizeof(float)});
              });

          py::class_<complexDoubleTensor3D, floatHyper, std::shared_ptr<complexDoubleTensor3D> >(
              clsVector, "complexDoubleTensor3D", py::buffer_protocol())
              .def(py::init<const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def("allocate", (void (complexDoubleTensor3D::*)()) & complexDoubleTensor3D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<complexDoubleTensor3D>(complexDoubleTensor3D::*)() const) &
                       complexDoubleTensor3D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<complexDoubleTensor3D>(complexDoubleTensor3D::*)() const) &
                       complexDoubleTensor3D::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<complexDoubleTensor3D>(complexDoubleTensor3D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       complexDoubleTensor3D::window,
                   "Window a vector")

              .def_buffer([](complexDoubleTensor3D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(float), py::format_descriptor<float>::format(),
                       3,
                       {m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(float) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(float) * m.getHyper()->getAxis(1).n, sizeof(float)});
              });

          py::class_<complexDoubleTensor4D, floatHyper, std::shared_ptr<complexDoubleTensor4D> >(
              clsVector, "complexDoubleTensor4D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (complexDoubleTensor4D::*)()) & complexDoubleTensor4D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<complexDoubleTensor4D>(complexDoubleTensor4D::*)() const) &
                       complexDoubleTensor4D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<complexDoubleTensor4D>(complexDoubleTensor4D::*)() const) &
                       complexDoubleTensor4D::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<complexDoubleTensor4D>(complexDoubleTensor4D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       complexDoubleTensor4D::window,
                   "Window a vector")

              .def_buffer([](complexDoubleTensor4D &m) -> py::buffer_info {
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
          py::class_<complexDoubleTensor5D, floatHyper, std::shared_ptr<complexDoubleTensor5D> >(
              clsVector, "complexDoubleTensor5D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (complexDoubleTensor5D::*)()) & complexDoubleTensor5D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<complexDoubleTensor5D>(complexDoubleTensor5D::*)() const) &
                       complexDoubleTensor5D::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<complexDoubleTensor5D>(complexDoubleTensor5D::*)() const) &
                       complexDoubleTensor5D::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<complexDoubleTensor5D>(complexDoubleTensor5D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       complexDoubleTensor5D::window,
                   "Window a vector")

              .def_buffer([](complexDoubleTensor5D &m) -> py::buffer_info {
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

          py::class_<complexDoubleTensor6D, floatHyper, std::shared_ptr<complexDoubleTensor6D> >(
              clsVector, "complexDoubleTensor6D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (complexDoubleTensor6D::*)()) & complexDoubleTensor6D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<complexDoubleTensor6D>(complexDoubleTensor6D::*)() const) &
                       complexDoubleTensor6D::clone,
                   "Make a copy of the vector")
              .def("window",
                   (std::shared_ptr<complexDoubleTensor6D>(complexDoubleTensor6D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       complexDoubleTensor6D::window,
                   "Window a vector")

              .def("cloneSpace",
                   (std::shared_ptr<complexDoubleTensor6D>(complexDoubleTensor6D::*)() const) &
                       complexDoubleTensor6D::cloneSpace,
                   "Make a copy of the vector space")
              .def_buffer([](complexDoubleTensor6D &m) -> py::buffer_info {
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
          py::class_<complexDoubleTensor7D, floatHyper, std::shared_ptr<complexDoubleTensor7D> >(
              clsVector, "complexDoubleTensor7D", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (complexDoubleTensor7D::*)()) & complexDoubleTensor7D::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<complexDoubleTensor7D>(complexDoubleTensor7D::*)() const) &
                       complexDoubleTensor7D::clone,
                   "Make a copy of the vector")
              .def("window",
                   (std::shared_ptr<complexDoubleTensor7D>(complexDoubleTensor7D::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       complexDoubleTensor7D::window,
                   "Window a vector")

              .def("cloneSpace",
                   (std::shared_ptr<complexDoubleTensor7D>(complexDoubleTensor7D::*)() const) &
                       complexDoubleTensor7D::cloneSpace,
                   "Make a copy of the vector space")
              .def_buffer([](complexDoubleTensor7D &m) -> py::buffer_info {
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
