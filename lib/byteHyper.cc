#include <byteHyper.h>
#include <hypercube.h>
#include <iostream>
#include <random>
using namespace SEP;

void byteHyper::random() {
  assert(!spaceOnly());
  for (long long i = 0; i < getHyper()->getN123(); i++)
    _vals[i] = ((double)rand() / (RAND_MAX)) * 256;
  calcCheckSum();
}

void byteHyper::zero() {
  for (long long i = 0; i < getHyper()->getN123(); i++) _vals[i] = 0;
  calcCheckSum();
}

void byteHyper::infoStream(const int lev, std::stringstream &x) {
  getHyper()->infoStream(x);
  if (spaceOnly())
    x << "Only space\n";
  else {
    x << "Allocated\n";
    long long npts = std::min((const long long)lev, getHyper()->getN123());
    for (long long i = 0; i < npts; i++)
      x << std::to_string(i) << std::string(" ") << std::to_string(_vals[i])
        << std::endl;
  }
}

int byteHyper::absMax() const {
  int val = abs(_vals[0]);
  for (int i = 1; i < getHyper()->getN123(); i++)
    val = std::max(val, abs((int)_vals[i]));
  return val;
}
int byteHyper::max() const {
  int val = abs(_vals[0]);
  for (int i = 1; i < getHyper()->getN123(); i++)
    val = std::max(val, (int)_vals[i]);
  return val;
}
int byteHyper::min() const {
  int val = abs(_vals[0]);
  for (int i = 1; i < getHyper()->getN123(); i++)
    val = std::min(val, (int)_vals[i]);
  return val;
}
void byteHyper::calcCheckSum() {
  uint32_t sum1 = 0, sum2 = 0;
  uint32_t *data = (uint32_t *)_vals;
  uint32_t mx = 4294967295;
  for (long long i = 0; i < getHyper()->getN123() / 4; i++) {
    sum1 = (sum1 + data[i]) % mx;
    sum2 = (sum2 + sum1) % mx;
  }
  setCheckSum(sum2 * 2 ^ 32 + sum1);
}

bool byteHyper::checkSame(const std::shared_ptr<byteHyper> vec2) const {
  if (!vec2) {
    std::cerr << "Not allocated vec2" << std::endl;
    return false;
  }
  //  if (getHyper() == vec2->getHyper()) return true;
  return true;
  std::cerr << getHyper()->getAxis(1).n << " " << vec2->getHyper()->getAxis(1).n
            << std::endl;
  std::cerr << "Not from the same Hypercube" << std::endl;

  return false;
}
