#pragma once
#include <hypercube.h>
#include <cassert>
#include <cstdint>
#include <sstream>
#include "regSpace.h"
namespace SEP {

class intHyper : public regSpace {
 public:
  intHyper() { ; }

  bool getSpaceOnly() const { return _spaceOnly; }
  virtual void add(std::shared_ptr<intHyper> vec);
  virtual void scale(const double val);
  virtual void scaleAdd(std::shared_ptr<intHyper> vec2, const double sc1,
                        const double sc2);
  virtual void random();
  virtual void signum();
  virtual void mult(std::shared_ptr<intHyper> vec2);
  virtual double dot(std::shared_ptr<intHyper> vec2) const;
  virtual void setSpace() { _spaceOnly = true; }
  virtual void setNotSpace() { _spaceOnly = false; }
  inline bool spaceOnly() const { return _spaceOnly; }
  void createMask(const int zero, const int err);
  void setData(int *ptr) {
    _vals = ptr;
    setNotSpace();
    setMemPtr((void *)ptr, sizeof(int));
  }
  void calcCheckSum();
  void setCheckSum(const uint64_t x) { _checkSum = x; }
  bool isDifferent(std::shared_ptr<intHyper> vec2) {
    calcCheckSum();
    if (vec2->getCheckSum() != getCheckSum()) return true;
    return false;
  }

  long long norm(const int n) const;
  void zero();

  int *getVals() { return _vals; }
  const int *getCVals() const { return _vals; }
  virtual void softClip(const float val);
  virtual int absMax() const;
  int min() const;
  int max() const;
  virtual void infoStream(const int lev, std::stringstream &x);
  virtual bool checkSame(const std::shared_ptr<SEP::intHyper> vec2) const;
  uint64_t getCheckSum() { return _checkSum; }

  bool _spaceOnly;
  std::string _vecType;

 private:
  int *_vals;
  uint64_t _checkSum;
};

}  // namespace SEP
