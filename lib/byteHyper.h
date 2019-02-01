#ifndef byte_hyper_h
#define byte_hyper_h 1
#include <hypercube.h>
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
  unsigned char cent(const float pct, const int j) const {
    long long iv = std::max(
        (long long)0, std::min((long long)(getHyper()->getN123() * pct / 100.),
                               getHyper()->getN123() - 1));
    return cent(iv, j);
  }
  unsigned char cent(const long long iv, const int j) const;
  void clip(const unsigned char bclip, const unsigned char eclip);
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
#endif
