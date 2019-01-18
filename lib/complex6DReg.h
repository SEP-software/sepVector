#pragma once
#include "boost/multi_array.hpp"

#include <complexHyper.h>

typedef boost::multi_array<std::complex<float>, 6> complex6D;
namespace SEP {
class complex6DReg : public complexHyper {
 public:
  complex6DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  complex6DReg(const int n1, const int n2, const int n3, const int n4,
               const int n5, const int n6) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    a.push_back(SEP::axis(n3));
    a.push_back(SEP::axis(n4));
    a.push_back(SEP::axis(n5));
    a.push_back(SEP::axis(n6));

    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  complex6DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
               const SEP::axis &a4, const SEP::axis &a5, const SEP::axis &a6) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);
    a.push_back(a4);
    a.push_back(a5);
    a.push_back(a6);

    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  complex6DReg(std::shared_ptr<SEP::hypercube> hyper, const complex6D &vals) {
    initData(hyper, vals);
  }
  complex6DReg(const int n1, const int n2, const int n3, const int n4,
               const int n5, const int n6, complex6D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    a.push_back(SEP::axis(n3));
    a.push_back(SEP::axis(n4));
    a.push_back(SEP::axis(n5));
    a.push_back(SEP::axis(n6));

    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  complex6DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
               const SEP::axis &a4, const SEP::axis &a5, const SEP::axis &a6,
               complex6D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);
    a.push_back(a4);
    a.push_back(a5);
    a.push_back(a6);

    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  void allocate() {
    std::vector<int> ns = getHyper()->getNs();
    _mat.reset(new complex6D(
        boost::extents[ns[5]][ns[4]][ns[3]][ns[2]][ns[1]][ns[0]]));

    setData(_mat->data());
    ;
  }
  std::shared_ptr<complex6DReg> clone() const;
  std::shared_ptr<complex6DReg> cloneSpace() const;
  virtual void cleanMemory() {
    _mat = 0;
    setSpace();
  }
  std::shared_ptr<complex6DReg> window(const std::vector<int> &nw,
                                       const std::vector<int> &fw,
                                       const std::vector<int> &jw) const;
  std::shared_ptr<complex6D> _mat;

 private:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  void initData(std::shared_ptr<SEP::hypercube> hyp, const complex6D &vals);
};
}  // namespace SEP
