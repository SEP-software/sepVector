#pragma once
#include <byteHyper.h>
#include "boost/multi_array.hpp"
typedef boost::multi_array<unsigned char, 3> byte3D;
namespace SEP {
class byte3DReg : public byteHyper {
 public:
  byte3DReg() { ; }
  byte3DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  byte3DReg(const int n1, const int n2, const int n3) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    a.push_back(SEP::axis(n3));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  byte3DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  byte3DReg(std::shared_ptr<SEP::hypercube> hyper, const byte3D &vals) {
    initData(hyper, vals);
  }
  byte3DReg(int n1, int n2, int n3, byte3D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    a.push_back(SEP::axis(n3));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  byte3DReg(SEP::axis &a1, SEP::axis &a2, SEP::axis &a3, byte3D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  void allocate() {
    std::vector<int> ns = getHyper()->getNs();
    _mat.reset(new byte3D(boost::extents[ns[2]][ns[1]][ns[0]]));

    setData(_mat->data());
    ;
  }
  std::shared_ptr<byte3DReg> clone() const;
  std::shared_ptr<byte3DReg> cloneSpace() const;
  virtual void cleanMemory() {
    _mat = 0;
    setSpace();
  }
  std::shared_ptr<byte3DReg> window(const std::vector<int> &nw,
                                    const std::vector<int> &fw,
                                    const std::vector<int> &jw) const;

  std::shared_ptr<byte3D> _mat;

 protected:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  void initData(std::shared_ptr<SEP::hypercube> hyp,
                std::shared_ptr<byte3D> vals);

  void initData(std::shared_ptr<SEP::hypercube> hyp, const byte3D &vals);
};
}  // namespace SEP
