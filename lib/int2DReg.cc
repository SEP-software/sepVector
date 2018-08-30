#include <int2DReg.h>
using namespace SEP;

std::shared_ptr<int2DReg> int2DReg::clone() const {
  if (getSpaceOnly()) {
    std::shared_ptr<int2DReg> x(new int2DReg(getHyper()));

    return x;
  } else {
    std::shared_ptr<int2DReg> x(new int2DReg(getHyper(), *_mat));

    return x;
  }
}
std::shared_ptr<int2DReg> int2DReg::cloneSpace() const {
  std::shared_ptr<int2DReg> x(new int2DReg(getHyper()));
  x->_mat = 0;
  x->setSpace();

  return x;
}

void int2DReg::initNoData(std::shared_ptr<SEP::hypercube> hyp) {
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);

  assert(axes.size() == 2);

  _mat.reset(new int2D(boost::extents[axes[1].n][axes[0].n]));
  setData(_mat->data());
}
void int2DReg::initData(std::shared_ptr<SEP::hypercube> hyp,
                        const int2D &vals) {
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);

  assert(axes.size() == 2);
  assert(axes[0].n == vals.shape()[1] && axes[1].n == vals.shape()[0]);
  _mat.reset(new int2D(boost::extents[axes[1].n][axes[0].n]));
  setData(_mat->data());
  for (long long j = 0; j < axes[1].n; j++) {
    for (long long i = 0; i < axes[0].n; i++) {
      (*_mat)[j][i] = vals[j][i];
    }
  }
}
