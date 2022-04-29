

#include "int1DReg.h"
#include "int2DReg.h"
#include "int3DReg.h"
#include "int4DReg.h"
#include "int5DReg.h"
#include "int6DReg.h"

#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;
namespace SEP
{

     void init_intR(py::module &clsVector)
     {

          py::class_<intHyper, regSpace, std::shared_ptr<intHyper> >(clsVector,
                                                                     "intHyper") //
              .def(py::init<>(), "Initlialize a new int Hyper (don't use this")
              .def("getSpaceOnly", (bool (intHyper::*)()) & intHyper::getSpaceOnly,
                   "Check to see if this only a description of the vector space")

              .def("setData", (void (intHyper::*)(int *)) & intHyper::setData,
                   "Set the data pointer")
              .def("getVals", (int *(intHyper::*)()) & intHyper::getVals,
                   "Get the data pointer")

              .def("isDifferent",
                   (bool (intHyper::*)(std::shared_ptr<intHyper>)) &
                       intHyper::isDifferent,
                   "Check to  see if two vectors are different")

              .def_property("_vals", &intHyper::getVals, &intHyper::setData,
                            py::return_value_policy::reference)
              .def("clip", (void (intHyper::*)(const int, const int)) & intHyper::clip,
                   "Clip a dataset given minumum and maximum value")
              .def("cent",
                   (int (intHyper::*)(const float pct, const int jsamp) const) &
                       intHyper::cent,
                   "Calculate  the percentile of a dataset")
              .def("add",
                   (void (intHyper::*)(std::shared_ptr<intHyper>)) & intHyper::add,
                   "Add two vectors")
              .def("scale", (void (intHyper::*)(const int)) & intHyper::scale,
                   "Scale a vector")
              .def("scaleAdd",
                   (void (intHyper::*)(std::shared_ptr<intHyper>, const int,
                                       const int)) &
                       intHyper::scaleAdd,
                   "vec=vec*sc1+vec2*sc2")
              .def("calcCheckSum", (int (intHyper::*)() const) & intHyper::calcCheckSum,
                   "Calculate checksum of a vector")
              .def("zero", (void (intHyper::*)()) & intHyper::zero,
                   "Fill a vector with zero")
              .def("set", (void (intHyper::*)(const int)) & intHyper::set,
                   "Fill a vector with a value")
              .def("signum", (void (intHyper::*)()) & intHyper::signum,
                   "Fill a vector with it's signum")
              .def("rand", (void (intHyper::*)()) & intHyper::random,
                   "Fill a vector with random number")
              .def("mult",
                   (void (intHyper::*)(std::shared_ptr<intHyper>)) & intHyper::mult,
                   "vec=vec*vec2")
              .def("checkSame",
                   (bool (intHyper::*)(const std::shared_ptr<intHyper>) const) &
                       intHyper::checkSame,
                   "Check to make sure the vectors exist in the same space");

          py::class_<int1DReg, intHyper, std::shared_ptr<int1DReg> >(
              clsVector, "int1DReg", py::buffer_protocol())
              .def(py::init<const int>(), "Initialize giving size")
              .def(py::init<const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const std::shared_ptr<int6DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 6-D hypercube")
              .def(py::init<const std::shared_ptr<int5DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 5-D hypercube")
              .def(py::init<const std::shared_ptr<int4DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 4-D hypercube")
              .def(py::init<const std::shared_ptr<int3DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 3-D hypercube")
              .def(py::init<const std::shared_ptr<int2DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 2-D hypercube")
              .def(py::init<const std::shared_ptr<int1DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 1-D hypercube")
              .def("clone",
                   (std::shared_ptr<int1DReg>(int1DReg::*)() const) & int1DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<int1DReg>(int1DReg::*)() const) &
                       int1DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("allocate", (void (int1DReg::*)()) & int1DReg::allocate,
                   "Allocate the array")
              .def("window",
                   (std::shared_ptr<int1DReg>(int1DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       int1DReg::window,
                   "Window a vector")
              .def_buffer([](int1DReg &m) -> py::buffer_info {
                   return py::buffer_info(m.getVals(), sizeof(int),
                                          py::format_descriptor<int>::format(), 1,
                                          {m.getHyper()->getAxis(1).n}, {sizeof(int)});
              });
          py::class_<int2DReg, intHyper, std::shared_ptr<int2DReg> >(
              clsVector, "int2DReg", py::buffer_protocol())
              .def(py::init<const int, const int>(), "Initialize giving size")
              .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const std::shared_ptr<int6DReg>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 6-D hypercube")
              .def(py::init<const std::shared_ptr<int5DReg>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 5-D hypercube")
              .def(py::init<const std::shared_ptr<int4DReg>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 4-D hypercube")
              .def(py::init<const std::shared_ptr<int3DReg>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 3-D hypercube")
              .def(py::init<const std::shared_ptr<int2DReg>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 2-D hypercube")
              .def("clone",
                   (std::shared_ptr<int2DReg>(int2DReg::*)() const) & int2DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<int2DReg>(int2DReg::*)() const) &
                       int2DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("allocate", (void (int2DReg::*)()) & int2DReg::allocate,
                   "Allocate the array")
              .def("window",
                   (std::shared_ptr<int2DReg>(int2DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       int2DReg::window,
                   "Window a vector")

              .def_buffer([](int2DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(int), py::format_descriptor<int>::format(), 2,
                       {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(int) * m.getHyper()->getAxis(1).n, sizeof(int)});
              });

          py::class_<int3DReg, intHyper, std::shared_ptr<int3DReg> >(
              clsVector, "int3DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def("allocate", (void (int3DReg::*)()) & int3DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<int3DReg>(int3DReg::*)() const) & int3DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<int3DReg>(int3DReg::*)() const) &
                       int3DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<int3DReg>(int3DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       int3DReg::window,
                   "Window a vector")

              .def_buffer([](int3DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(int), py::format_descriptor<int>::format(), 3,
                       {m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(int) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(int) * m.getHyper()->getAxis(1).n, sizeof(int)});
              });

          py::class_<int4DReg, intHyper, std::shared_ptr<int4DReg> >(
              clsVector, "int4DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (int4DReg::*)()) & int4DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<int4DReg>(int4DReg::*)() const) & int4DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<int4DReg>(int4DReg::*)() const) &
                       int4DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<int4DReg>(int4DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       int4DReg::window,
                   "Window a vector")
              .def_buffer([](int4DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(int), py::format_descriptor<int>::format(), 4,
                       {m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(int) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(int) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(int) * m.getHyper()->getAxis(1).n, sizeof(int)});
              });
          py::class_<int5DReg, intHyper, std::shared_ptr<int5DReg> >(
              clsVector, "int5DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (int5DReg::*)()) & int5DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<int5DReg>(int5DReg::*)() const) & int5DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<int5DReg>(int5DReg::*)() const) &
                       int5DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<int5DReg>(int5DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       int5DReg::window,
                   "Window a vector")
              .def_buffer([](int5DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(int), py::format_descriptor<int>::format(), 5,
                       {m.getHyper()->getAxis(5).n, m.getHyper()->getAxis(4).n,
                        m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(int) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(int) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(int) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(int) * m.getHyper()->getAxis(1).n, sizeof(int)});
              });

          py::class_<int6DReg, intHyper, std::shared_ptr<int6DReg> >(
              clsVector, "int6DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (int6DReg::*)()) & int6DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<int6DReg>(int6DReg::*)() const) & int6DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<int6DReg>(int6DReg::*)() const) &
                       int6DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<int6DReg>(int6DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       int6DReg::window,
                   "Window a vector")
              .def_buffer([](int6DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(int), py::format_descriptor<int>::format(), 6,
                       {m.getHyper()->getAxis(6).n, m.getHyper()->getAxis(5).n,
                        m.getHyper()->getAxis(4).n, m.getHyper()->getAxis(3).n,
                        m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(int) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n * m.getHyper()->getAxis(5).n,
                        sizeof(int) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n *
                            m.getHyper()->getAxis(4).n,
                        sizeof(int) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n * m.getHyper()->getAxis(3).n,
                        sizeof(int) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(int) * m.getHyper()->getAxis(1).n, sizeof(int)});
              });
     }
} // namespace SEP
