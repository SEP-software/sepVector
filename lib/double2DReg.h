#ifndef double2d_reg_h
#define double2d_reg_h 1
#include <doubleHyper.h>
#include "double3DReg.h"
#include "double4DReg.h"
#include "double5DReg.h"
#include "double6DReg.h"

#include "boost/multi_array.hpp"
typedef boost::multi_array<double, 2> double2D;
namespace SEP {
class double2DReg : public doubleHyper {
 public:
  double2DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  double2DReg(const int n1, const int n2) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  double2DReg(const SEP::axis &a1, const SEP::axis &a2) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  double2DReg(std::shared_ptr<SEP::hypercube> hyper, const double2D &vals) {
    initData(hyper, vals);
  }
  double2DReg(int n1, int n2, double2D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  double2DReg(SEP::axis &a1, SEP::axis &a2, double2D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  double2DReg(const std::shared_ptr<double2DReg> old, const int iax1,
              const bool rev1, const int iax2, const bool rev2,
              const std::vector<int> &ipos, const std::vector<int> &beg,
              const std::vector<int> &end);
  double2DReg(const std::shared_ptr<double3DReg> old, const int iax1,
              const bool rev1, const int iax2, const bool rev2,
              const std::vector<int> &ipos, const std::vector<int> &beg,
              const std::vector<int> &end);
  double2DReg(const std::shared_ptr<double4DReg> old, const int iax1,
              const bool rev1, const int iax2, const bool rev2,
              const std::vector<int> &ipos, const std::vector<int> &beg,
              const std::vector<int> &end);
  double2DReg(const std::shared_ptr<double5DReg> old, const int iax1,
              const bool rev1, const int iax2, const bool rev2,
              const std::vector<int> &ipos, const std::vector<int> &beg,
              const std::vector<int> &end);
  double2DReg(const std::shared_ptr<double6DReg> old, const int iax1,
              const bool rev1, const int iax2, const bool rev2,
              const std::vector<int> &ipos, const std::vector<int> &beg,
              const std::vector<int> &end);
  void allocate() {
    std::vector<int> ns = getHyper()->getNs();
    _mat.reset(new double2D(boost::extents[ns[1]][ns[0]]));

    setData(_mat->data());
    ;
  }
  std::shared_ptr<double2DReg> clone() const;
  std::shared_ptr<double2DReg> cloneSpace() const;

  std::shared_ptr<double2DReg> window(const std::vector<int> &nw,
                                      const std::vector<int> &fw,
                                      const std::vector<int> &jw) const;
  virtual void cleanMemory() { setSpace(); }
  std::shared_ptr<double2D> _mat;

 private:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  void initData(std::shared_ptr<SEP::hypercube> hyp, const double2D &vals);
};
}  // namespace SEP
#endif
