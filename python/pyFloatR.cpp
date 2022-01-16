

#include "floatHyper.h"
#include "float1DReg.h"
#include "float2DReg.h"
#include "float3DReg.h"
#include "float4DReg.h"
#include "float5DReg.h"
#include "float6DReg.h"
#include "float7DReg.h"
#include "floatTensor.h"

#include "sepVectorConfig.h"
#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;
namespace SEP
{

     void init_floatR(py::module &clsVector)
     {

          py::class_<floatHyper,  regSpace, std::shared_ptr<floatHyper> >(
              clsVector,
              "floatHyper") //
              .def(py::init<>(), "Initlialize a new Float Hyper (don't use this")
              .def("getSpaceOnly", (bool (floatHyper::*)()) & floatHyper::getSpaceOnly,
                   "Check to see if this only a description of the vector space")

              .def("setData", (void (floatHyper::*)(float *)) & floatHyper::setData,
                   "Set the data pointer")
              .def("getVals", (float *(floatHyper::*)()) & floatHyper::getVals,
                   "Get the data pointer")

              .def("isDifferent",
                   (bool (floatHyper::*)(std::shared_ptr<floatHyper>)) &
                       floatHyper::isDifferent,
                   "Check to  see if two vectors are different")

              .def_property("_vals", &floatHyper::getVals, &floatHyper::setData,
                            py::return_value_policy::reference)

              .def("createMask",
                   (void (floatHyper::*)(const float, const float)) &
                       floatHyper::createMask,
                   "Create a mask weight")
              .def("add",
                   (void (floatHyper::*)(std::shared_ptr<floatHyper>)) &
                       floatHyper::add,
                   "Add two vectors")
              .def("scale", (void (floatHyper::*)(const double)) & floatHyper::scale,
                   "Scale a vector")
              .def("clipVector",
                   (void (floatHyper::*)(const std::shared_ptr<floatHyper>,
                                         const std::shared_ptr<floatHyper>)) &
                       floatHyper::clipVector,
                   "vec=min(max(low,vec),high)")
              .def("calcHisto",
                   (void (floatHyper::*)(std::shared_ptr<int1DReg>, float, float)) &
                       floatHyper::calcHisto,
                   "Calculate histogram")
              .def("scaleAdd",
                   (void (floatHyper::*)(std::shared_ptr<floatHyper>, const double,
                                         const double)) &
                       floatHyper::scaleAdd,
                   "vec=vec*sc1+vec2*sc2")
              .def("calcCheckSum",
                   (double (floatHyper::*)() const) & floatHyper::calcCheckSum,
                   "Calculate checksum of a vector")
              .def("clip",
                   (void (floatHyper::*)(const float, const float)) & floatHyper::clip,
                   "Clip a dataset given minumum and maximum value")
              .def("cent",
                   (float (floatHyper::*)(const float, const int) const) &
                       floatHyper::cent,
                   "Calculate  the percentile of a dataset")
              .def("norm",
                   (double (floatHyper::*)(const int n) const) & floatHyper::norm,
                   "Calculate n-norm of a vector")
              .def("zero", (void (floatHyper::*)()) & floatHyper::zero,
                   "Fill a vector with zero")
              .def("set", (void (floatHyper::*)(const float)) & floatHyper::set,
                   "Fill a vector with a value")
              .def("signum", (void (floatHyper::*)()) & floatHyper::signum,
                   "Fill a vector with it's signum")
              .def("rand", (void (floatHyper::*)()) & floatHyper::random,
                   "Fill a vector with random number")

              .def("mult",
                   (void (floatHyper::*)(std::shared_ptr<floatHyper>)) &
                       floatHyper::mult,
                   "vec=vec*vec2")
              .def("dot",
                   (double (floatHyper::*)(std::shared_ptr<floatHyper>) const) &
                       floatHyper::dot,
                   "Calculate dot product")
              .def("checkSame",
                   (bool (floatHyper::*)(const std::shared_ptr<floatHyper>) const) &
                       floatHyper::checkSame,
                   "Check to make sure the vectors exist in the same space");

          py::class_<float1DReg, floatHyper, std::shared_ptr<float1DReg> >(
              clsVector, "float1DReg", py::buffer_protocol())
              .def(py::init<const int>(), "Initialize giving size")
              .def(py::init<const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const std::shared_ptr<float6DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 6-D hypercube")
              .def(py::init<const std::shared_ptr<float5DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 5-D hypercube")
              .def(py::init<const std::shared_ptr<float4DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 4-D hypercube")
              .def(py::init<const std::shared_ptr<float3DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 3-D hypercube")
              .def(py::init<const std::shared_ptr<float2DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 2-D hypercube")
              .def(py::init<const std::shared_ptr<float1DReg>, const int, const bool,
                            const std::vector<int> &, const std::vector<int> &,
                            std::vector<int> &>(),
                   "Create a 1-D slice from 1-D hypercube")
              .def("clone",
                   (std::shared_ptr<float1DReg>(float1DReg::*)() const) &
                       float1DReg::clone,
                   "Make a copy of the vector")
              .def("window",
                   (std::shared_ptr<float1DReg>(float1DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       float1DReg::window,
                   "Window a vector")

              .def("cloneSpace",
                   (std::shared_ptr<float1DReg>(float1DReg::*)() const) &
                       float1DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("allocate", (void (float1DReg::*)()) & float1DReg::allocate,
                   "Allocate the array")

              .def_buffer([](float1DReg &m) -> py::buffer_info {
                   return py::buffer_info(m.getVals(), sizeof(float),
                                          py::format_descriptor<float>::format(), 1,
                                          {m.getHyper()->getAxis(1).n}, {sizeof(float)});
              });
          py::class_<float2DReg, floatHyper, std::shared_ptr<float2DReg> >(
              clsVector, "float2DReg", py::buffer_protocol())
              .def(py::init<const int, const int>(), "Initialize giving size")
              .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const std::shared_ptr<float6DReg>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 6-D hypercube")
              .def(py::init<const std::shared_ptr<float5DReg>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 5-D hypercube")
              .def(py::init<const std::shared_ptr<float4DReg>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 4-D hypercube")
              .def(py::init<const std::shared_ptr<float3DReg>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 3-D hypercube")
              .def(py::init<const std::shared_ptr<float2DReg>, const int, const bool,
                            const int, const bool, const std::vector<int> &,
                            const std::vector<int> &, std::vector<int> &>(),
                   "Create a 2-D slice from 2-D hypercube")
              .def("clone",
                   (std::shared_ptr<float2DReg>(float2DReg::*)() const) &
                       float2DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<float2DReg>(float2DReg::*)() const) &
                       float2DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("allocate", (void (float2DReg::*)()) & float2DReg::allocate,
                   "Allocate the array")
              .def("window",
                   (std::shared_ptr<float2DReg>(float2DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       float2DReg::window,
                   "Window a vector")

              .def_buffer([](float2DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(float), py::format_descriptor<float>::format(),
                       2, {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
                       {sizeof(float) * m.getHyper()->getAxis(1).n, sizeof(float)});
              });

          py::class_<float3DReg, floatHyper, std::shared_ptr<float3DReg> >(
              clsVector, "float3DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def(py::init<const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def("allocate", (void (float3DReg::*)()) & float3DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<float3DReg>(float3DReg::*)() const) &
                       float3DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<float3DReg>(float3DReg::*)() const) &
                       float3DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<float3DReg>(float3DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       float3DReg::window,
                   "Window a vector")

              .def_buffer([](float3DReg &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(float), py::format_descriptor<float>::format(),
                       3,
                       {m.getHyper()->getAxis(3).n, m.getHyper()->getAxis(2).n,
                        m.getHyper()->getAxis(1).n},
                       {sizeof(float) * m.getHyper()->getAxis(1).n *
                            m.getHyper()->getAxis(2).n,
                        sizeof(float) * m.getHyper()->getAxis(1).n, sizeof(float)});
              });

          py::class_<float4DReg, floatHyper, std::shared_ptr<float4DReg> >(
              clsVector, "float4DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (float4DReg::*)()) & float4DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<float4DReg>(float4DReg::*)() const) &
                       float4DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<float4DReg>(float4DReg::*)() const) &
                       float4DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<float4DReg>(float4DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       float4DReg::window,
                   "Window a vector")

              .def_buffer([](float4DReg &m) -> py::buffer_info {
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
          py::class_<float5DReg, floatHyper, std::shared_ptr<float5DReg> >(
              clsVector, "float5DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (float5DReg::*)()) & float5DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<float5DReg>(float5DReg::*)() const) &
                       float5DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<float5DReg>(float5DReg::*)() const) &
                       float5DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("window",
                   (std::shared_ptr<float5DReg>(float5DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       float5DReg::window,
                   "Window a vector")

              .def_buffer([](float5DReg &m) -> py::buffer_info {
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

          py::class_<float6DReg, floatHyper, std::shared_ptr<float6DReg> >(
              clsVector, "float6DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (float6DReg::*)()) & float6DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<float6DReg>(float6DReg::*)() const) &
                       float6DReg::clone,
                   "Make a copy of the vector")
              .def("window",
                   (std::shared_ptr<float6DReg>(float6DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       float6DReg::window,
                   "Window a vector")

              .def("cloneSpace",
                   (std::shared_ptr<float6DReg>(float6DReg::*)() const) &
                       float6DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def_buffer([](float6DReg &m) -> py::buffer_info {
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
          py::class_<float7DReg, floatHyper, std::shared_ptr<float7DReg> >(
              clsVector, "float7DReg", py::buffer_protocol())
              .def(py::init<const int, const int, const int, const int, const int, const int,
                            const int>(),
                   "Initialize giving size")
              .def(py::init<const axis &, const axis &, const axis &, const axis &,
                            const axis &, const axis &, const axis &>(),
                   "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")
              .def("allocate", (void (float7DReg::*)()) & float7DReg::allocate,
                   "Allocate the array")
              .def("clone",
                   (std::shared_ptr<float7DReg>(float7DReg::*)() const) &
                       float7DReg::clone,
                   "Make a copy of the vector")
              .def("window",
                   (std::shared_ptr<float7DReg>(float7DReg::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &) const) &
                       float7DReg::window,
                   "Window a vector")

              .def("cloneSpace",
                   (std::shared_ptr<float7DReg>(float7DReg::*)() const) &
                       float6DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def_buffer([](float7DReg &m) -> py::buffer_info {
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
