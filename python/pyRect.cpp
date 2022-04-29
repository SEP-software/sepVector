
#include "rectFilter.h"
#include "regSpace.h"
#include "short1DReg.h"
#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;
namespace SEP
{

     void init_rect(py::module &clsVector)
     {

          py::class_<rectFilter2D, float2DReg, std::shared_ptr<rectFilter2D> >(
              clsVector, "rectFilter2D")
              .def(py::init<const std::vector<int> &, const std::vector<int> &,
                            const bool>(),
                   "Initialize rectFilter2D")
              .def("clone",
                   (std::shared_ptr<rectFilter2D>(rectFilter2D::*)() const) &
                       rectFilter2D::clone,
                   "Make a copy of the vector")

              .def("cloneSpace",
                   (std::shared_ptr<rectFilter2D>(rectFilter2D::*)() const) &
                       rectFilter2D::cloneSpace,
                   "Make a copy of the vector space")
              .def_buffer([](rectFilter2D &m) -> py::buffer_info {
                   return py::buffer_info(
                       m.getVals(), sizeof(float), py::format_descriptor<float>::format(),
                       2,
                       {
                           m.getHyper()->getAxis(2).n,
                           m.getHyper()->getAxis(1).n,
                       },
                       {sizeof(float) * m.getHyper()->getAxis(1).n, sizeof(float)});
              });

          py::class_<rectFilter1D, float1DReg, std::shared_ptr<rectFilter1D> >(
              clsVector, "rectFilter1D", py::buffer_protocol())
              .def(py::init<const std::vector<int> &, const std::vector<int> &,
                            const bool>(),
                   "Initialize rectFilter1D")
              .def("clone",
                   (std::shared_ptr<rectFilter1D>(rectFilter1D::*)() const) &
                       rectFilter1D::clone,
                   "Make a copy of the vector")

              .def("cloneSpace",
                   (std::shared_ptr<rectFilter1D>(rectFilter1D::*)() const) &
                       rectFilter1D::cloneSpace,
                   "Make a copy of the vector space")
              .def_buffer([](rectFilter1D &m) -> py::buffer_info {
                   return py::buffer_info(m.getVals(), sizeof(float),
                                          py::format_descriptor<float>::format(), 1,
                                          {m.getHyper()->getAxis(1).n}, {sizeof(float)});
              });
     }
} // namespace SEP
