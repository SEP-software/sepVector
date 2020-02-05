#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "byteHyper.h"


namespace py = pybind11;
using namespace SEP;
void init_hyperbyte(py::module &clsVector){
py::class_<byteHyper, regSpace, std::shared_ptr<byteHyper>>(clsVector,
                                                              "byteHyper")  //
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

}