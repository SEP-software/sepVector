#include "byte1DReg.h"
#include "byte2DReg.h"
#include "byte3DReg.h"
#include "byte4DReg.h"
#include "byte5DReg.h"
#include "byte6DReg.h"
#include "complex1DReg.h"
#include "complex2DReg.h"
#include "complex3DReg.h"
#include "complex4DReg.h"
#include "complex5DReg.h"
#include "complex6DReg.h"
#include "complex7DReg.h"

#include "complexDouble1DReg.h"
#include "complexDouble2DReg.h"
#include "complexDouble3DReg.h"
#include "complexDouble4DReg.h"
#include "complexDouble5DReg.h"
#include "complexDouble6DReg.h"
#include "complexDouble7DReg.h"

#include "double1DReg.h"
#include "double2DReg.h"
#include "double3DReg.h"
#include "double4DReg.h"
#include "double5DReg.h"
#include "double6DReg.h"
#include "double7DReg.h"

#include "float1DReg.h"
#include "float2DReg.h"
#include "float3DReg.h"
#include "float4DReg.h"
#include "float5DReg.h"
#include "float6DReg.h"
#include "float7DReg.h"
#include "floatHyper.h"
#include "floatTensor.h"

#include "int1DReg.h"
#include "int2DReg.h"
#include "int3DReg.h"
#include "int4DReg.h"
#include "int5DReg.h"
#include "int6DReg.h"
#include "rectFilter.h"
#include "regSpace.h"
#include "sepVectorConfig.h"
#include "short1DReg.h"
#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;
namespace SEP {

void init_base(py::module &clsVector) {

  py::class_<Vector, std::shared_ptr<Vector>>(clsVector, "Vector")
      .def(py::init<>(), "Initlialize a new Vector (don't use this");

  py::class_<regSpace, std::shared_ptr<regSpace>>(clsVector, "regSpace")
      .def(py::init<>(), "Initlialize a new regSpace (don't use this")
      .def("getHyper",
           (std::shared_ptr<hypercube>(regSpace::*)()) & regSpace::getHyper,
           "Get the hypercube")
      .def_property("_hyper", &regSpace::getHyper, &regSpace::setHyper,
                    py::return_value_policy::reference)
      .def("copyElements",
           (void(regSpace::*)(const std::shared_ptr<regSpace>)) &
               regSpace::copyElements,
           "Copy elements")
      .def("setHyper",
           (void(regSpace::*)(std::shared_ptr<hypercube>)) & regSpace::setHyper,
           "Get the hypercube")
      .def("getVoidPtr", (void *(regSpace::*)()) & regSpace::getVoidPtr,
           "Get a void ptr")
      .def("getEsize", (int(regSpace::*)()) & regSpace::getEsize,
           "Get the element size");

} // namespace SEP
} // namespace SEP
