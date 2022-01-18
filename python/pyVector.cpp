
#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
namespace SEP
{
    void init_floatT(py::module &);

    void init_floatR(py::module &);
    void init_doubleR(py::module &);
    void init_complexDR(py::module &);
    void init_complexR(py::module &);
    void init_byteR(py::module &);
    void init_intR(py::module &);
    void init_shortR(py::module &);
    void init_rect(py::module &);
    void init_base(py::module &);
    void init_byteT(py::module &);
    void init_doubleT(py::module &);
    void init_complexT(py::module &);
    void init_complexDT(py::module &);
    void init_intT(py::module &);
    void init_longT(py::module &);
    void init_shortT(py::module &);
    using namespace SEP;

    PYBIND11_MODULE(pySepVector, clsVector)

    {
        init_base(clsVector);

        init_floatR(clsVector);
        init_rect(clsVector);

        init_doubleR(clsVector);
        init_complexR(clsVector);
        init_intR(clsVector);
        init_complexDR(clsVector);
        init_byteR(clsVector);
        init_shortR(clsVector);

        init_byteT(clsVector);
        init_doubleT(clsVector);
        init_complexT(clsVector);
        init_complexDT(clsVector);
        init_intT(clsVector);
        init_shortT(clsVector);
        init_floatT(clsVector);
        init_longT(clsVector);
    }
}
