#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "intHyper.h"


namespace py = pybind11;
using namespace SEP;
void init_hyperint(py::module &clsVector){
py::class_<intHyper, regSpace, std::shared_ptr<intHyper>>(clsVector,
                                                            "intHyper")  //
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

}