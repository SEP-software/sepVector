#ifndef short1d_reg_h
#define short1d_reg_h 1
#include <shortHyper.h>
#include <cstdint>
#include <iostream>
#include "boost/multi_array.hpp"
typedef boost::multi_array<short, 1> short1D;
namespace SEP {
class short1DReg : public shortHyper {
 public:
  short1DReg() { ; }
  short1DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  short1DReg(const int n) {
    std::vector<SEP::axis> a(1, SEP::axis(n));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  short1DReg(const SEP::axis &a) {
    std::vector<SEP::axis> as(1, a);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(as));
    initNoData(hyp);
  }
  short1DReg(std::shared_ptr<SEP::hypercube> hyper, const short1D &vals) {
    initData(hyper, vals);
  }
  short1DReg(const int n, short1D &vals) {
    std::vector<SEP::axis> a(1, SEP::axis(n));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  short1DReg(const SEP::axis &a, const short1D &vals) {
    std::vector<SEP::axis> as(1, a);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(as));
    initData(hyp, vals);
  }
  void allocate() {
    std::vector<int> ns = getHyper()->getNs();
    _mat.reset(new short1D(boost::extents[ns[0]]));

    setData(_mat->data());
    ;
  }
  std::shared_ptr<short1DReg> clone() const;
  std::shared_ptr<short1DReg> cloneSpace() const;
  virtual void cleanMemory() { setSpace(); }
  std::shared_ptr<short1D> _mat;

 protected:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  //  void initData(std::shared_ptr<SEP::hypercube> hyp, const float *vals);
  void initData(std::shared_ptr<SEP::hypercube> hyp, const short1D &vals);
};

}  // namespace SEP
#endif
