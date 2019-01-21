#pragma once
#include "SEPException.h"
#include "hypercube.h"

namespace SEP {

class regSpace {
 public:
  regSpace() { ; }
  std::shared_ptr<SEP::hypercube> getHyper() const { return _hyper; }
  void setHyper(std::shared_ptr<SEP::hypercube> h) { _hyper = h->clone(); }
  void setMemPtr(void *ptr, size_t esize) {
    _storage = ptr;
    _esize = esize;
  }
  void checkWindow(const int n, const int nw, const int fw,
                   const int jw) const {
    if (fw < 0)
      throw(SEPException(std::string("fw must be 0 or greater=") +
                         std::to_string(fw)));
    if (jw < 1)
      throw(SEPException(std::string("jw must be 1 or greater=") +
                         std::to_string(jw)));
    if (nw < 1)
      throw(SEPException(std::string("nw must be 1 or greater=") +
                         std::to_string(nw)));
    if (fw + jw * (nw - 1) < n)
      throw(SEPException(std::string("fw+jw*(nw-1) <n ") + std::to_string(fw) +
                         std::string("=fw jw=") + std::to_string(jw) +
                         std::string(" nw=") + std::to_string(nw) +
                         std::string(" n=") + std::to_string(n)));
  }
  void *getVoidPtr() { return _storage; }
  size_t getEsize() { return _esize; }
  virtual ~regSpace() = default;

 protected:
  inline void calcTraverse(const std::vector<int> &nd, const int iax1,
                           const bool rev1, int &f1, int &j1, const int iax2,
                           const bool rev2, int &f2, int &j2) {
    if (iax2 > iax1) {
      if (!rev1) {
        f1 = 0;
        j1 = 1;
      } else {
        f1 = nd[iax1] - 1;
        j1 = -1;
      }
      if (!rev2) {
        f2 = 0;
        j2 = nd[iax1];
      } else {
        f2 = (nd[iax2] - 1) * nd[iax1];
        j2 = -nd[iax1];
      }
    } else {
      if (!rev2) {
        f2 = 0;
        j2 = 1;
      } else {
        f2 = nd[iax2] - 1;
        j2 = -1;
      }
      if (!rev1) {
        f1 = 0;
        j1 = nd[iax2];
      } else {
        f1 = (nd[iax1] - 1) * nd[iax2];
        j1 = -nd[iax2];
      }
    }
  }

 private:
  std::shared_ptr<SEP::hypercube> _hyper;
  size_t _esize;
  void *_storage;
};
}  // namespace SEP