#ifndef complex1d_reg_h
#define complex1d_reg_h 1
#include <complexHyper.h>
#include <cstdint>
#include <iostream>
#include "boost/multi_array.hpp"
#include "complex2DReg.h"
#include "complex3DReg.h"
#include "complex4DReg.h"
#include "complex5DReg.h"
#include "complex6DReg.h"

typedef boost::multi_array<std::complex<float>, 1> complex1D;
namespace SEP {
class complex1DReg : public complexHyper {
 public:
  complex1DReg() { ; }
  complex1DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  complex1DReg(const int n) {
    std::vector<SEP::axis> a(1, SEP::axis(n));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  complex1DReg(const SEP::axis &a) {
    std::vector<SEP::axis> as(1, a);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(as));
    initNoData(hyp);
  }
  complex1DReg(std::shared_ptr<SEP::hypercube> hyper, const complex1D &vals) {
    initData(hyper, vals);
  }
  complex1DReg(const int n, complex1D &vals) {
    std::vector<SEP::axis> a(1, SEP::axis(n));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  complex1DReg(const SEP::axis &a, const complex1D &vals) {
    std::vector<SEP::axis> as(1, a);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(as));
    initData(hyp, vals);
  }
  complex1DReg(const std::shared_ptr<complex6DReg> old, const int iax1,
               const bool rev1, const std::vector<int> &ipos,
               const std::vector<int> &beg, const std::vector<int> &end);
  complex1DReg(const std::shared_ptr<complex5DReg> old, const int iax1,
               const bool rev1, const std::vector<int> &ipos,
               const std::vector<int> &beg, const std::vector<int> &end);
  complex1DReg(const std::shared_ptr<complex4DReg> old, const int iax1,
               const bool rev1, const std::vector<int> &ipos,
               const std::vector<int> &beg, const std::vector<int> &end);
  complex1DReg(const std::shared_ptr<complex3DReg> old, const int iax1,
               const bool rev1, const std::vector<int> &ipos,
               const std::vector<int> &beg, const std::vector<int> &end);
  complex1DReg(const std::shared_ptr<complex2DReg> old, const int iax1,
               const bool rev1, const std::vector<int> &ipos,
               const std::vector<int> &beg, const std::vector<int> &end);
  complex1DReg(const std::shared_ptr<complex1DReg> old, const int iax1,
               const bool rev1, const std::vector<int> &ipos,
               const std::vector<int> &beg, const std::vector<int> &end);
  void allocate() {
    std::vector<int> ns = getHyper()->getNs();
    _mat.reset(new complex1D(boost::extents[ns[0]]));

    setData(_mat->data());
    ;
  }
  std::shared_ptr<complex1DReg> window(const std::vector<int> &nw,
                                       const std::vector<int> &fw,
                                       const std::vector<int> &jw) const;
  std::shared_ptr<complex1DReg> window(const int nw, const int fw,
                                       const int jw) {
    std::vector<int> nws;
    nws.push_back(nw);
    std::vector<int> fws;
    fws.push_back(fw);
    std::vector<int> jws;
    jws.push_back(jw);
    return (window(nws, fws, jws));
  }
  std::shared_ptr<complex1DReg> clone() const;
  std::shared_ptr<complex1DReg> cloneSpace() const;
  virtual void cleanMemory() { setSpace(); }
  std::shared_ptr<complex1D> _mat;

 protected:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  //  void initData(std::shared_ptr<SEP::hypercube> hyp, const float *vals);
  void initData(std::shared_ptr<SEP::hypercube> hyp, const complex1D &vals);
};

}  // namespace SEP
#endif
