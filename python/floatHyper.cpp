#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "floatHyper.h"


namespace py = pybind11;
using namespace SEP;
void init_hyperfloat(py::module &clsVector){
py::class_<floatHyper, Vector, regSpace, std::shared_ptr<floatHyper>>(
      clsVector,
      "floatHyper")  //
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
      .def(
          "add",
          (void (floatHyper::*)(std::shared_ptr<floatHyper>)) & floatHyper::add,
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
}