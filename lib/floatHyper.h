#ifndef float_hyper_h
#define float_hyper_h 1
#include <hypercube.h>
#include <cstdint>
#include <sstream>
#include "SEPException.h"
#include "Vector.h"
#include "regSpace.h"

namespace SEP {

class floatHyper : public Vector, public regSpace {
 public:
  floatHyper() { ; }

  bool getSpaceOnly() const { return _spaceOnly; }
  virtual void add(std::shared_ptr<floatHyper> vec);
  virtual void scale(const double val) override;

  virtual void scaleAdd(std::shared_ptr<floatHyper> vec2, const double sc1,
                        const double sc2);

  virtual void random() override;

  virtual void signum();

  virtual void mult(std::shared_ptr<floatHyper> vec2);

  virtual double dot(std::shared_ptr<floatHyper> vec2) const;
  float cent(const float pct, const int j) const {
    long long iv = std::max(
        (long long)0, std::min((long long)(getHyper()->getN123() * pct / 100.),
                               getHyper()->getN123() - 1));
    return cent(iv, j);
  }
  float cent(const long long iv, const int j) const;
  void clip(const float bpclip, const float epclip);
  void clipVector(const std::shared_ptr<floatHyper> beg,
                  const std::shared_ptr<floatHyper> end);
  void createMask(const float zero, const float err);
  void setData(float *ptr) {
    _vals = ptr;
    setNotSpace();
    setMemPtr((void *)ptr, sizeof(float));
  }
  void calcCheckSum() override;
  void setCheckSum(const uint64_t x) { _checkSum = x; }
  bool isDifferent(std::shared_ptr<floatHyper> vec2) {
    calcCheckSum();
    if (vec2->getCheckSum() != getCheckSum()) return true;
    return false;
  }

  double norm(const int n) const;

  void set(const float val);
  void zero() {
    std::cerr << "in this zero " << std::endl;
    set(0.);
  }

  float *getVals() { return _vals; }
  const float *getCVals() const { return _vals; }
  virtual void softClip(const float val) override;
  virtual double absMax() const override;
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
#endif
