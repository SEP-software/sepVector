#include <complex1DReg.h>
using namespace SEP;
std::shared_ptr<complex1DReg> complex1DReg::clone() const {
  if (getSpaceOnly()) {
    std::shared_ptr<complex1DReg> x(new complex1DReg(getHyper()));

    return x;
  } else {
    std::shared_ptr<complex1DReg> x(new complex1DReg(getHyper(), *_mat));
    return x;
  }
}
std::shared_ptr<complex1DReg> complex1DReg::cloneSpace() const {
  std::shared_ptr<complex1DReg> x(new complex1DReg(getHyper()));
  x->_mat = 0;
  x->setSpace();

  return x;
}
void complex1DReg::initNoData(std::shared_ptr<SEP::hypercube> hyp) {
  setHyper(hyp);

  _vecType = "vec 1d float";
  const std::vector<SEP::axis> axes = hyp->getAxes();
  assert(axes.size() == 1);
  _mat.reset(new complex1D(boost::extents[axes[0].n]));
  setData(_mat->data());
}
void complex1DReg::initData(std::shared_ptr<SEP::hypercube> hyp,
                            const complex1D &vals) {
  setHyper(hyp);

  const std::vector<SEP::axis> axes = hyp->getAxes();
  assert(axes.size() == 1);
  assert(axes[0].n == vals.shape()[0]);
  _mat.reset(new complex1D(boost::extents[axes[0].n]));
  setData(_mat->data());
  for (long long i = 0; i < axes[0].n; i++) (*_mat)[i] = vals[i];
}
std::shared_ptr<complex1DReg> complex1DReg::window(
    const std::vector<int> &nw, const std::vector<int> &jw,
    const std::vector<int> &fw) const {
  const std::vector<SEP::axis> axes = getHyper()->getAxes();
  assert(nw.size() == axes.size() && fw.size() == axes.size() &&
         jw.size() == axes.size());
  std::vector<axis> aout;
  for (int i = 0; i < axes.size(); i++) {
    checkWindow(axes[i].n, nw[i], fw[i], jw[i]);
    aout.push_back(
        axis(nw[i], axes[i].o + axes[i].d * fw[i], axes[i].d * jw[i]));
  }
  std::shared_ptr<hypercube> hypOut(new hypercube(aout));
  std::shared_ptr<complex1DReg> out(new complex1DReg(hypOut));
  for (int i0 = 0; i0 < nw[0]; i0++) {
    (*out->_mat)[i0] = (*_mat)[fw[0] + i0 * jw[0]];
  }

  return out;
}
/*
void complex1DReg::initData(std::shared_ptr<SEP::hypercube> hyp,
                          const float *vals) {
  setHyper(hyp);

  const std::vector<SEP::axis> axes = hyp->getAxes();
  assert(axes.size() == 1);
  _mat.reset(new complex1D(boost::extents[axes[0].n]));
  setData(_mat->data());
  for (long long i = 0; i < axes[0].n; i++) (*_mat)[i] = vals[i];
}
*/
