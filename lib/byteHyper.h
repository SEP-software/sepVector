#pragma once
#include <hypercube.h>
#include <cassert>
#include <cstdint>
#include <sstream>
#include "regSpace.h"
namespace SEP {

class byteHyper : public regSpace {
 public:
  byteHyper() { ; }

  byteHyper(std::shared_ptr<SEP::hypercube> h) { setHyper(h->clone()); }

  bool getSpaceOnly() const { return _spaceOnly; }

  virtual void random();
  virtual void setSpace() { _spaceOnly = true; }
  virtual void setNotSpace() { _spaceOnly = false; }
  inline bool spaceOnly() const { return _spaceOnly; }

  void setData(unsigned char *ptr) {
    _vals = ptr;
    setNotSpace();
    setMemPtr((void *)ptr, sizeof(unsigned char));
  }
  void calcCheckSum();
  void setCheckSum(const uint64_t x) { _checkSum = x; }
  bool isDifferent(std::shared_ptr<byteHyper> vec2) {
    calcCheckSum();
    if (vec2->getCheckSum() != getCheckSum()) return true;
    return false;
  }

  long long norm(const int n) const;
  void zero() { set(0); }
  void set(const unsigned char val);

  unsigned char *getVals() { return _vals; }
  const unsigned char *getCVals() const { return _vals; }
  virtual int absMax() const;
  int min() const;
  int max() const;
  virtual void infoStream(const int lev, std::stringstream &x);

  virtual bool checkSame(const std::shared_ptr<SEP::byteHyper> vec2) const;
  uint64_t getCheckSum() { return _checkSum; }

  bool _spaceOnly;
  std::string _vecType;

 private:
  unsigned char *_vals;
  uint64_t _checkSum;
};

}  // namespace SEP
