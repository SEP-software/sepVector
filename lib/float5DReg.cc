#include <float5DReg.h>

using namespace SEP;

std::shared_ptr<float5DReg> float5DReg::clone() const {
  if (getSpaceOnly()) {
    std::shared_ptr<float5DReg> x(new float5DReg(getHyper()));

    return x;
  } else {
    std::shared_ptr<float5DReg> x(new float5DReg(getHyper(), *_mat));

    return x;
  }
}
std::shared_ptr<float5DReg> float5DReg::cloneSpace() const {
  std::shared_ptr<float5DReg> x(new float5DReg(getHyper()));
  x->_mat = 0;

  x->setSpace();
  return x;
}

void float5DReg::initNoData(std::shared_ptr<SEP::hypercube> hyp) {
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);

  assert(axes.size() == 5);

  _mat.reset(new float5D(
      boost::extents[axes[4].n][axes[3].n][axes[2].n][axes[1].n][axes[0].n]));
  setData(_mat->data());
}
void float5DReg::initData(std::shared_ptr<SEP::hypercube> hyp,
                          const float5D &vals) {
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);

  assert(axes.size() == 5);
  assert(axes[4].n == vals.shape()[0] && axes[3].n == vals.shape()[1] &&
         axes[2].n == vals.shape()[2] && axes[1].n == vals.shape()[3] &&
         axes[2].n == vals.shape()[2]);
  _mat.reset(new float5D(
      boost::extents[axes[4].n][axes[3].n][axes[2].n][axes[1].n][axes[0].n]));
  setData(_mat->data());
  for (long long m = 0; m < axes[4].n; m++) {
    for (long long l = 0; l < axes[3].n; l++) {
      for (long long k = 0; k < axes[2].n; k++) {
        for (long long j = 0; j < axes[1].n; j++) {
          for (long long i = 0; i < axes[0].n; i++) {
            (*_mat)[m][l][k][j][i] = vals[m][l][k][j][i];
          }
        }
      }
    }
  }
}
