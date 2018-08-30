#include <double1DReg.h>
using namespace SEP;
std::shared_ptr<double1DReg> double1DReg::clone() const {
  if (getSpaceOnly()) {
    std::shared_ptr<double1DReg> x(new double1DReg(getHyper()));

    return x;
  } else {
    std::shared_ptr<double1DReg> x(new double1DReg(getHyper(), *_mat));
    return x;
  }
}
std::shared_ptr<double1DReg> double1DReg::cloneSpace() const {
  std::shared_ptr<double1DReg> x(new double1DReg(getHyper()));
  x->_mat = 0;
  x->setSpace();

  return x;
}
void double1DReg::initNoData(std::shared_ptr<SEP::hypercube> hyp) {
  setHyper(hyp);

  _vecType = "vec 1d float";
  const std::vector<SEP::axis> axes = hyp->getAxes();
  assert(axes.size() == 1);
  _mat.reset(new double1D(boost::extents[axes[0].n]));
  setData(_mat->data());
}
void double1DReg::initData(std::shared_ptr<SEP::hypercube> hyp,
                           const double1D &vals) {
  setHyper(hyp);

  const std::vector<SEP::axis> axes = hyp->getAxes();
  assert(axes.size() == 1);
  assert(axes[0].n == vals.shape()[0]);
  _mat.reset(new double1D(boost::extents[axes[0].n]));
  setData(_mat->data());
  for (long long i = 0; i < axes[0].n; i++) (*_mat)[i] = vals[i];
}

/*
void double1DReg::initData(std::shared_ptr<SEP::hypercube> hyp,
                          const float *vals) {
  setHyper(hyp);

  const std::vector<SEP::axis> axes = hyp->getAxes();
  assert(axes.size() == 1);
  _mat.reset(new double1D(boost::extents[axes[0].n]));
  setData(_mat->data());
  for (long long i = 0; i < axes[0].n; i++) (*_mat)[i] = vals[i];
}
*/
