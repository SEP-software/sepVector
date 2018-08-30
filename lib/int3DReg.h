#pragma once
#include <intHyper.h>
#include "boost/multi_array.hpp"
typedef boost::multi_array<int, 3> int3D;
namespace SEP {
class int3DReg : public intHyper {
 public:
  int3DReg() { ; }
  int3DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  int3DReg(const int n1, const int n2, const int n3) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    a.push_back(SEP::axis(n3));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  int3DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  int3DReg(std::shared_ptr<SEP::hypercube> hyper, const int3D &vals) {
    initData(hyper, vals);
  }
  int3DReg(int n1, int n2, int n3, int3D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    a.push_back(SEP::axis(n3));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  int3DReg(SEP::axis &a1, SEP::axis &a2, SEP::axis &a3, int3D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  void allocate() {
    std::vector<int> ns = getHyper()->getNs();
    _mat.reset(new int3D(boost::extents[ns[2]][ns[1]][ns[0]]));

    setData(_mat->data());
    ;
  }
  std::shared_ptr<int3DReg> clone() const;
  std::shared_ptr<int3DReg> cloneSpace() const;
  virtual void cleanMemory() {
    _mat = 0;
    setSpace();
  }
  std::shared_ptr<int3D> _mat;

 protected:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  void initData(std::shared_ptr<SEP::hypercube> hyp,
                std::shared_ptr<int3D> vals);

  void initData(std::shared_ptr<SEP::hypercube> hyp, const int3D &vals);
};
}  // namespace SEP
