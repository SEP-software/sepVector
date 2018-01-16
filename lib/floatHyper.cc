#include <floatHyper.h>
#include <hypercube.h>
#include <random>
using namespace giee;

void floatHyper::add(const std::shared_ptr<Vector> vec2) {
  assert(checkSame(vec2, true));
  std::shared_ptr<floatHyper> vec2H =
      std::dynamic_pointer_cast<floatHyper>(vec2);

  for (long long i = 0; i < _hyper->getN123(); i++) _vals[i] += vec2H->_vals[i];
}
void floatHyper::scaleAdd(const double sc1, std::shared_ptr<Vector> vec2,
                          const double sc2) {
  assert(checkSame(vec2, true));
  std::shared_ptr<floatHyper> vec2H =
      std::dynamic_pointer_cast<floatHyper>(vec2);

  for (long long i = 0; i < _hyper->getN123(); i++)
    _vals[i] = _vals[i] * sc1 + sc2 * vec2H->_vals[i];
}

void floatHyper::scale(double sc) {
  assert(!spaceOnly());
  for (long long i = 0; i < _hyper->getN123(); i++) _vals[i] = _vals[i] * sc;
}
void floatHyper::random() {
  assert(!spaceOnly());
  for (long long i = 0; i < _hyper->getN123(); i++)
    _vals[i] = ((double)rand() / (RAND_MAX)) - .5;
}
double floatHyper::dot(const std::shared_ptr<Vector> vec2) const {
  assert(checkSame(vec2, true));

  std::shared_ptr<floatHyper> vec2H =
      std::dynamic_pointer_cast<floatHyper>(vec2);

  double dt = 0.;
  for (long long i = 0; i < _hyper->getN123(); i++) {
    dt += (double)_vals[i] * (double)vec2H->_vals[i];
  }
  return dt;
}
void floatHyper::infoStream(const int lev, std::stringstream &x) {
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
void floatHyper::softClip(const float scale) {
  float sc2 = scale * scale;
  for (int i = 0; i < _hyper->getN123(); i++)
    _vals[i] = scale * _vals[i] / sqrtf(1. + sc2 * _vals[i] * _vals[i]);
}

float floatHyper::absMax() const {
  float val = fabsf(_vals[0]);
  for (int i = 1; i < _hyper->getN123(); i++)
    val = std::max(val, fabsf(_vals[i]));
  return val;
}
float floatHyper::min() const {
  float val = fabsf(_vals[0]);
  for (int i = 1; i < _hyper->getN123(); i++)
    val = std::min(val, fabsf(_vals[i]));
  return val;
}
void floatHyper::calcCheckSum() {
  uint32_t sum1 = 0, sum2 = 0;
  uint32_t *data = (uint32_t *)_vals;
  uint32_t mx = 4294967295;
  for (long long i = 0; i < _hyper->getN123(); i++) {
    sum1 = (sum1 + data[i]) % mx;
    sum2 = (sum2 + sum1) % mx;
  }
  setCheckSum(sum2 * 2 ^ 32 + sum1);
}

bool floatHyper::checkSame(const std::shared_ptr<Vector> vec2,
                           bool checkAlloc) const {
  std::shared_ptr<floatHyper> vec2H =
      std::dynamic_pointer_cast<floatHyper>(vec2);
  if (!vec2) {
    std::cerr << "Not the same type" << std::endl;
    return false;
  }
  if (checkAlloc) {
    if (vec2->spaceOnly()) {
      std::cerr << "vec2 is not allocated" << std::endl;
      return false;
    }
  }
  if (_hyper == vec2H->getHyper()) return true;
  std::cerr << "Not from the same Hypercube" << std::endl;

  return false;
}
