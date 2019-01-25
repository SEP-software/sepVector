#pragma once
#include "float1DReg.h"
#include "float2DReg.h"
#include "float3DReg.h"
#include "float4DReg.h"
#include "float5DReg.h"
namespace SEP {
class rectFilter {
 public:
  rectFilter() { ; }
  void setBasics(const std::vector<int> &box, const std::vector<int> &f) {
    _n = box;
    _f = f;
    for (auto i = 0; i < box.size(); i++) {
      _e.push_back(_n[i] - _f[i] - 1);
    }
  }
  virtual void zeroNeg() = 0;
  virtual void initializePEF() = 0;

 public:
  std::vector<int> _n, _f, _e;
};

class rectFilter1D : public rectFilter, public SEP::float1DReg {
 public:
  rectFilter1D(const std::vector<int> &box, const std::vector<int> &beg);
  std::shared_ptr<rectFilter1D> clone();
  std::shared_ptr<rectFilter1D> cloneSpace();
  virtual void zeroNeg() override;
  virtual void initializePEF() override;
};

class rectFilter2D : public rectFilter, public SEP::float2DReg {
 public:
  rectFilter2D(const std::vector<int> &box, const std::vector<int> &beg);
  std::shared_ptr<rectFilter2D> clone();
  std::shared_ptr<rectFilter2D> cloneSpace();
  virtual void zeroNeg() override;
  virtual void initializePEF() override;
};

class rectFilter3D : public rectFilter, public SEP::float3DReg {
 public:
  rectFilter3D(const std::vector<int> &box, const std::vector<int> &beg);
  std::shared_ptr<rectFilter3D> clone();
  std::shared_ptr<rectFilter3D> cloneSpace();
  virtual void zeroNeg() override;
  virtual void initializePEF() override;
};

class rectFilter4D : public rectFilter, public SEP::float4DReg {
 public:
  rectFilter4D(const std::vector<int> &box, const std::vector<int> &f);
  std::shared_ptr<rectFilter4D> clone();
  std::shared_ptr<rectFilter4D> cloneSpace();
  virtual void zeroNeg() override;
  virtual void initializePEF() override;
};

}  // namespace giee
