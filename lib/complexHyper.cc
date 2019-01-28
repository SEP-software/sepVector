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
  if (!checkSame(vec2)) throw(std::string("Vectors not of the same space"));

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
  if (!checkSame(vec2)) throw(std::string("Vectors not of the same space"));
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

void complexHyper::random() {
  if (spaceOnly()) throw(std::string("Vectors not allocated"));
  for (long long ii = 0; ii < getHyper()->getN123(); ii++)
    _vals[ii] = {(float)((double)rand() / (RAND_MAX)-.5),
                 (float)((double)rand() / (RAND_MAX)-.5)};
  calcCheckSum();
}

void complexHyper::set(const std::complex<float> val) {
  for (long long i = 0; i < getHyper()->getN123(); i++) _vals[i] = val;
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
    throw SEPException("Vec2 is not allocated");
    return false;
  }
  bool b;
  try {
    b = getHyper()->checkSame(vec2->getHyper());
  } catch (SEPException &e) {
    throw SEPException(e.getMessage());
  }

  return b;
  return true;
}
