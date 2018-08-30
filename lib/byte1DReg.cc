#include <byte1DReg.h>
using namespace SEP;
std::shared_ptr<byte1DReg> byte1DReg::clone() const {
  if (getSpaceOnly()) {
    std::shared_ptr<byte1DReg> x(new byte1DReg(getHyper()));

    return x;
  } else {
    std::shared_ptr<byte1DReg> x(new byte1DReg(getHyper(), *_mat));
    return x;
  }
}
std::shared_ptr<byte1DReg> byte1DReg::cloneSpace() const {
  std::shared_ptr<byte1DReg> x(new byte1DReg(getHyper()));
  x->_mat = 0;
  x->setSpace();

  return x;
}
void byte1DReg::initNoData(std::shared_ptr<SEP::hypercube> hyp) {
  setHyper(hyp);

  _vecType = "vec 1d int";
  const std::vector<SEP::axis> axes = hyp->getAxes();
  assert(axes.size() == 1);
  _mat.reset(new byte1D(boost::extents[axes[0].n]));
  setData(_mat->data());
}
void byte1DReg::initData(std::shared_ptr<SEP::hypercube> hyp,
                         const byte1D &vals) {
  setHyper(hyp);

  const std::vector<SEP::axis> axes = hyp->getAxes();
  assert(axes.size() == 1);
  assert(axes[0].n == vals.shape()[0]);
  _mat.reset(new byte1D(boost::extents[axes[0].n]));
  setData(_mat->data());
  for (long long i = 0; i < axes[0].n; i++) (*_mat)[i] = vals[i];
}

/*
void float1DReg::initData(std::shared_ptr<SEP::hypercube> hyp,
                          const float *vals) {
  setHyper(hyp);

  const std::vector<SEP::axis> axes = hyp->getAxes();
  assert(axes.size() == 1);
  _mat.reset(new float1D(boost::extents[axes[0].n]));
  setData(_mat->data());
  for (long long i = 0; i < axes[0].n; i++) (*_mat)[i] = vals[i];
}
*/
