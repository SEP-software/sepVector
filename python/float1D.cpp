#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "float6DReg.h"
#include "float5DReg.h"
#include "float4DReg.h"
#include "float3DReg.h"
#include "float2DReg.h"
#include "float1DReg.h"

namespace py = pybind11;
using namespace SEP;
void init_1dfloat(py::module &clsVector){
py::class_<float1DReg, floatHyper, std::shared_ptr<float1DReg>>(
      clsVector, "float1DReg", py::buffer_protocol())
      .def(py::init<const int>(), "Initialize giving size")
      .def(py::init<const axis &>(), "Initialize from an axis")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
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
      py::class_<float3DReg, floatHyper, std::shared_ptr<float3DReg>>(
      clsVector, "float3DReg", py::buffer_protocol())
      .def(py::init<const int, const int, const int>(),
           "Initialize giving size")
      .def(py::init<std::shared_ptr<hypercube>>(), "Initialize with hypercube")
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
           (std::shared_ptr<float1DReg>(float3DReg::*)(
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
}