#pragma once
#include <intHyper.h>
#include <cstdint>
#include <iostream>
#include "boost/multi_array.hpp"
typedef boost::multi_array<int, 1> int1D;
namespace SEP {
class int1DReg : public intHyper {
 public:
  int1DReg() { ; }
  int1DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  int1DReg(const int n) {
    std::vector<SEP::axis> a(1, SEP::axis(n));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  int1DReg(const SEP::axis &a) {
    std::vector<SEP::axis> as(1, a);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(as));
    initNoData(hyp);
  }
  int1DReg(std::shared_ptr<SEP::hypercube> hyper, const int1D &vals) {
    initData(hyper, vals);
  }
  int1DReg(const int n, int1D &vals) {
    std::vector<SEP::axis> a(1, SEP::axis(n));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  int1DReg(const SEP::axis &a, const int1D &vals) {
    std::vector<SEP::axis> as(1, a);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(as));
    initData(hyp, vals);
  }
  void allocate() {
    std::vector<int> ns = getHyper()->getNs();
    _mat.reset(new int1D(boost::extents[ns[0]]));

    setData(_mat->data());
    ;
  }
  std::shared_ptr<int1DReg> window(const std::vector<int> &nw,
                                   const std::vector<int> &fw,
                                   const std::vector<int> &jw) const;
  std::shared_ptr<int1DReg> window(const int nw, const int fw, const int jw) {
    std::vector<int> nws;
    nws.push_back(nw);
    std::vector<int> fws;
    fws.push_back(fw);
    std::vector<int> jws;
    jws.push_back(jw);
    return (window(nws, fws, jws));
  }
  std::shared_ptr<int1DReg> clone() const;
  std::shared_ptr<int1DReg> cloneSpace() const;
  virtual void cleanMemory() { setSpace(); }
  std::shared_ptr<int1D> _mat;

 protected:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  //  void initData(std::shared_ptr<SEP::hypercube> hyp, const float *vals);
  void initData(std::shared_ptr<SEP::hypercube> hyp, const int1D &vals);
};

}  // namespace SEP
