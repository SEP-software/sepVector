#include <hypercube.h>
#include <intHyper.h>
#include <iostream>
#include <random>
using namespace SEP;

void intHyper::add(const std::shared_ptr<intHyper> vec2) {
  assert(checkSame(vec2));
  std::shared_ptr<intHyper> vec2H = std::dynamic_pointer_cast<intHyper>(vec2);

  for (long long i = 0; i < _hyper->getN123(); i++) _vals[i] += vec2H->_vals[i];
  calcCheckSum();
}
void intHyper::mult(const std::shared_ptr<intHyper> vec2) {
  assert(checkSame(vec2));
  std::shared_ptr<intHyper> vec2H = std::dynamic_pointer_cast<intHyper>(vec2);

  for (long long i = 0; i < _hyper->getN123(); i++) _vals[i] *= vec2H->_vals[i];
  calcCheckSum();
}
void intHyper::scaleAdd(std::shared_ptr<intHyper> vec2, const double sc1,
                        const double sc2) {
  assert(checkSame(vec2));
  std::shared_ptr<intHyper> vec2H = std::dynamic_pointer_cast<intHyper>(vec2);

  for (long long i = 0; i < _hyper->getN123(); i++)
    _vals[i] = _vals[i] * sc1 + sc2 * vec2H->_vals[i];
  calcCheckSum();
}
void intHyper::signum() {
  assert(!spaceOnly());
  for (long long i = 0; i < _hyper->getN123(); i++) {
    if (_vals[i] > 1e-20)
      _vals[i] = 1;
    else if (_vals[i] < -1e-20)
      _vals[i] = -1;
    else
      _vals[i] = 0;
  }
  calcCheckSum();
}
void intHyper::scale(double sc) {
  assert(!spaceOnly());
  for (long long i = 0; i < _hyper->getN123(); i++) _vals[i] = _vals[i] * sc;
  calcCheckSum();
}
void intHyper::random() {
  assert(!spaceOnly());
  for (long long i = 0; i < _hyper->getN123(); i++)
    _vals[i] = ((double)rand() / (RAND_MAX)) - .5;
  calcCheckSum();
}

long long intHyper::norm(const int n) const {
  long long dt = 0;
  if (n == 1) {
    for (long long i = 0; i < _hyper->getN123(); i++) dt += fabsf(_vals[i]);

  } else if (n == 2) {
    for (long long i = 0; i < _hyper->getN123(); i++) dt += _vals[i] * _vals[i];
  }
  return dt;
}
void intHyper::zero() {
  for (long long i = 0; i < _hyper->getN123(); i++) _vals[i] = 0;
  calcCheckSum();
}
double intHyper::dot(const std::shared_ptr<intHyper> vec2) const {
  assert(checkSame(vec2));
  std::shared_ptr<intHyper> vec2H = std::dynamic_pointer_cast<intHyper>(vec2);

  double dt = 0.;
  for (long long i = 0; i < _hyper->getN123(); i++) {
    dt += (double)_vals[i] * (double)vec2H->_vals[i];
  }

  return dt;
}
void intHyper::createMask(const int zero, const int err) {
  for (long long i = 0; i < _hyper->getN123(); i++) {
    if (abs(_vals[i] - zero) > err)

      _vals[i] = 0.;
    else
      _vals[i] = 1;
  }
  calcCheckSum();
}

void intHyper::infoStream(const int lev, std::stringstream &x) {
  _hyper->infoStream(x);
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
void intHyper::softClip(const float scale) {
  float sc2 = scale * scale;
  for (int i = 0; i < _hyper->getN123(); i++)
    _vals[i] = scale * _vals[i] / sqrt(1. + sc2 * _vals[i] * _vals[i]);
  calcCheckSum();
}

int intHyper::absMax() const {
  int val = abs(_vals[0]);
  for (int i = 1; i < _hyper->getN123(); i++)
    val = std::max(val, abs(_vals[i]));
  return val;
}
int intHyper::max() const {
  int val = abs(_vals[0]);
  for (int i = 1; i < _hyper->getN123(); i++) val = std::max(val, _vals[i]);
  return val;
}
int intHyper::min() const {
  int val = abs(_vals[0]);
  for (int i = 1; i < _hyper->getN123(); i++) val = std::min(val, _vals[i]);
  return val;
}
void intHyper::calcCheckSum() {
  uint32_t sum1 = 0, sum2 = 0;
  uint32_t *data = (uint32_t *)_vals;
  uint32_t mx = 4294967295;
  for (long long i = 0; i < _hyper->getN123(); i++) {
    sum1 = (sum1 + data[i]) % mx;
    sum2 = (sum2 + sum1) % mx;
  }
  setCheckSum(sum2 * 2 ^ 32 + sum1);
}

bool intHyper::checkSame(const std::shared_ptr<intHyper> vec2) const {
  if (!vec2) {
    std::cerr << "Not allocated vec2" << std::endl;
    return false;
  }
  //  if (_hyper == vec2->getHyper()) return true;
  return true;
  std::cerr << _hyper->getAxis(1).n << " " << vec2->getHyper()->getAxis(1).n
            << std::endl;
  std::cerr << "Not from the same Hypercube" << std::endl;

  return false;
}
