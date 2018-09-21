#include <doubleHyper.h>
#include <hypercube.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>
#include <tbb/tbb.h>
#include <iostream>
#include <random>
using namespace SEP;

void doubleHyper::add(const std::shared_ptr<doubleHyper> vec2) {
  assert(checkSame(vec2));
  std::shared_ptr<doubleHyper> vec2H =
      std::dynamic_pointer_cast<doubleHyper>(vec2);
  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        _vals[i] += vec2H->_vals[i];
                    });
  calcCheckSum();
}
void doubleHyper::mult(const std::shared_ptr<doubleHyper> vec2) {
  assert(checkSame(vec2));
  std::shared_ptr<doubleHyper> vec2H =
      std::dynamic_pointer_cast<doubleHyper>(vec2);

  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        _vals[i] *= vec2H->_vals[i];
                    });
  calcCheckSum();
}
void doubleHyper::scaleAdd(std::shared_ptr<doubleHyper> vec2, const double sc1,
                           const double sc2) {
  assert(checkSame(vec2));
  std::shared_ptr<doubleHyper> vec2H =
      std::dynamic_pointer_cast<doubleHyper>(vec2);
  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        _vals[i] = _vals[i] * sc1 + sc2 * vec2H->_vals[i];
                    });
  calcCheckSum();
}
void doubleHyper::signum() {
  assert(!spaceOnly());
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
void doubleHyper::scale(double sc) {
  assert(!spaceOnly());
  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        _vals[i] = _vals[i] * sc;
                    });
  calcCheckSum();
}
void doubleHyper::random() {
  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        _vals[i] = ((double)rand() / (RAND_MAX)) - .5;
                    });
  calcCheckSum();
}

double doubleHyper::norm(const int n) const {
  double dt = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()), 0.,
      [&](const tbb::blocked_range<size_t> &r, double v) {
        if (n == 1) {
          for (size_t i = r.begin(); i != r.end(); ++i) {
            v += (double)fabs(_vals[i]);
          }
        } else {
          for (size_t i = r.begin(); i != r.end(); ++i) {
            v += (double)_vals[i] * (double)_vals[i];
          }
        }
        return v;
      },
      [](double a, double b) { return a + b; });

  return dt;
}
void doubleHyper::zero() {
  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        _vals[i] = 0;
                    });
  calcCheckSum();
}
double doubleHyper::dot(const std::shared_ptr<doubleHyper> vec2) const {
  assert(checkSame(vec2));
  std::shared_ptr<doubleHyper> vec2H =
      std::dynamic_pointer_cast<doubleHyper>(vec2);

  double dot = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()), 0.,
      [&](const tbb::blocked_range<size_t> &r, double v) {
        for (size_t i = r.begin(); i != r.end(); ++i) {
          v += (double)_vals[i] * (double)vec2H->_vals[i];
        }
        return v;
      },
      [](double a, double b) { return a + b; });

  return dot;
}
void doubleHyper::createMask(const float zero, const float err) {
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

void doubleHyper::infoStream(const int lev, std::stringstream &x) {
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
void doubleHyper::softClip(const float scale) {
  float sc2 = scale * scale;
  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        _vals[i] = scale * _vals[i] /
                                   sqrtf(1. + sc2 * _vals[i] * _vals[i]);
                    });
  calcCheckSum();
}

double doubleHyper::absMax() const {
  double val = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()), -1.e31,
      [&](const tbb::blocked_range<size_t> &r, double v) {
        for (size_t i = r.begin(); i != r.end(); ++i) {
          v = std::max(v, fabs(_vals[i]));
        }
        return v;
      },
      [](double a, double b) {
        if (a > b) return a;
        return b;
      });
  return (double)val;
}
double doubleHyper::max() const {
  double val = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()), -1.e31,
      [&](const tbb::blocked_range<size_t> &r, double v) {
        for (size_t i = r.begin(); i != r.end(); ++i) {
          v = std::max(v, _vals[i]);
        }
        return v;
      },
      [](double a, double b) {
        if (a > b) return a;
        return b;
      });
  return (double)val;
}
double doubleHyper::min() const {
  double val = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()), 1.e31,
      [&](const tbb::blocked_range<size_t> &r, double v) {
        for (size_t i = r.begin(); i != r.end(); ++i) {
          v = std::min(v, _vals[i]);
        }
        return v;
      },
      [](double a, double b) {
        if (a > b) return b;
        return a;
      });
  return (double)val;
}
void doubleHyper::calcCheckSum() {
  uint32_t sum1 = 0, sum2 = 0;
  uint32_t *data = (uint32_t *)_vals;
  uint32_t mx = 4294967295;
  for (long long i = 0; i < getHyper()->getN123(); i++) {
    sum1 = (sum1 + data[i]) % mx;
    sum2 = (sum2 + sum1) % mx;
  }
  setCheckSum(sum2 * 2 ^ 32 + sum1);
}

bool doubleHyper::checkSame(const std::shared_ptr<doubleHyper> vec2) const {
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
