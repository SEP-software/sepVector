#pragma once
#include <cassert>
#include <cstdint>
#include <memory>
#include <sstream>
namespace SEP {
class Vector {
 public:
  Vector() : _spaceOnly(false), _vecType(std::string("base")) { ; }
  virtual void add(const std::shared_ptr<Vector> vec) { assert(1 == 2); }
  virtual void scale(const double val) { assert(1 == 2); }
  virtual void scaleAdd(const double sc1, const std::shared_ptr<Vector>,
                        const double sc2) {
    assert(1 == 2);
  }
  virtual void random() { assert(1 == 2); }
  virtual void softClip(float val) { assert(1 == 2); }
  virtual float absMax() const { assert(1 == 2); }
  virtual double dot(const std::shared_ptr<Vector> vec2) const {
    assert(1 == 2);
  }
  virtual bool checkSame(const std::shared_ptr<Vector> vec2,
                         const bool checkAlloc = false) const {
    assert(1 == 2);
  }
  virtual void cleanMemory() { assert(1 == 2); }
  virtual void setSpace() { _spaceOnly = true; }
  virtual void infoStream(const int lev, std::stringstream &x) {
    assert(1 == 2);
  }
  std::string info(const std::string &nm, const int lev);
  virtual void calcCheckSum() { assert(1 == 2); }
  void setCheckSum(const uint64_t x) { _checkSum = x; }
  uint64_t getCheckSum() { return _checkSum; }
  inline bool spaceOnly() const { return _spaceOnly; }
  void setNotSpace() { _spaceOnly = false; }
  std::string _vecType;

 protected:
  bool _spaceOnly;
  uint64_t _checkSum;
};

}  // namespace SEP
