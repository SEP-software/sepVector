#ifndef RECTFILTER_H
#define RECTFILTER_H 1
#include "float1DReg.h"
#include "float2DReg.h"
#include "float3DReg.h"
#include "float4DReg.h"
#include "float5DReg.h"
namespace SEP {

class rectFilter1D : public SEP::float1DReg {
 public:
  rectFilter1D(const std::vector<int> &box, const std::vector<int> &beg,
               bool pef = false);
  std::shared_ptr<rectFilter1D> clone() const;
  std::shared_ptr<rectFilter1D> cloneSpace() const;
  void cleanFilter() {
    zeroNonCoefs();
    (*_mat)[_f[0]] = 1;
  }
  void zeroNonCoefs();
  bool isPef() { return _pef; }
  void setBasics(const std::vector<int> &box, const std::vector<int> &f,
                 const bool pef) {
    _n = box;
    _f = f;
    for (auto i = 0; i < box.size(); i++) {
      _e.push_back(_n[i] - _f[i] - 1);
    }
    _pef = pef;
  }

 public:
  std::vector<int> _n, _f, _e;
  bool _pef;
};

class rectFilter2D : public SEP::float2DReg {
 public:
  rectFilter2D(const std::vector<int> &box, const std::vector<int> &beg,
               bool pef = false);
  std::shared_ptr<rectFilter2D> clone() const;
  std::shared_ptr<rectFilter2D> cloneSpace() const;
  void zeroNonCoefs();
  void cleanFilter() {
    zeroNonCoefs();
    (*_mat)[_f[1]][_f[0]] = 1;
  }
  bool isPef() { return _pef; }
  void setBasics(const std::vector<int> &box, const std::vector<int> &f,
                 const bool pef) {
    _n = box;
    _f = f;
    for (auto i = 0; i < box.size(); i++) {
      _e.push_back(_n[i] - _f[i] - 1);
    }
    _pef = pef;
  }

 public:
  std::vector<int> _n, _f, _e;
  bool _pef;
};

class rectFilter3D : public SEP::float3DReg {
 public:
  rectFilter3D(const std::vector<int> &box, const std::vector<int> &beg,
               bool pef = false);
  std::shared_ptr<rectFilter3D> clone() const;
  std::shared_ptr<rectFilter3D> cloneSpace() const;
  void zeroNonCoefs();
  void cleanFilter() {
    zeroNonCoefs();
    (*_mat)[_f[2]][_f[1]][_f[0]] = 1;
  }
  bool isPef() { return _pef; }
  void setBasics(const std::vector<int> &box, const std::vector<int> &f,
                 const bool pef) {
    _n = box;
    _f = f;
    for (auto i = 0; i < box.size(); i++) {
      _e.push_back(_n[i] - _f[i] - 1);
    }
    _pef = pef;
  }

 public:
  std::vector<int> _n, _f, _e;
  bool _pef;
};

class rectFilter4D : public SEP::float4DReg {
 public:
  rectFilter4D(const std::vector<int> &box, const std::vector<int> &f,
               bool pef = false);
  std::shared_ptr<rectFilter4D> clone() const;
  std::shared_ptr<rectFilter4D> cloneSpace() const;
  void zeroNonCoefs();
  void cleanFilter() {
    zeroNonCoefs();
    (*_mat)[_f[3]][_f[2]][_f[1]][_f[0]] = 1;
  }
  bool isPef() { return _pef; }
  void setBasics(const std::vector<int> &box, const std::vector<int> &f,
                 const bool pef) {
    _n = box;
    _f = f;
    for (auto i = 0; i < box.size(); i++) {
      _e.push_back(_n[i] - _f[i] - 1);
    }
    _pef = pef;
  }

 public:
  std::vector<int> _n, _f, _e;
  bool _pef;
};

}  // namespace SEP
#endif