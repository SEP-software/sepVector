#include <byteHyper.h>
#include <hypercube.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>
#include <tbb/tbb.h>
#include <iostream>
#include <random>
using namespace SEP;

void byteHyper::random() {
  if (spaceOnly()) throw(std::string("Vectors not allocated"));

  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        _vals[i] = ((double)rand() / (RAND_MAX)) * 256;
                    });
  calcCheckSum();
}

void byteHyper::set(const unsigned char val) {
  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        _vals[i] = val;
                    });
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
  int val = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()), -1e31,
      [&](const tbb::blocked_range<size_t> &r, int v) {
        for (size_t i = r.begin(); i != r.end(); ++i) {
          v = std::max(v, abs((int)_vals[i]));
        }
        return v;
      },
      [](int a, int b) {
        if (a > b) return a;
        return b;
      });
  return val;
}
unsigned char byteHyper::cent(const long long iv, const int js) const {
  int q;
  int n = getHyper()->getN123() / js;
  unsigned char *x = new unsigned char[n];
  const unsigned char *in = getCVals();
  if (js < 1)
    throw SEPException(std::string("j must be positive ") + std::to_string(js));
  for (auto i = 0; i < n; i++) {
    x[i] = in[i * js];
  }
  register unsigned char *i, *j, ak;
  unsigned char *low, *hi, buf, *k;
  for (low = x, hi = x + n - 1, k = x + q; low < hi;) {
    ak = *k;
    i = low;
    j = hi;
    do {
      while (*i < ak) i++;
      while (*j > ak) j--;
      if (i <= j) {
        buf = *i;
        *i++ = *j;
        *j-- = buf;
      }
    } while (i <= j);
    if (j < k) low = i;
    if (k < i) hi = j;
  }
  unsigned char vv = (*k);
  delete[] x;
  return vv;
}
void byteHyper::clip(const unsigned char bclip, const unsigned char eclip) {
  if (spaceOnly()) throw(std::string("Vectors not allocated"));
  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        _vals[i] = std::max(eclip, std::min(bclip, _vals[i]));
                    });
}
int byteHyper::max() const {
  int val = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()), -1e31,
      [&](const tbb::blocked_range<size_t> &r, int v) {
        for (size_t i = r.begin(); i != r.end(); ++i) {
          v = std::max(v, (int)_vals[i]);
        }
        return v;
      },
      [](int a, int b) {
        if (a > b) return a;
        return b;
      });
  return val;
}
int byteHyper::min() const {
  int val = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()), 1e31,
      [&](const tbb::blocked_range<size_t> &r, int v) {
        for (size_t i = r.begin(); i != r.end(); ++i) {
          v = std::min(v, (int)_vals[i]);
        }
        return v;
      },
      [](int a, int b) {
        if (a > b) return b;
        return a;
      });
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
