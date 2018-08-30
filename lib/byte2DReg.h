#pragma once
#include <byteHyper.h>
#include "boost/multi_array.hpp"
typedef boost::multi_array<unsigned char, 2> byte2D;
namespace SEP {
class byte2DReg : public byteHyper {
 public:
  byte2DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  byte2DReg(const int n1, const int n2) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  byte2DReg(const SEP::axis &a1, const SEP::axis &a2) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  byte2DReg(std::shared_ptr<SEP::hypercube> hyper, const byte2D &vals) {
    initData(hyper, vals);
  }
  byte2DReg(int n1, int n2, byte2D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  byte2DReg(SEP::axis &a1, SEP::axis &a2, byte2D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  void allocate() {
    std::vector<int> ns = getHyper()->getNs();
    _mat.reset(new byte2D(boost::extents[ns[1]][ns[0]]));

    setData(_mat->data());
    ;
  }
  std::shared_ptr<byte2DReg> clone() const;
  std::shared_ptr<byte2DReg> cloneSpace() const;
  virtual void cleanMemory() { setSpace(); }
  std::shared_ptr<byte2D> _mat;

 private:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  void initData(std::shared_ptr<SEP::hypercube> hyp, const byte2D &vals);
};
}  // namespace SEP
