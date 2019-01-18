#pragma once

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
    assert(fw >= 0);
    assert(jw > 0);
    assert(nw > 0);
    assert(fw + jw * (nw - 1) < n);
  }
  void *getVoidPtr() { return _storage; }
  size_t getEsize() { return _esize; }
  virtual ~regSpace() = default;

 private:
  std::shared_ptr<SEP::hypercube> _hyper;
  size_t _esize;
  void *_storage;
};
}  // namespace SEP