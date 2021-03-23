#include "byte1DReg.h"
#include "byte2DReg.h"
#include "byte3DReg.h"
#include "byte4DReg.h"
#include "byte5DReg.h"
#include "byte6DReg.h"

#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;
namespace SEP
{

     void init_byteR(py::module &clsVector)
     {

          py::class_<byteHyper, regSpace, std::shared_ptr<byteHyper> >(clsVector,
                                                                       "byteHyper") //
              .def(py::init<>(), "Initlialize a new byte Hyper (don't use this")
              .def("getSpaceOnly", (bool (byteHyper::*)()) & byteHyper::getSpaceOnly,
                   "Check to see if this only a description of the vector space")

              .def("setData",
                   (void (byteHyper::*)(unsigned char *)) & byteHyper::setData,
                   "Set the data pointer")
              .def("getVals", (unsigned char *(byteHyper::*)()) & byteHyper::getVals,
                   "Get the data pointer")
              .def("calcHisto",
                   (void (byteHyper::*)(std::shared_ptr<int1DReg>, float, float)) &
                       byteHyper::calcHisto,
                   "Calculate histogram")
              .def("isDifferent",
                   (bool (byteHyper::*)(std::shared_ptr<byteHyper>)) &
                       byteHyper::isDifferent,
                   "Check to  see if two vectors are different")

              .def_property("_vals", &byteHyper::getVals, &byteHyper::setData,
                            py::return_value_policy::reference)
              .def("clip",
                   (void (byteHyper::*)(const int, const int)) & byteHyper::clip,
                   "Clip a dataset given minumum and maximum value")
              .def("cent",
                   (unsigned char (byteHyper::*)(const float, const int) const) &
                       byteHyper::cent,
                   "Calculate  the percentile of a dataset")
              .def("calcCheckSum",
                   (unsigned char (byteHyper::*)() const) & byteHyper::calcCheckSum,
                   "Calculate checksum of a vector")

              .def("zero", (void (byteHyper::*)()) & byteHyper::zero,
                   "Fill a vector with zero")
              .def("set", (void (byteHyper::*)(const unsigned char)) & byteHyper::set,
                   "Fill a vector with a value")
              .def("rand", (void (byteHyper::*)()) & byteHyper::random,
                   "Fill a vector with random number")

              .def("checkSame",
                   (bool (byteHyper::*)(const std::shared_ptr<byteHyper>) const) &
                       byteHyper::checkSame,
                   "Check to make sure the vectors exist in the same space");

          py::class_<byte1DReg, byteHyper, std::shared_ptr<byte1DReg> >(
              clsVector, "byte1DReg", py::buffer_protocol())
              .def(py::init<const int>(), "Initialize giving size")
              .def(py::init<const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const std::shared_ptr<byte6DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 6-D hypercube")
              .def(py::init<const std::shared_ptr<byte5DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 5-D hypercube")
              .def(py::init<const std::shared_ptr<byte4DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 4-D hypercube")
              .def(py::init<const std::shared_ptr<byte3DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 3-D hypercube")
              .def(py::init<const std::shared_ptr<byte2DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 2-D hypercube")
              .def(py::init<const std::shared_ptr<byte1DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 1-D hypercube")
              .def("clone",
                   (std::shared_ptr<byte1DReg>(byte1DReg::*)() const) &
                       byte1DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<byte1DReg>(byte1DReg::*)() const) &
                       byte1DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("allocate", (void (byte1DReg::*)()) & byte1DReg::allocate,
                   "Allocate the array")
              .def("window",
                   (std::shared_ptr<byte1DReg>(byte1DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       byte1DReg::window,
                   "Window a vector")

              .def_buffer([](byte1DReg &m) -> py::buffer_info {
                   return py::buffer_info(m.getVals(), sizeof(unsigned char),
                                          py::format_descriptor<unsigned char>::format(),
                                          1, {m.getHyper()->getAxis(1).n},
                                          {sizeof(unsigned char)});
              });
          py::class_<byte2DReg, byteHyper, std::shared_ptr<byte2DReg> >(
              clsVector, "byte2DReg", py::buffer_protocol())
              .def(py::init<const int, const int>(), "Initialize giving size")
              .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const std::shared_ptr<byte6DReg>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 6-D hypercube")
              .def(py::init<const std::shared_ptr<byte5DReg>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 5-D hypercube")
              .def(py::init<const std::shared_ptr<byte4DReg>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 4-D hypercube")
              .def(py::init<const std::shared_ptr<byte3DReg>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 3-D hypercube")
              .def(py::init<const std::shared_ptr<byte2DReg>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 2-D hypercube")
              .def("clone",
                   (std::shared_ptr<byte2DReg>(byte2DReg::*)() const) &
                       byte2DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<byte2DReg>(byte2DReg::*)() const) &
                       byte2DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("allocate", (void (byte2DReg::*)()) & byte2DReg::allocate,
                   "Allocate the array")
              .def("window",
                   (std::shared_ptr<byte2DReg>(byte2DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       byte2DReg::window,
                   "Window a vector")
              .def_buffer([](byte2DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(unsigned char),
                       py::format_descriptor<unsigned char>::format(), 2,
                       {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(unsigned char) * m.getHyper()->getAxis(1).n,
                        sizeof(unsigned char)});
              });

          py::class_<byte3DReg, byteHyper, std::shared_ptr<byte3DReg> >(
              clsVector, "byte3DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def("allocate", (void (byte3DReg::*)()) & byte3DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<byte3DReg>(byte3DReg::*)() const) &
                       byte3DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<byte3DReg>(byte3DReg::*)() const) &
                       byte3DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<byte3DReg>(byte3DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       byte3DReg::window,
                   "Window a vector")
              .def_buffer([](byte3DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(unsigned char),
                       py::format_descriptor<unsigned char>::format(), 3,
                       {m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(unsigned char) * m.getHyper()->getAxis(1).n,
                        sizeof(unsigned char)});
              });

          py::class_<byte4DReg, byteHyper, std::shared_ptr<byte4DReg> >(
              clsVector, "byte4DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (byte4DReg::*)()) & byte4DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<byte4DReg>(byte4DReg::*)() const) &
                       byte4DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<byte4DReg>(byte4DReg::*)() const) &
                       byte4DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<byte4DReg>(byte4DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       byte4DReg::window,
                   "Window a vector")
              .def_buffer([](byte4DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(unsigned char),
                       py::format_descriptor<unsigned char>::format(), 4,
                       {m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(unsigned char) * m.getHyper()->getAxis(1).n,
                        sizeof(unsigned char)});
              });
          py::class_<byte5DReg, byteHyper, std::shared_ptr<byte5DReg> >(
              clsVector, "byte5DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (byte5DReg::*)()) & byte5DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<byte5DReg>(byte5DReg::*)() const) &
                       byte5DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<byte5DReg>(byte5DReg::*)() const) &
                       byte5DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<byte5DReg>(byte5DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       byte5DReg::window,
                   "Window a vector")
              .def_buffer([](byte5DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(unsigned char),
                       py::format_descriptor<unsigned char>::format(), 5,
                       {m.getHyper()->getAxis(5).n, m.getHyper()->getAxis(4).n,
                        m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(unsigned char) * m.getHyper()->getAxis(1).n,
                        sizeof(unsigned char)});
              });

          py::class_<byte6DReg, byteHyper, std::shared_ptr<byte6DReg> >(
              clsVector, "byte6DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (byte6DReg::*)()) & byte6DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<byte6DReg>(byte6DReg::*)() const) &
                       byte6DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<byte6DReg>(byte6DReg::*)() const) &
                       byte6DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<byte6DReg>(byte6DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       byte6DReg::window,
                   "Window a vector")
              .def_buffer([](byte6DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(unsigned char),
                       py::format_descriptor<unsigned char>::format(), 6,
                       {m.getHyper()->getAxis(6).n, m.getHyper()->getAxis(5).n,
                        m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n,
                        sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(unsigned char) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(unsigned char) * m.getHyper()->getAxis(1).n,
                        sizeof(unsigned char)});
              });

     } // namespace SEP
} // namespace SEP
