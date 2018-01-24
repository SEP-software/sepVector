#include <pybind11/pybind11.h>
#include "float1DReg.h"
#include "float2DReg.h"
#include "float3DReg.h"
#include "float4DReg.h"

namespace py = pybind11;
namespace giee {
using namespace SEP;

PYBIND11_MODULE(pySepVector, clsVector) {
  py::class_<floatHyper, std::shared_ptr<floatHyper>>(clsVector,
                                                      "floatHyper")  //
      .def(py::init<>(), "Initlialize a new Float Hyper (don't use this")
      .def("getSpaceOnly", (bool (floatHyper::*)()) & floatHyper::getSpaceOnly,
           "Check to see if this only a description of the vector space")
      .def("add",
           (void (floatHyper::*)(std::shared_ptr<Vector>)) & floatHyper::add,
           "Add two vectors")
      .def("scale",
           (void (floatHyper::*)(const double val)) & floatHyper::scale,
           "Scale a vector")
      .def("scaleAdd",
           (void (floatHyper::*)(const double sc1, std::shared_ptr<Vector>,
                                 const double sc2)) &
               floatHyper::scaleAdd,
           "vec=vec*sc1+vec2*sc2")
      .def("random",
           (void (floatHyper::*)(std::shared_ptr<Vector>)) & floatHyper::random,
           "Fill a vector with random number")
      .def("setData", (void (floatHyper::*)(float *)) & floatHyper::setData,
           "Set the data pointer")
      .def("dot",
           (double (floatHyper::*)(std::shared_ptr<Vector>) const) &
               floatHyper::dot,
           "Calculate dot product")
      .def("checkSame",
           (bool (floatHyper::*)(const std::shared_ptr<Vector>,
                                 const bool checkAlloc) const) &
               floatHyper::checkSame,
           "Check to make sure the vectors exist in the same space")
      .def("getHyper",
           (std::shared_ptr<hypercube>(floatHyper::*)() const) &
               floatHyper::getHyper,
           "Return a hypercube describing the space");

  py::class_<float1DReg, std::shared_ptr<float1DReg>>(clsVector, "float1DReg")
      .def(py::init<const int>(), "Initialize giving size")
      .def(py::init<const axis &>(), "Initialize from an axis")
      .def("clone",
           (std::shared_ptr<Vector>(float1DReg::*)() const) & float1DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<Vector>(float1DReg::*)() const) &
               float1DReg::cloneSpace,
           "Make a copy of the vector space");

  py::class_<float2DReg, std::shared_ptr<float2DReg>>(clsVector, "float2DReg",
                                                      py::buffer_protocol())
      .def(py::init<const int, const int>(), "Initialize giving size")
      .def(py::init<const axis &, const axis &>(), "Initialize from an axis")
      .def("clone",
           (std::shared_ptr<Vector>(float2DReg::*)() const) & float2DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<Vector>(float2DReg::*)() const) &
               float1DReg::cloneSpace,
           "Make a copy of the vector space")
      .def_buffer([](float2DReg &m) -> py::buffer_info {
        return py::buffer_info(
            m.getVals(), sizeof(float), py::format_descriptor<float>::format(),
            2, {m.getHyper()->getAxis(2).n, m.getHyper()->getAxis(1).n},
            {sizeof(float) * m.getHyper()->getAxis(1).n, sizeof(float)});
      });

  py::class_<float3DReg, std::shared_ptr<float3DReg>>(clsVector, "float3DReg")
      .def(py::init<const int, const int, const int>(),
           "Initialize giving size")
      .def(py::init<const axis &, const axis &, const axis &>(),
           "Initialize from an axis")
      .def("clone",
           (std::shared_ptr<Vector>(float3DReg::*)() const) & float3DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<Vector>(float3DReg::*)() const) &
               float1DReg::cloneSpace,
           "Make a copy of the vector space");

  py::class_<float4DReg, std::shared_ptr<float4DReg>>(clsVector, "float4DReg")
      .def(py::init<const int, const int, const int, const int>(),
           "Initialize giving size")
      .def(py::init<const axis &, const axis &, const axis &, const axis &>(),
           "Initialize from an axis")
      .def("clone",
           (std::shared_ptr<Vector>(float4DReg::*)() const) & float4DReg::clone,
           "Make a copy of the vector")
      .def("cloneSpace",
           (std::shared_ptr<Vector>(float4DReg::*)() const) &
               float1DReg::cloneSpace,
           "Make a copy of the vector space");
}
}  // namespace giee