#pragma once
#include <hypercube.h>
#include <cassert>
#include <cstdint>
#include <sstream>
#include "Vector.h"
namespace giee {

class floatHyper : public Vector {
 public:
  floatHyper() { ; }

  void setHyper(std::shared_ptr<SEP::hypercube> h) { _hyper = h; }

  bool getSpaceOnly() const { return _spaceOnly; }
  virtual void add(std::shared_ptr<floatHyper> vec);
  virtual void scale(const double val);
  virtual void scaleAdd(const double sc1, std::shared_ptr<floatHyper> vec2,
                        const double sc2);
  virtual void random();
  virtual double dot(std::shared_ptr<floatHyper> vec2) const;
  void createMask(const float zero, const float err);
  void setData(float *ptr) {
    _vals = ptr;
    setNotSpace();
  }
  void calcCheckSum();
  void setCheckSum(const uint64_t x) { _checkSum = x; }
  bool isDifferent(std::shared_ptr<floatHyper> vec2) {
    if (vec2->getCheckSum() != getCheckSum()) return true;
    return false;
  }
  void setNorm(std::string nrm) {
    if (nrm == std::string("L2")){
      this->norm = nrm;
return;
} 
    else if (nrm == std::string("L1")){
      this->norm = nrm;
return;
}
    assert(1 == 2);
  }
  std::string getNorm() const { 
     if(this->norm==std::string("")) return "L2";
      return this->norm; 

}
  double calcNorm() const {
    if (this->norm == std::string("L2"))
      return this->L2Obj();
    else {
      return this->L1Obj();
    }
  }
  double L2Obj() const;
  double L1Obj() const;
  float *getVals() { return _vals; }
  const float *getCVals() const { return _vals; }
  virtual void softClip(const float val);
  virtual float absMax() const;
  float min() const;
  virtual void infoStream(const int lev, std::stringstream &x);
  std::shared_ptr<SEP::hypercube> getHyper() const { return _hyper; }
  virtual bool checkSame(const std::shared_ptr<giee::floatHyper> vec2) const;
  uint64_t getCheckSum() { return _checkSum; }

 private:
  std::shared_ptr<SEP::hypercube> _hyper;
  float *_vals;
  uint64_t _checkSum;
  std::string norm;
};

}  // namespace giee
