#pragma once
#include <hypercube.h>
#include <cassert>
#include <cstdint>
#include <sstream>
#include "Vector.h"
#include "regSpace.h"

namespace SEP {

class doubleHyper : public Vector, public regSpace {
 public:
  doubleHyper() { ; }

  bool getSpaceOnly() const { return _spaceOnly; }
  virtual void add(std::shared_ptr<doubleHyper> vec);
  virtual void scale(const double val) override;
  virtual void scaleAdd(std::shared_ptr<doubleHyper> vec2, const double sc1,
                        const double sc2);
  virtual void random() override;
  virtual void signum();
  virtual void mult(std::shared_ptr<doubleHyper> vec2);
  virtual double dot(std::shared_ptr<doubleHyper> vec2) const;
  void createMask(const float zero, const float err);
  void setData(double *ptr) {
    _vals = ptr;
    setNotSpace();
    setMemPtr((void *)ptr, sizeof(double));
  }
  void calcCheckSum() override;
  void setCheckSum(const uint64_t x) { _checkSum = x; }
  bool isDifferent(std::shared_ptr<doubleHyper> vec2) {
    calcCheckSum();
    if (vec2->getCheckSum() != getCheckSum()) return true;
    return false;
  }

  double norm(const int n) const;
  void set(const double val);
  void zero() { set(0.); }

  double *getVals() { return _vals; }
  const double *getCVals() const { return _vals; }
  virtual void softClip(const float val) override;
  virtual double absMax() const override;
  double min() const;
  double max() const;
  virtual void infoStream(const int lev, std::stringstream &x) override;
  virtual bool checkSame(const std::shared_ptr<SEP::doubleHyper> vec2) const;
  uint64_t getCheckSum() { return _checkSum; }

 private:
  double *_vals;
  uint64_t _checkSum;
};

}  // namespace SEP
