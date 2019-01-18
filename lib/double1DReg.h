#pragma once
#include <doubleHyper.h>
#include <cstdint>
#include <iostream>
#include "boost/multi_array.hpp"
typedef boost::multi_array<double, 1> double1D;
namespace SEP {
class double1DReg : public doubleHyper {
 public:
  double1DReg() { ; }
  double1DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  double1DReg(const int n) {
    std::vector<SEP::axis> a(1, SEP::axis(n));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  double1DReg(const SEP::axis &a) {
    std::vector<SEP::axis> as(1, a);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(as));
    initNoData(hyp);
  }
  double1DReg(std::shared_ptr<SEP::hypercube> hyper, const double1D &vals) {
    initData(hyper, vals);
  }
  double1DReg(const int n, double1D &vals) {
    std::vector<SEP::axis> a(1, SEP::axis(n));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  double1DReg(const SEP::axis &a, const double1D &vals) {
    std::vector<SEP::axis> as(1, a);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(as));
    initData(hyp, vals);
  }
  void allocate() {
    std::vector<int> ns = getHyper()->getNs();
    _mat.reset(new double1D(boost::extents[ns[0]]));

    setData(_mat->data());
    ;
  }
  std::shared_ptr<double1DReg> window(const std::vector<int> &nw,
                                      const std::vector<int> &fw,
                                      const std::vector<int> &jw) const;
  std::shared_ptr<double1DReg> window(const int nw, const int fw,
                                      const int jw) {
    std::vector<int> nws;
    nws.push_back(nw);
    std::vector<int> fws;
    fws.push_back(fw);
    std::vector<int> jws;
    jws.push_back(jw);
    return (window(nws, fws, jws));
  }
  std::shared_ptr<double1DReg> clone() const;
  std::shared_ptr<double1DReg> cloneSpace() const;
  virtual void cleanMemory() { setSpace(); }
  std::shared_ptr<double1D> _mat;

 protected:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  //  void initData(std::shared_ptr<SEP::hypercube> hyp, const float *vals);
  void initData(std::shared_ptr<SEP::hypercube> hyp, const double1D &vals);
};

}  // namespace SEP
