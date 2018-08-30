#pragma once
#include "boost/multi_array.hpp"

#include <complexHyper.h>

typedef boost::multi_array<std::complex<float>, 4> complex4D;
namespace SEP {
class complex4DReg : public complexHyper {
 public:
  complex4DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  complex4DReg(const int n1, const int n2, const int n3, const int n4) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    a.push_back(SEP::axis(n3));
    a.push_back(SEP::axis(n4));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  complex4DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
               const SEP::axis &a4) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);
    a.push_back(a4);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  complex4DReg(std::shared_ptr<SEP::hypercube> hyper, const complex4D &vals) {
    initData(hyper, vals);
  }
  complex4DReg(const int n1, const int n2, const int n3, const int n4,
               complex4D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    a.push_back(SEP::axis(n3));
    a.push_back(SEP::axis(n4));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  complex4DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
               const SEP::axis &a4, complex4D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);
    a.push_back(a4);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  void allocate() {
    std::vector<int> ns = getHyper()->getNs();
    _mat.reset(new complex4D(boost::extents[ns[3]][ns[2]][ns[1]][ns[0]]));

    setData(_mat->data());
    ;
  }
  std::shared_ptr<complex4DReg> clone() const;
  std::shared_ptr<complex4DReg> cloneSpace() const;
  virtual void cleanMemory() {
    _mat = 0;
    setSpace();
  }
  std::shared_ptr<complex4D> _mat;

 private:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  void initData(std::shared_ptr<SEP::hypercube> hyp, const complex4D &vals);
};
}  // namespace SEP
