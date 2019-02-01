#ifndef float1d_reg_h
#define float1d_reg_h 1
#include <floatHyper.h>
#include <cstdint>
#include <iostream>
#include "float2DReg.h"
#include "float3DReg.h"
#include "float4DReg.h"
#include "float5DReg.h"
#include "float6DReg.h"

#include "boost/multi_array.hpp"
typedef boost::multi_array<float, 1> float1D;
namespace SEP {
class float1DReg : public floatHyper {
 public:
  float1DReg() { ; }
  float1DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  float1DReg(const int n) {
    std::vector<SEP::axis> a(1, SEP::axis(n));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  float1DReg(const SEP::axis &a) {
    std::vector<SEP::axis> as(1, a);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(as));
    initNoData(hyp);
  }
  float1DReg(std::shared_ptr<SEP::hypercube> hyper, const float1D &vals) {
    initData(hyper, vals);
  }
  float1DReg(const int n, float1D &vals) {
    std::vector<SEP::axis> a(1, SEP::axis(n));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  float1DReg(const SEP::axis &a, const float1D &vals) {
    std::vector<SEP::axis> as(1, a);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(as));
    initData(hyp, vals);
  }
  float1DReg(const std::shared_ptr<float6DReg> old, const int iax1,
             const bool rev1, const std::vector<int> &ipos,
             const std::vector<int> &beg, const std::vector<int> &end);
  float1DReg(const std::shared_ptr<float5DReg> old, const int iax1,
             const bool rev1, const std::vector<int> &ipos,
             const std::vector<int> &beg, const std::vector<int> &end);
  float1DReg(const std::shared_ptr<float4DReg> old, const int iax1,
             const bool rev1, const std::vector<int> &ipos,
             const std::vector<int> &beg, const std::vector<int> &end);
  float1DReg(const std::shared_ptr<float3DReg> old, const int iax1,
             const bool rev1, const std::vector<int> &ipos,
             const std::vector<int> &beg, const std::vector<int> &end);
  float1DReg(const std::shared_ptr<float2DReg> old, const int iax1,
             const bool rev1, const std::vector<int> &ipos,
             const std::vector<int> &beg, const std::vector<int> &end);
  float1DReg(const std::shared_ptr<float1DReg> old, const int iax1,
             const bool rev1, const std::vector<int> &ipos,
             const std::vector<int> &beg, const std::vector<int> &end);
  void allocate() {
    std::vector<int> ns = getHyper()->getNs();
    _mat.reset(new float1D(boost::extents[ns[0]]));

    setData(_mat->data());
    ;
  }
  std::shared_ptr<float1DReg> window(const std::vector<int> &nw,
                                     const std::vector<int> &fw,
                                     const std::vector<int> &jw) const;
  std::shared_ptr<float1DReg> window(const int nw, const int fw, const int jw) {
    std::vector<int> nws;
    nws.push_back(nw);
    std::vector<int> fws;
    fws.push_back(fw);
    std::vector<int> jws;
    jws.push_back(jw);
    return (window(nws, fws, jws));
  }
  std::shared_ptr<float1DReg> clone() const;
  std::shared_ptr<float1DReg> cloneSpace() const;
  virtual void cleanMemory() { setSpace(); }
  std::shared_ptr<float1D> _mat;

 protected:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  //  void initData(std::shared_ptr<SEP::hypercube> hyp, const float *vals);
  void initData(std::shared_ptr<SEP::hypercube> hyp, const float1D &vals);
};

}  // namespace SEP
#endif
