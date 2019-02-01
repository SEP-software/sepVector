#ifndef int2d_reg_h
#define int2d_reg_h 1
#include <intHyper.h>
#include "int3DReg.h"
#include "int4DReg.h"
#include "int5DReg.h"
#include "int6DReg.h"

#include "boost/multi_array.hpp"

typedef boost::multi_array<int, 2> int2D;
namespace SEP {
class int2DReg : public intHyper {
 public:
  int2DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  int2DReg(const int n1, const int n2) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  int2DReg(const SEP::axis &a1, const SEP::axis &a2) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  int2DReg(std::shared_ptr<SEP::hypercube> hyper, const int2D &vals) {
    initData(hyper, vals);
  }
  int2DReg(int n1, int n2, int2D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  int2DReg(SEP::axis &a1, SEP::axis &a2, int2D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  int2DReg(const std::shared_ptr<int2DReg> old, const int iax1, const bool rev1,
           const int iax2, const bool rev2, const std::vector<int> &ipos,
           const std::vector<int> &beg, std::vector<int> &end);
  int2DReg(const std::shared_ptr<int3DReg> old, const int iax1, const bool rev1,
           const int iax2, const bool rev2, const std::vector<int> &ipos,
           const std::vector<int> &beg, std::vector<int> &end);
  int2DReg(const std::shared_ptr<int4DReg> old, const int iax1, const bool rev1,
           const int iax2, const bool rev2, const std::vector<int> &ipos,
           const std::vector<int> &beg, std::vector<int> &end);
  int2DReg(const std::shared_ptr<int5DReg> old, const int iax1, const bool rev1,
           const int iax2, const bool rev2, const std::vector<int> &ipos,
           const std::vector<int> &beg, std::vector<int> &end);
  int2DReg(const std::shared_ptr<int6DReg> old, const int iax1, const bool rev1,
           const int iax2, const bool rev2, const std::vector<int> &ipos,
           const std::vector<int> &beg, std::vector<int> &end);
  void allocate() {
    std::vector<int> ns = getHyper()->getNs();
    _mat.reset(new int2D(boost::extents[ns[1]][ns[0]]));

    setData(_mat->data());
    ;
  }
  std::shared_ptr<int2DReg> clone() const;
  std::shared_ptr<int2DReg> cloneSpace() const;
  std::shared_ptr<int2DReg> window(const std::vector<int> &nw,
                                   const std::vector<int> &fw,
                                   const std::vector<int> &jw) const;
  virtual void cleanMemory() { setSpace(); }
  std::shared_ptr<int2D> _mat;

 private:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  void initData(std::shared_ptr<SEP::hypercube> hyp, const int2D &vals);
};
}  // namespace SEP
#endif
