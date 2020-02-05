#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "doubleHyper.h"


namespace py = pybind11;
using namespace SEP;
void init_hyperdouble(py::module &clsVector){
 py::class_<doubleHyper, regSpace, std::shared_ptr<doubleHyper>>(
      clsVector,
      "doubleHyper")  //
      .def(py::init<>(), "Initlialize a new double Hyper (don't use this")
      .def("getSpaceOnly",
           (bool (doubleHyper::*)()) & doubleHyper::getSpaceOnly,
           "Check to see if this only a description of the vector space")

      .def("setData", (void (doubleHyper::*)(double *)) & doubleHyper::setData,
           "Set the data pointer")
      .def("getVals", (double *(doubleHyper::*)()) & doubleHyper::getVals,
           "Get the data pointer")
      .def("clip",
           (void (doubleHyper::*)(const double, const double)) &
               doubleHyper::clip,
           "Clip a dataset given minumum and maximum value")
      .def("cent",
           (double (doubleHyper::*)(const float pct, const int jsamp) const) &
               doubleHyper::cent,
           "Calculate  the percentile of a dataset")
      .def("calcHisto",
           (void (doubleHyper::*)(std::shared_ptr<int1DReg>, float, float)) &
               doubleHyper::calcHisto,
           "Calculate histogram")
      .def("clipVector",
           (void (doubleHyper::*)(const std::shared_ptr<doubleHyper>,
                                  const std::shared_ptr<doubleHyper>)) &
               doubleHyper::clipVector,
           "vec=min(max(low,vec),high)")
      .def("isDifferent",
           (bool (doubleHyper::*)(std::shared_ptr<doubleHyper>)) &
               doubleHyper::isDifferent,
           "Check to  see if two vectors are different")

      .def_property("_vals", &doubleHyper::getVals, &doubleHyper::setData,
                    py::return_value_policy::reference)

      .def("createMask",
           (void (doubleHyper::*)(const double, const double)) &
               doubleHyper::createMask,
           "Create a mask weight")
      .def("add",
           (void (doubleHyper::*)(std::shared_ptr<doubleHyper>)) &
               doubleHyper::add,
           "Add two vectors")
      .def("scale", (void (doubleHyper::*)(const double)) & doubleHyper::scale,
           "Scale a vector")

      .def("scaleAdd",
           (void (doubleHyper::*)(std::shared_ptr<doubleHyper>, const double,
                                  const double)) &
               doubleHyper::scaleAdd,
           "vec=vec*sc1+vec2*sc2")
      .def("calcCheckSum",
           (double (doubleHyper::*)() const) & doubleHyper::calcCheckSum,
           "Calculate checksum of a vector")

      .def("norm",
           (double (doubleHyper::*)(const int n) const) & doubleHyper::norm,
           "Calculate n-norm of a vector")
      .def("zero", (void (doubleHyper::*)()) & doubleHyper::zero,
           "Fill a vector with zero")
      .def("set", (void (doubleHyper::*)(const double)) & doubleHyper::set,
           "Fill a vector with a value")
      .def("signum", (void (doubleHyper::*)()) & doubleHyper::signum,
           "Fill a vector with it's signum")
      .def("rand", (void (doubleHyper::*)()) & doubleHyper::random,
           "Fill a vector with random number")

      .def("mult",
           (void (doubleHyper::*)(std::shared_ptr<doubleHyper>)) &
               doubleHyper::mult,
           "vec=vec*vec2")
      .def("dot",
           (double (doubleHyper::*)(std::shared_ptr<doubleHyper>) const) &
               doubleHyper::dot,
           "Calculate dot product")
      .def("checkSame",
           (bool (doubleHyper::*)(const std::shared_ptr<doubleHyper>) const) &
               doubleHyper::checkSame,
           "Check to make sure the vectors exist in the same space");

}