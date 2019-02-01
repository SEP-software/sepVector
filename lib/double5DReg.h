#ifndef double5d_reg_h
#define double5d_reg_h 1
#include "boost/multi_array.hpp"

#include <doubleHyper.h>

typedef boost::multi_array<double, 5> double5D;
namespace SEP {
class double5DReg : public doubleHyper {
 public:
  double5DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  double5DReg(const int n1, const int n2, const int n3, const int n4,
              const int n5) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    a.push_back(SEP::axis(n3));
    a.push_back(SEP::axis(n4));
    a.push_back(SEP::axis(n5));

    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  double5DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
              const SEP::axis &a4, const SEP::axis &a5) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);
    a.push_back(a4);
    a.push_back(a5);

    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  double5DReg(std::shared_ptr<SEP::hypercube> hyper, const double5D &vals) {
    initData(hyper, vals);
  }
  double5DReg(const int n1, const int n2, const int n3, const int n4,
              const int n5, double5D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    a.push_back(SEP::axis(n3));
    a.push_back(SEP::axis(n4));
    a.push_back(SEP::axis(n5));

    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  double5DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
              const SEP::axis &a4, const SEP::axis &a5, double5D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);
    a.push_back(a4);
    a.push_back(a5);

    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  void allocate() {
    std::vector<int> ns = getHyper()->getNs();
    _mat.reset(new double5D(boost::extents[ns[4]][ns[3]][ns[2]][ns[1]][ns[0]]));

    setData(_mat->data());
    ;
  }
  std::shared_ptr<double5DReg> clone() const;
  std::shared_ptr<double5DReg> cloneSpace() const;

  std::shared_ptr<double5DReg> window(const std::vector<int> &nw,
                                      const std::vector<int> &fw,
                                      const std::vector<int> &jw) const;
  virtual void cleanMemory() {
    _mat = 0;
    setSpace();
  }
  std::shared_ptr<double5D> _mat;

 private:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  void initData(std::shared_ptr<SEP::hypercube> hyp, const double5D &vals);
};
}  // namespace SEP
#endif
