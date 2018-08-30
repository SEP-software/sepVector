#pragma once
#include <byteHyper.h>
#include <cstdint>
#include <iostream>
#include "boost/multi_array.hpp"
typedef boost::multi_array<unsigned char, 1> byte1D;
namespace SEP {
class byte1DReg : public byteHyper {
 public:
  byte1DReg() { ; }
  byte1DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  byte1DReg(const int n) {
    std::vector<SEP::axis> a(1, SEP::axis(n));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  byte1DReg(const SEP::axis &a) {
    std::vector<SEP::axis> as(1, a);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(as));
    initNoData(hyp);
  }
  byte1DReg(std::shared_ptr<SEP::hypercube> hyper, const byte1D &vals) {
    initData(hyper, vals);
  }
  byte1DReg(const int n, byte1D &vals) {
    std::vector<SEP::axis> a(1, SEP::axis(n));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  byte1DReg(const SEP::axis &a, const byte1D &vals) {
    std::vector<SEP::axis> as(1, a);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(as));
    initData(hyp, vals);
  }
  void allocate() {
    std::vector<int> ns = getHyper()->getNs();
    _mat.reset(new byte1D(boost::extents[ns[0]]));

    setData(_mat->data());
    ;
  }
  std::shared_ptr<byte1DReg> clone() const;
  std::shared_ptr<byte1DReg> cloneSpace() const;
  virtual void cleanMemory() { setSpace(); }
  std::shared_ptr<byte1D> _mat;

 protected:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  //  void initData(std::shared_ptr<SEP::hypercube> hyp, const float *vals);
  void initData(std::shared_ptr<SEP::hypercube> hyp, const byte1D &vals);
};

}  // namespace SEP
