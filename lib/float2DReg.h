#ifndef float2d_reg_h
#define float2d_reg_h 1
#include <float3DReg.h>
#include <float4DReg.h>
#include <float5DReg.h>
#include <float6DReg.h>
#include <floatHyper.h>

#include "boost/multi_array.hpp"
typedef boost::multi_array<float, 2> float2D;
namespace SEP {
class float2DReg : public floatHyper {
 public:
  float2DReg() { ; }
  float2DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  float2DReg(const int n1, const int n2) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  float2DReg(const SEP::axis &a1, const SEP::axis &a2) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  float2DReg(std::shared_ptr<SEP::hypercube> hyper, const float2D &vals) {
    initData(hyper, vals);
  }
  float2DReg(int n1, int n2, float2D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  float2DReg(SEP::axis &a1, SEP::axis &a2, float2D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  float2DReg(const std::shared_ptr<float6DReg> old, const int iax1,
             const bool rev1, const int iax2, const bool rev2,
             const std::vector<int> &ipos, const std::vector<int> &beg,
             const std::vector<int> &end);
  float2DReg(const std::shared_ptr<float5DReg> old, const int iax1,
             const bool rev1, const int iax2, const bool rev2,
             const std::vector<int> &ipos, const std::vector<int> &beg,
             const std::vector<int> &end);
  float2DReg(const std::shared_ptr<float4DReg> old, const int iax1,
             const bool rev1, const int iax2, const bool rev2,
             const std::vector<int> &ipos, const std::vector<int> &beg,
             const std::vector<int> &end);
  float2DReg(const std::shared_ptr<float3DReg> old, const int iax1,
             const bool rev1, const int iax2, const bool rev2,
             const std::vector<int> &ipos, const std::vector<int> &beg,
             const std::vector<int> &end);
  float2DReg(const std::shared_ptr<float2DReg> old, const int iax1,
             const bool rev1, const int iax2, const bool rev2,
             const std::vector<int> &ipos, const std::vector<int> &beg,
             const std::vector<int> &end);

  void allocate() {
    std::vector<int> ns = getHyper()->getNs();
    _mat.reset(new float2D(boost::extents[ns[1]][ns[0]]));

    setData(_mat->data());
    ;
  }

  std::shared_ptr<float2DReg> window(const std::vector<int> &nw,
                                     const std::vector<int> &fw,
                                     const std::vector<int> &jw) const;
  std::shared_ptr<float2DReg> clone() const;
  std::shared_ptr<float2DReg> cloneSpace() const;
  virtual void cleanMemory() { setSpace(); }
  std::shared_ptr<float2D> _mat;

 protected:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  void initData(std::shared_ptr<SEP::hypercube> hyp, const float2D &vals);
};
}  // namespace SEP
#endif
