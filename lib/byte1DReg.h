#ifndef byte1d_reg_h
#define byte1d_reg_h 1
#include <byteHyper.h>
#include <cstdint>
#include <iostream>
#include "boost/multi_array.hpp"
#include "byte2DReg.h"
#include "byte3DReg.h"
#include "byte4DReg.h"
#include "byte5DReg.h"
#include "byte6DReg.h"

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
  byte1DReg(const std::shared_ptr<byte6DReg> old, const int iax1,
            const bool rev1, const std::vector<int> &ipos,
            const std::vector<int> &beg, const std::vector<int> &end);
  byte1DReg(const std::shared_ptr<byte5DReg> old, const int iax1,
            const bool rev1, const std::vector<int> &ipos,
            const std::vector<int> &beg, const std::vector<int> &end);
  byte1DReg(const std::shared_ptr<byte4DReg> old, const int iax1,
            const bool rev1, const std::vector<int> &ipos,
            const std::vector<int> &beg, const std::vector<int> &end);
  byte1DReg(const std::shared_ptr<byte3DReg> old, const int iax1,
            const bool rev1, const std::vector<int> &ipos,
            const std::vector<int> &beg, const std::vector<int> &end);
  byte1DReg(const std::shared_ptr<byte2DReg> old, const int iax1,
            const bool rev1, const std::vector<int> &ipos,
            const std::vector<int> &beg, const std::vector<int> &end);
  byte1DReg(const std::shared_ptr<byte1DReg> old, const int iax1,
            const bool rev1, const std::vector<int> &ipos,
            const std::vector<int> &beg, const std::vector<int> &end);
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
  std::shared_ptr<byte1DReg> window(const std::vector<int> &nw,
                                    const std::vector<int> &fw,
                                    const std::vector<int> &jw) const;
  std::shared_ptr<byte1DReg> window(const int nw, const int fw, const int jw) {
    std::vector<int> nws;
    nws.push_back(nw);
    std::vector<int> fws;
    fws.push_back(fw);
    std::vector<int> jws;
    jws.push_back(jw);
    return (window(nws, fws, jws));
  }

 protected:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  //  void initData(std::shared_ptr<SEP::hypercube> hyp, const float *vals);
  void initData(std::shared_ptr<SEP::hypercube> hyp, const byte1D &vals);
};

}  // namespace SEP
#endif
