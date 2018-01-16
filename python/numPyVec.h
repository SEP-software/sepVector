#include <float1DReg.h>
#include <float2DReg.h>
#include <float3DReg.h>
#include <float4DReg.h>
#include <floatHyper.h>
#include <numpy/arrayobject.h>

class numPyVec {
 public:
  numPyVec(giee::floatHyper &hyp, const bool copy = false);
  numPyVec(const giee::floatHyper &hyp, const std::vector<int> &nw,
           const std::vector<int> &fw, const std::vector<int> &jw) {
    windowInit(hyp, nw, fw, jw);
  }
  numPyVec(const giee::floatHyper &hyp, const std::vector<int> &nw) {
    std::vector<int> fw(nw.size(), 0), jw(nw.size(), 1);
    windowInit(hyp, nw, fw, jw);
  }
  numPyVec(PyObject *numpy, const std::vector<int> &n,
           const std::vector<float> &o, const std::vector<float> &d,
           const std::vector<std::string> &label);
  void windowInit(const giee::floatHyper &hyp, const std::vector<int> &nw,
                  const std::vector<int> &fw, const std::vector<int> &jw);

 private:
  std::vector<float> _vec;
  std::shared_ptr<SEP::hypercube> _hyper;
  std::shared_ptr<PyObject> _ar;
};
