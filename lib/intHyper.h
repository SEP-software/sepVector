#pragma once
#include <hypercube.h>
#include <cassert>
#include <cstdint>
#include <sstream>
namespace SEP {

class intHyper {
 public:
  intHyper() { ; }

  void setHyper(std::shared_ptr<SEP::hypercube> h) { _hyper = h->clone(); }

  bool getSpaceOnly() const { return _spaceOnly; }
  virtual void add(std::shared_ptr<intHyper> vec);
  virtual void scale(const double val);
  virtual void scaleAdd(std::shared_ptr<intHyper> vec2, const double sc1,
                        const double sc2);
  virtual void random();
  virtual void norm(int norm);
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
  std::shared_ptr<SEP::hypercube> getHyper() const { return _hyper; }
  virtual bool checkSame(const std::shared_ptr<SEP::intHyper> vec2) const;
  uint64_t getCheckSum() { return _checkSum; }

  bool _spaceOnly;

 private:
  std::shared_ptr<SEP::hypercube> _hyper;
  int *_vals;
  uint64_t _checkSum;
};

}  // namespace SEP
