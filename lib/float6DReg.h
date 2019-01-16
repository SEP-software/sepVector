#pragma once
#include "boost/multi_array.hpp"

#include <floatHyper.h>

typedef boost::multi_array<float, 6> float6D;
namespace SEP {
class float6DReg : public floatHyper {
 public:
  float6DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  float6DReg(const int n1, const int n2, const int n3, const int n4,
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
  float6DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
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
  float6DReg(std::shared_ptr<SEP::hypercube> hyper, const float6D &vals) {
    initData(hyper, vals);
  }
  float6DReg(const int n1, const int n2, const int n3, const int n4,
             const int n5, const int n6, float6D &vals) {
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
  float6DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
             const SEP::axis &a4, const SEP::axis &a5, const SEP::axis &a6,
             float6D &vals) {
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
    _mat.reset(
        new float6D(boost::extents[ns[5]][ns[4]][ns[3]][ns[2]][ns[1]][ns[0]]));

    setData(_mat->data());
    ;
  }
  std::shared_ptr<float6DReg> clone() const;
  std::shared_ptr<float6DReg> cloneSpace() const;
  virtual void cleanMemory() {
    _mat = 0;
    setSpace();
  }
  std::shared_ptr<float6D> _mat;

 protected:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  void initData(std::shared_ptr<SEP::hypercube> hyp, const float6D &vals);
};
}  // namespace SEP
