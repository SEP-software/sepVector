#include <complexHyper.h>
#include <hypercube.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>
#include <tbb/tbb.h>
#include <iostream>
#include <random>
using namespace SEP;

void complexHyper::add(const std::shared_ptr<complexHyper> vec2) {
  assert(checkSame(vec2));
  std::shared_ptr<complexHyper> vec2H =
      std::dynamic_pointer_cast<complexHyper>(vec2);

  for (long long i = 0; i < getHyper()->getN123(); i++)

    tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                      [&](const tbb::blocked_range<long long> &r) {
                        for (long long i = r.begin(); i != r.end(); ++i)
                          _vals[i] += vec2H->_vals[i];
                      });
  calcCheckSum();
}
void complexHyper::mult(const std::shared_ptr<complexHyper> vec2) {
  assert(checkSame(vec2));
  std::shared_ptr<complexHyper> vec2H =
      std::dynamic_pointer_cast<complexHyper>(vec2);
  for (long long i = 0; i < getHyper()->getN123(); i++)

    tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                      [&](const tbb::blocked_range<long long> &r) {
                        for (long long i = r.begin(); i != r.end(); ++i)
                          _vals[i] *= vec2H->_vals[i];
                      });
  calcCheckSum();
}
/*
void complexHyper::scaleAdd(std::shared_ptr<complexHyper> vec2,
                            const std::complex<double> sc1,
                            const std::complex<double> sc2) {
  assert(checkSame(vec2));
  std::shared_ptr<complexHyper> vec2H =
      std::dynamic_pointer_cast<complexHyper>(vec2);

  for (long long i = 0; i < getHyper()->getN123(); i++)
    _vals[i] = _vals[i] * sc1 + sc2 * vec2H->_vals[i];
  calcCheckSum();
}

void complexHyper::scale(std::complex<double> sc) {
  assert(!spaceOnly());
  for (long long i = 0; i < getHyper()->getN123(); i++) _vals[i] = _vals[i] *
sc; calcCheckSum();
}
*/

void complexHyper::random() {
  assert(!spaceOnly());
  for (long long ii = 0; ii < getHyper()->getN123(); ii++)
    _vals[ii] = {(float)((double)rand() / (RAND_MAX)-.5),
                 (float)((double)rand() / (RAND_MAX)-.5)};
  calcCheckSum();
}

void complexHyper::zero() {
  for (long long i = 0; i < getHyper()->getN123(); i++) _vals[i] = 0;
  calcCheckSum();
}

void complexHyper::infoStream(const int lev, std::stringstream &x) {
  getHyper()->infoStream(x);
  if (spaceOnly())
    x << "Only space\n";
  else {
    x << "Allocated\n";
    long long npts = std::min((const long long)lev, getHyper()->getN123());
    //  for (long long i = 0; i < npts; i++)
    //  x << std::to_string(i) << std::string(" ") << std::to_string(_vals[i])
    //  << std::endl;
  }
}

void complexHyper::calcCheckSum() {
  uint32_t sum1 = 0, sum2 = 0;
  uint32_t *data = (uint32_t *)_vals;
  uint32_t mx = 4294967295;
  for (long long i = 0; i < getHyper()->getN123(); i++) {
    sum1 = (sum1 + data[i]) % mx;
    sum2 = (sum2 + sum1) % mx;
  }
  setCheckSum(sum2 * 2 ^ 32 + sum1);
}

bool complexHyper::checkSame(const std::shared_ptr<complexHyper> vec2) const {
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
