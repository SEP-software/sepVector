#ifndef byte5d_reg_h
#define byte5d_reg_h 1
#include "boost/multi_array.hpp"

#include <byteHyper.h>

typedef boost::multi_array<unsigned char, 5> byte5D;
namespace SEP {
class byte5DReg : public byteHyper {
 public:
  byte5DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  byte5DReg(const int n1, const int n2, const int n3, const int n4,
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
  byte5DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
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
  byte5DReg(std::shared_ptr<SEP::hypercube> hyper, const byte5D &vals) {
    initData(hyper, vals);
  }
  byte5DReg(const int n1, const int n2, const int n3, const int n4,
            const int n5, byte5D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    a.push_back(SEP::axis(n3));
    a.push_back(SEP::axis(n4));
    a.push_back(SEP::axis(n5));

    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  byte5DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
            const SEP::axis &a4, const SEP::axis &a5, byte5D &vals) {
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
    _mat.reset(new byte5D(boost::extents[ns[4]][ns[3]][ns[2]][ns[1]][ns[0]]));

    setData(_mat->data());
    ;
  }

  std::shared_ptr<byte5DReg> window(const std::vector<int> &nw,
                                    const std::vector<int> &fw,
                                    const std::vector<int> &jw) const;
  std::shared_ptr<byte5DReg> clone() const;
  std::shared_ptr<byte5DReg> cloneSpace() const;
  virtual void cleanMemory() {
    _mat = 0;
    setSpace();
  }
  std::shared_ptr<byte5D> _mat;

 private:
  void initNoData(std::shared_ptr<SEP::hypercube> hyp);
  void initData(std::shared_ptr<SEP::hypercube> hyp, const byte5D &vals);
};
}  // namespace SEP
#endif
