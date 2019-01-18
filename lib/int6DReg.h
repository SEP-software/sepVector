#pragma once
#include "boost/multi_array.hpp"

#include <intHyper.h>

typedef boost::multi_array<int, 6> int6D;
namespace SEP {
class int6DReg : public intHyper {
 public:
  int6DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  int6DReg(const int n1, const int n2, const int n3, const int n4, const int n5,
           const int n6) {
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
  int6DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
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
  int6DReg(std::shared_ptr<SEP::hypercube> hyper, const int6D &vals) {
    initData(hyper, vals);
  }
  int6DReg(const int n1, const int n2, const int n3, const int n4, const int n5,
           const int n6, int6D &vals) {
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
  int6DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
           const SEP::axis &a4, const SEP::axis &a5, const SEP::axis &a6,
           int6D &vals) {
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
        new int6D(boost::extents[ns[5]][ns[4]][ns[3]][ns[2]][ns[1]][ns[0]]));

    setData(_mat->data());
    ;
  }
  std::shared_ptr<int6DReg> clone() const;
  std::shared_ptr<int6DReg> cloneSpace() const;
  std::shared_ptr<int6DReg> window(const std::vector<int> &nw,
                                   const std::vector<int> &fw,
                                   const std::vector<int> &jw) const;
  virtual void cleanMemory() {
    _mat = 0;
    setSpace();
  }
  std::shared_ptr<int6D> _mat;

 private:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  void initData(std::shared_ptr<SEP::hypercube> hyp, const int6D &vals);
};
}  // namespace SEP
