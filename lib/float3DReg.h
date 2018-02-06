#pragma once
#include <floatHyper.h>
#include "boost/multi_array.hpp"
typedef boost::multi_array<float, 3> float3D;
namespace giee {
class float3DReg : public floatHyper {
 public:
  float3DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  float3DReg(const int n1, const int n2, const int n3) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    a.push_back(SEP::axis(n3));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  float3DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  float3DReg(std::shared_ptr<SEP::hypercube> hyper, const float3D &vals) {
    initData(hyper, vals);
  }
  float3DReg(int n1, int n2, int n3, float3D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    a.push_back(SEP::axis(n3));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  float3DReg(SEP::axis &a1, SEP::axis &a2, SEP::axis &a3, float3D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  void allocate() {
    std::vector<int> ns = getHyper()->getNs();
    _mat.reset(new float3D(boost::extents[ns[2]][ns[1]][ns[0]]));

    std::cerr << "in allocate" << ns[0] << std::endl;
    setData(_mat->data());
    ;
  }
  std::shared_ptr<float3DReg> clone() const;
  std::shared_ptr<float3DReg> cloneSpace() const;
  virtual void cleanMemory() {
    _mat = 0;
    setSpace();
  }
  std::shared_ptr<float3D> _mat;

 private:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  void initData(std::shared_ptr<SEP::hypercube> hyp, const float3D &vals);
};
}  // namespace giee
