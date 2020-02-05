#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "complexHyper.h"


namespace py = pybind11;
using namespace SEP;
void init_hypercomplex(py::module &clsVector){
  py::class_<complexHyper, regSpace, std::shared_ptr<complexHyper>>(
      clsVector,
      "complexHyper")  //
      .def(py::init<>(), "Initlialize a new complex Hyper (don't use this")
      .def("getSpaceOnly",
           (bool (complexHyper::*)()) & complexHyper::getSpaceOnly,
           "Check to see if this only a description of the vector space")

      .def("setData",
           (void (complexHyper::*)(std::complex<float> *)) &
               complexHyper::setData,
           "Set the data pointer")
      .def("getVals",
           (std::complex<float> * (complexHyper::*)()) & complexHyper::getVals,
           "Get the data pointer")

      .def("isDifferent",
           (bool (complexHyper::*)(std::shared_ptr<complexHyper>)) &
               complexHyper::isDifferent,
           "Check to  see if two vectors are different")

      .def("mult",
           (void (complexHyper::*)(std::shared_ptr<complexHyper>)) &
               complexHyper::mult,
           "vec=vec*vec2")
      .def("dot",
           (double (complexHyper::*)(std::shared_ptr<complexHyper>) const) &
               complexHyper::dot,
           "Calculate dot product")
      .def_property("_vals", &complexHyper::getVals, &complexHyper::setData,
                    py::return_value_policy::reference)
      .def("scale",
           (void (complexHyper::*)(const double)) & complexHyper::scale,
           "Scale a vector")
      .def("scaleAdd",
           (void (complexHyper::*)(std::shared_ptr<complexHyper>, const double,
                                   const double)) &
               complexHyper::scaleAdd,
           "vec=vec*sc1+vec2*sc2")
      .def("calcCheckSum",
           (unsigned char (complexHyper::*)() const) &
               complexHyper::calcCheckSum,
           "Calculate checksum of a vector")
      .def("norm",
           (double (complexHyper::*)(const int n) const) & complexHyper::norm,
           "Calculate n-norm of a vector")
      .def("zero", (void (complexHyper::*)()) & complexHyper::zero,
           "Fill a vector with zero")
      .def("set",
           (void (complexHyper::*)(const std::complex<float>)) &
               complexHyper::set,
           "Fill a vector with a value")
      .def("rand", (void (complexHyper::*)()) & complexHyper::random,
           "Fill a vector with random number")
      .def("clipVector",
           (void (complexHyper::*)(const std::shared_ptr<floatHyper>,
                                   const std::shared_ptr<floatHyper>)) &
               complexHyper::clipVector,
           "vec=min(max(low,vec),high)")
      .def("clipVector",
           (void (complexHyper::*)(const std::shared_ptr<complexHyper>,
                                   const std::shared_ptr<complexHyper>)) &
               complexHyper::clipVector,
           "vec=min(max(low,vec),high)")
      .def("checkSame",
           (bool (complexHyper::*)(const std::shared_ptr<complexHyper>) const) &
               complexHyper::checkSame,
           "Check to make sure the vectors exist in the same space");
}