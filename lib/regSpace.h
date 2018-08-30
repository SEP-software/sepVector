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
  void *getVoidPtr() { return _storage; }
  size_t getEsize() { return _esize; }
  virtual ~regSpace() = default;

 private:
  std::shared_ptr<SEP::hypercube> _hyper;
  size_t _esize;
  void *_storage;
};
}  // namespace SEP