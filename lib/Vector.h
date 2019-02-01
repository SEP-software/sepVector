#ifndef vector_h
#define vector_h 1
#include <cstdint>
#include <memory>
#include <sstream>
#include "SEPException.h"
namespace SEP {

class Vector {
 public:
  Vector() : _spaceOnly(false), _vecType(std::string("base")) { ; }
  virtual void add(const std::shared_ptr<Vector> vec) {
    throw SEPException(std::string("Must override add"));
  }
  virtual void scale(const double val) {
    throw SEPException(std::string("Must override scale"));
  }
  virtual void scaleAdd(const double sc1, const std::shared_ptr<Vector>,
                        const double sc2) {
    throw SEPException(std::string("Must override scaleAdd"));
  }
  virtual void random() {
    throw SEPException(std::string("Must override random"));
  }

  virtual void softClip(float val) {
    throw SEPException(std::string("Must override softclip"));
  }
  virtual double absMax() const {
    throw SEPException(std::string("Must override absMax"));
  }
  virtual double dot(const std::shared_ptr<Vector> vec2) const {
    throw SEPException(std::string("Must override dot"));
  }
  virtual bool checkSame(const std::shared_ptr<Vector> vec2,
                         const bool checkAlloc = false) const {
    throw SEPException(std::string("Must override checkSame"));
  }
  virtual void cleanMemory() {
    throw SEPException(std::string("Must override cleanMemory"));
  }

  virtual void setSpace() { _spaceOnly = true; }
  virtual void infoStream(const int lev, std::stringstream &x) {
    throw SEPException(std::string("Must override infoStream"));
  }

  std::string info(const std::string &nm, const int lev);
  virtual void calcCheckSum() {
    throw SEPException(std::string("Must override calcCheckSum"));
  }

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
#endif
