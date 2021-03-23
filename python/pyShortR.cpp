
#include "sepVectorConfig.h"
#include "short1DReg.h"
#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;
namespace SEP
{

     void init_shortR(py::module &clsVector)
     {

          py::class_<shortHyper, regSpace, std::shared_ptr<shortHyper> >(clsVector,
                                                                         "shortHyper") //
              .def(py::init<>(), "Initlialize a new int Hyper (don't use this")
              .def("getSpaceOnly", (bool (shortHyper::*)()) & shortHyper::getSpaceOnly,
                   "Check to see if this only a description of the vector space")

              .def("setData", (void (shortHyper::*)(int *)) & shortHyper::setData,
                   "Set the data pointer")
              .def("getVals", (int *(shortHyper::*)()) & shortHyper::getVals,
                   "Get the data pointer")

              .def("isDifferent",
                   (bool (shortHyper::*)(std::shared_ptr<shortHyper>)) &
                       shortHyper::isDifferent,
                   "Check to  see if two vectors are different")

              .def_property("_vals", &shortHyper::getVals, &shortHyper::setData,
                            py::return_value_policy::reference)

              .def("add",
                   (void (shortHyper::*)(std::shared_ptr<shortHyper>)) &
                       shortHyper::add,
                   "Add two vectors")
              .def("scale", (void (shortHyper::*)(const int)) & shortHyper::scale,
                   "Scale a vector")
              .def("scaleAdd",
                   (void (shortHyper::*)(std::shared_ptr<shortHyper>, const int,
                                         const int)) &
                       shortHyper::scaleAdd,
                   "vec=vec*sc1+vec2*sc2")
              .def("calcCheckSum",
                   (int (shortHyper::*)() const) & shortHyper::calcCheckSum,
                   "Calculate checksum of a vector")
              .def("zero", (void (shortHyper::*)()) & shortHyper::zero,
                   "Fill a vector with zero")
              .def("set", (void (shortHyper::*)(const short)) & shortHyper::set,
                   "Fill a vector with a value")
              .def("signum", (void (shortHyper::*)()) & shortHyper::signum,
                   "Fill a vector with it's signum")
              .def("rand", (void (shortHyper::*)()) & shortHyper::random,
                   "Fill a vector with random number")
              .def("mult",
                   (void (shortHyper::*)(std::shared_ptr<shortHyper>)) &
                       shortHyper::mult,
                   "vec=vec*vec2")
              .def("checkSame",
                   (bool (shortHyper::*)(const std::shared_ptr<shortHyper>) const) &
                       shortHyper::checkSame,
                   "Check to make sure the vectors exist in the same space");
          py::class_<short1DReg, shortHyper, std::shared_ptr<short1DReg> >(
              clsVector, "short1DReg", py::buffer_protocol())
              .def(py::init<const int>(), "Initialize giving size")
              .def(py::init<const axis &>(), "Initialize from an axis")
              .def(py::init<std::shared_ptr<hypercube> >(), "Initialize with hypercube")

              .def("clone",
                   (std::shared_ptr<short1DReg>(short1DReg::*)() const) &
                       short1DReg::clone,
                   "Make a copy of the vector")
              .def("cloneSpace",
                   (std::shared_ptr<short1DReg>(short1DReg::*)() const) &
                       short1DReg::cloneSpace,
                   "Make a copy of the vector space")
              .def("allocate", (void (short1DReg::*)()) & short1DReg::allocate,
                   "Allocate the array")

              .def_buffer([](short1DReg &m) -> py::buffer_info {
                   return py::buffer_info(m.getVals(), sizeof(short),
                                          py::format_descriptor<int>::format(), 1,
                                          {m.getHyper()->getAxis(1).n}, {sizeof(short)});
              });
     }
} // namespace SEP
