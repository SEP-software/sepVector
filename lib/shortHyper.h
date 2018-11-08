#pragma once
#include <hypercube.h>
#include <cassert>
#include <cstdint>
#include <sstream>
#include "regSpace.h"
namespace SEP {

class shortHyper : public regSpace {
 public:
  shortHyper() { ; }

  bool getSpaceOnly() const { return _spaceOnly; }
  virtual void add(std::shared_ptr<shortHyper> vec);
  virtual void scale(const double val);
  virtual void scaleAdd(std::shared_ptr<shortHyper> vec2, const double sc1,
                        const double sc2);
  virtual void random();
  virtual void signum();
  virtual void mult(std::shared_ptr<shortHyper> vec2);
  virtual double dot(std::shared_ptr<shortHyper> vec2) const;
  virtual void setSpace() { _spaceOnly = true; }
  virtual void setNotSpace() { _spaceOnly = false; }
  inline bool spaceOnly() const { return _spaceOnly; }
  void createMask(const int zero, const int err);
  void setData(short *ptr) {
    _vals = ptr;
    setNotSpace();
    setMemPtr((void *)ptr, sizeof(short));
  }
  void calcCheckSum();
  void setCheckSum(const uint64_t x) { _checkSum = x; }
  bool isDifferent(std::shared_ptr<shortHyper> vec2) {
    calcCheckSum();
    if (vec2->getCheckSum() != getCheckSum()) return true;
    return false;
  }

  long long norm(const int n) const;
  void zero() { set(0); }
  void set(const short val);
  short *getVals() { return _vals; }
  const short *getCVals() const { return _vals; }
  virtual void softClip(const float val);
  virtual int absMax() const;
  int min() const;
  int max() const;
  virtual void infoStream(const int lev, std::stringstream &x);
  virtual bool checkSame(const std::shared_ptr<SEP::shortHyper> vec2) const;
  uint64_t getCheckSum() { return _checkSum; }

  bool _spaceOnly;
  std::string _vecType;

 private:
  short *_vals;
  uint64_t _checkSum;
};

}  // namespace SEP
