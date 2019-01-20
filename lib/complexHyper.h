#pragma once
#include <hypercube.h>
#include <complex>
#include <cstdint>
#include <sstream>
#include "regSpace.h"

namespace SEP {

class complexHyper : public regSpace {
 public:
  complexHyper() { ; }

  bool getSpaceOnly() const { return _spaceOnly; }
  virtual void add(std::shared_ptr<complexHyper> vec);
  /*
   virtual void scale(const std::complex<double> val);
   virtual void scaleAdd(std::shared_ptr<complexHyper> vec2,
                         const std::complex<double> sc1,
                         const std::complex<double> sc2);
                         */
  virtual void random();
  virtual void mult(std::shared_ptr<complexHyper> vec2);
  void setData(std::complex<float> *ptr) {
    _vals = ptr;
    setNotSpace();
    setMemPtr((void *)ptr, sizeof(std::complex<float>));
  }
  virtual void setSpace() { _spaceOnly = true; }
  virtual void setNotSpace() { _spaceOnly = false; }
  inline bool spaceOnly() const { return _spaceOnly; }

  void calcCheckSum();
  void setCheckSum(const uint64_t x) { _checkSum = x; }
  bool isDifferent(std::shared_ptr<complexHyper> vec2) {
    calcCheckSum();
    if (vec2->getCheckSum() != getCheckSum()) return true;
    return false;
  }

  void zero() {
    std::complex<float> val = {0., 0.};
    set(val);
  }
  void set(const std::complex<float> val);

  std::complex<float> *getVals() { return _vals; }
  const std::complex<float> *getCVals() const { return _vals; }

  virtual void infoStream(const int lev, std::stringstream &x);
  virtual bool checkSame(const std::shared_ptr<SEP::complexHyper> vec2) const;
  uint64_t getCheckSum() { return _checkSum; }
  std::string _vecType;

 private:
  std::complex<float> *_vals;
  bool _spaceOnly;

  uint64_t _checkSum;
};

}  // namespace SEP
