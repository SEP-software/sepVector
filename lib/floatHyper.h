#pragma once
#include <hypercube.h>
#include <cassert>
#include <cstdint>
#include <sstream>
#include "Vector.h"
#include "regSpace.h"

namespace SEP {

class floatHyper : public Vector, public regSpace {
 public:
  floatHyper() { ; }

  bool getSpaceOnly() const { return _spaceOnly; }
  virtual void add(std::shared_ptr<floatHyper> vec);
  virtual void scale(const double val);
  virtual void scaleAdd(std::shared_ptr<floatHyper> vec2, const double sc1,
                        const double sc2);
  virtual void random();
  virtual void signum();
  virtual void mult(std::shared_ptr<floatHyper> vec2);
  virtual double dot(std::shared_ptr<floatHyper> vec2) const;
  void createMask(const float zero, const float err);
  void setData(float *ptr) {
    _vals = ptr;
    setNotSpace();
    setMemPtr((void *)ptr, sizeof(float));
  }
  void calcCheckSum();
  void setCheckSum(const uint64_t x) { _checkSum = x; }
  bool isDifferent(std::shared_ptr<floatHyper> vec2) {
    calcCheckSum();
    if (vec2->getCheckSum() != getCheckSum()) return true;
    return false;
  }

  double norm(const int n) const;
  void set(const float val);
  void zero() { set(0.); }

  float *getVals() { return _vals; }
  const float *getCVals() const { return _vals; }
  virtual void softClip(const float val);
  virtual double absMax() const;
  double min() const;
  double max() const;
  virtual void infoStream(const int lev, std::stringstream &x) override;

  virtual bool checkSame(const std::shared_ptr<SEP::floatHyper> vec2) const;
  uint64_t getCheckSum() { return _checkSum; }

 private:
  float *_vals;
  uint64_t _checkSum;
};

}  // namespace SEP
