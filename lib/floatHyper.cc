#include <floatHyper.h>
#include <hypercube.h>
#include <iostream>
#include <random>
using namespace SEP;

void floatHyper::add(const std::shared_ptr<floatHyper> vec2) {
  assert(checkSame(vec2));
  std::shared_ptr<floatHyper> vec2H =
      std::dynamic_pointer_cast<floatHyper>(vec2);

  for (long long i = 0; i < getHyper()->getN123(); i++)
    _vals[i] += vec2H->_vals[i];
  calcCheckSum();
}
void floatHyper::mult(const std::shared_ptr<floatHyper> vec2) {
  assert(checkSame(vec2));
  std::shared_ptr<floatHyper> vec2H =
      std::dynamic_pointer_cast<floatHyper>(vec2);

  for (long long i = 0; i < getHyper()->getN123(); i++)
    _vals[i] *= vec2H->_vals[i];
  calcCheckSum();
}
void floatHyper::scaleAdd(std::shared_ptr<floatHyper> vec2, const double sc1,
                          const double sc2) {
  assert(checkSame(vec2));
  std::shared_ptr<floatHyper> vec2H =
      std::dynamic_pointer_cast<floatHyper>(vec2);

  for (long long i = 0; i < getHyper()->getN123(); i++)
    _vals[i] = _vals[i] * sc1 + sc2 * vec2H->_vals[i];
  calcCheckSum();
}
void floatHyper::signum() {
  assert(!spaceOnly());
  for (long long i = 0; i < getHyper()->getN123(); i++) {
    if (_vals[i] > 1e-20)
      _vals[i] = 1;
    else if (_vals[i] < -1e-20)
      _vals[i] = -1;
    else
      _vals[i] = 0;
  }
  calcCheckSum();
}
void floatHyper::scale(double sc) {
  assert(!spaceOnly());
  for (long long i = 0; i < getHyper()->getN123(); i++)
    _vals[i] = _vals[i] * sc;
  calcCheckSum();
}
void floatHyper::random() {
  assert(!spaceOnly());
  for (long long i = 0; i < getHyper()->getN123(); i++)
    _vals[i] = ((double)rand() / (RAND_MAX)) - .5;
  calcCheckSum();
}

double floatHyper::norm(const int n) const {
  double dt = 0;
  if (n == 1) {
    for (long long i = 0; i < getHyper()->getN123(); i++) dt += fabsf(_vals[i]);

  } else if (n == 2) {
    for (long long i = 0; i < getHyper()->getN123(); i++)
      dt += _vals[i] * _vals[i];
  }
  return dt;
}
void floatHyper::zero() {
  for (long long i = 0; i < getHyper()->getN123(); i++) _vals[i] = 0;
  calcCheckSum();
}
double floatHyper::dot(const std::shared_ptr<floatHyper> vec2) const {
  assert(checkSame(vec2));
  std::shared_ptr<floatHyper> vec2H =
      std::dynamic_pointer_cast<floatHyper>(vec2);

  double dt = 0.;
  for (long long i = 0; i < getHyper()->getN123(); i++) {
    dt += (double)_vals[i] * (double)vec2H->_vals[i];
  }

  return dt;
}
void floatHyper::createMask(const float zero, const float err) {
  for (long long i = 0; i < getHyper()->getN123(); i++) {
    if (fabs(_vals[i] - zero) > err)

      _vals[i] = 0.;
    else
      _vals[i] = 1;
  }
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
  for (int i = 0; i < getHyper()->getN123(); i++)
    _vals[i] = scale * _vals[i] / sqrtf(1. + sc2 * _vals[i] * _vals[i]);
  calcCheckSum();
}

double floatHyper::absMax() const {
  float val = fabsf(_vals[0]);
  for (int i = 1; i < getHyper()->getN123(); i++)
    val = std::max(val, fabsf(_vals[i]));
  return (double)val;
}
double floatHyper::max() const {
  float val = fabsf(_vals[0]);
  for (int i = 1; i < getHyper()->getN123(); i++) val = std::max(val, _vals[i]);
  return (double)val;
}
double floatHyper::min() const {
  float val = fabsf(_vals[0]);
  for (int i = 1; i < getHyper()->getN123(); i++) val = std::min(val, _vals[i]);
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
