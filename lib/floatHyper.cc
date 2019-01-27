#include <floatHyper.h>
#include <hypercube.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>
#include <tbb/tbb.h>
#include <iostream>
#include <random>
using namespace SEP;

void floatHyper::add(const std::shared_ptr<floatHyper> vec2) {
  if (!checkSame(vec2)) throw(std::string("Vectors not of the same space"));
  std::shared_ptr<floatHyper> vec2H =
      std::dynamic_pointer_cast<floatHyper>(vec2);

  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        _vals[i] += vec2H->_vals[i];
                    });
  calcCheckSum();
}
void floatHyper::mult(const std::shared_ptr<floatHyper> vec2) {
  if (!checkSame(vec2)) throw(std::string("Vectors not of the same space"));
  std::shared_ptr<floatHyper> vec2H =
      std::dynamic_pointer_cast<floatHyper>(vec2);

  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        _vals[i] *= vec2H->_vals[i];
                    });
  calcCheckSum();
}
void floatHyper::scaleAdd(std::shared_ptr<floatHyper> vec2, const double sc1,
                          const double sc2) {
  if (!checkSame(vec2)) throw(std::string("Vectors not of the same space"));
  std::shared_ptr<floatHyper> vec2H =
      std::dynamic_pointer_cast<floatHyper>(vec2);

  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        _vals[i] = _vals[i] * sc1 + sc2 * vec2H->_vals[i];
                    });
  calcCheckSum();
}
float floatHyper::cent(const long long iv, const int js) const {
  long long n = getHyper()->getN123() / js;
  float *x = new float[n];
  // float *x = (float *)malloc(sizeof(float) * n);
  const float *in = getCVals();
  if (js < 1)
    throw SEPException(std::string("j must be positive ") + std::to_string(js));
  for (auto i = 0; i < n; i++) {
    x[i] = in[i * js];
  }
  double w = (double)(iv) / (double)n;
  long long q =
      std::max((long long)0, std::min((long long)(n - 1), (long long)(w * n)));
  // std::cerr << "looking for " << q << " " << n << " " <<
  // getHyper()->getN123()
  //        << std::endl;

  register float *i, *j, ak;
  float *low, *hi, buf, *k;
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
  float m = *k;
  delete[] x;
  // free(x);
  return m;
}
void floatHyper::clip(const float bclip, const float eclip) {
  if (spaceOnly()) throw(std::string("Vectors not allocated"));
  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        _vals[i] = std::min(eclip, std::max(bclip, _vals[i]));
                    });
  calcCheckSum();
}
void floatHyper::signum() {
  if (spaceOnly()) throw(std::string("Vectors not allocated"));

  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i) {
                        if (_vals[i] > 1e-20)
                          _vals[i] = 1;
                        else if (_vals[i] < -1e-20)
                          _vals[i] = -1;
                        else
                          _vals[i] = 0;
                      }
                    });

  calcCheckSum();
}
void floatHyper::scale(double sc) {
  if (spaceOnly()) throw(std::string("Vectors not allocated"));
  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        _vals[i] = _vals[i] * sc;
                    });
  calcCheckSum();
}
void floatHyper::random() {
  if (spaceOnly()) throw(std::string("Vectors not allocated"));
  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        _vals[i] = ((double)rand() / (RAND_MAX)) - .5;
                    });
  calcCheckSum();
}

double floatHyper::norm(const int n) const {
  double dt = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()), 0.,
      [&](const tbb::blocked_range<size_t> &r, float v) {
        if (n == 1) {
          for (size_t i = r.begin(); i != r.end(); ++i) {
            v += (double)fabsf(_vals[i]);
          }
        } else {
          for (size_t i = r.begin(); i != r.end(); ++i) {
            v += (double)_vals[i] * (double)_vals[i];
          }
        }
        return v;
      },
      [](double a, double b) { return a + b; });
  if (n == 2) return sqrtf(dt);

  return dt;
}
void floatHyper::set(const float val) {
  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        _vals[i] = val;
                    });
  calcCheckSum();
}
double floatHyper::dot(const std::shared_ptr<floatHyper> vec2) const {
  if (!checkSame(vec2)) throw(std::string("Vectors not of the same space"));
  std::shared_ptr<floatHyper> vec2H =
      std::dynamic_pointer_cast<floatHyper>(vec2);

  double dot = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()), 0.,
      [&](const tbb::blocked_range<size_t> &r, float v) {
        for (size_t i = r.begin(); i != r.end(); ++i) {
          v += (double)_vals[i] * (double)vec2H->_vals[i];
        }
        return v;
      },
      [](double a, double b) { return a + b; });

  return dot;
}
void floatHyper::createMask(const float zero, const float err) {
  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i) {
                        if (fabs(_vals[i] - zero) > err)

                          _vals[i] = 0.;
                        else
                          _vals[i] = 1;
                      }
                    });
  calcCheckSum();
}

void floatHyper::infoStream(const int lev, std::stringstream &x) {
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
void floatHyper::softClip(const float scale) {
  float sc2 = scale * scale;
  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        _vals[i] = scale * _vals[i] /
                                   sqrtf(1. + sc2 * _vals[i] * _vals[i]);
                    });
  calcCheckSum();
}

double floatHyper::absMax() const {
  float val = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()), -1e31,
      [&](const tbb::blocked_range<size_t> &r, float v) {
        for (size_t i = r.begin(); i != r.end(); ++i) {
          v = std::max(v, fabsf(_vals[i]));
        }
        return v;
      },
      [](float a, float b) {
        if (a > b) return a;
        return b;
      });
  return (double)val;
}
double floatHyper::max() const {
  float val = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()), -1e31,
      [&](const tbb::blocked_range<size_t> &r, float v) {
        for (size_t i = r.begin(); i != r.end(); ++i) {
          v = std::max(v, _vals[i]);
        }
        return v;
      },
      [](float a, float b) {
        if (a > b) return a;
        return b;
      });
  return (double)val;
}
double floatHyper::min() const {
  float val = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()), 1e31,
      [&](const tbb::blocked_range<size_t> &r, float v) {
        for (size_t i = r.begin(); i != r.end(); ++i) {
          v = std::min(v, _vals[i]);
        }
        return v;
      },
      [](float a, float b) {
        if (a > b) return b;
        return a;
      });
  return (double)val;
}
void floatHyper::calcCheckSum() {
  uint32_t sum1 = 0, sum2 = 0;
  uint32_t *data = (uint32_t *)_vals;
  uint32_t mx = 4294967295;
  for (long long i = 0; i < getHyper()->getN123(); i++) {
    sum1 = (sum1 + data[i]) % mx;
    sum2 = (sum2 + sum1) % mx;
  }
  setCheckSum(sum2 * 2 ^ 32 + sum1);
}

bool floatHyper::checkSame(const std::shared_ptr<floatHyper> vec2) const {
  if (!vec2) {
    raise SEPException("Vec2 is not allocated") return false;
  }
  bool b;
  try {
    b = getHyper().checkSame(vec2->getHyper());
  } catch (SEPException &e) {
    throw SEPException(e.what);
  }

  return b;
  return true;
}
