#include <float3DReg.h>
using namespace SEP;

std::shared_ptr<float3DReg> float3DReg::clone() const {
  if (getSpaceOnly()) {
    std::shared_ptr<float3DReg> x(new float3DReg(getHyper()));
    return x;
  } else {
    std::shared_ptr<float3DReg> x(new float3DReg(getHyper(), *_mat));

    return x;
  }
}
std::shared_ptr<float3DReg> float3DReg::cloneSpace() const {
  std::shared_ptr<float3DReg> x(new float3DReg(getHyper()));
  x->_mat = 0;
  x->setSpace();

  return x;
}

void float3DReg::initNoData(std::shared_ptr<SEP::hypercube> hyp) {
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);

  assert(axes.size() == 3);

  _mat.reset(new float3D(boost::extents[axes[2].n][axes[1].n][axes[0].n]));
  setData(_mat->data());
}
void float3DReg::initData(std::shared_ptr<SEP::hypercube> hyp,
                          const float3D &vals) {
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);

  assert(axes.size() == 3);
  assert(axes[0].n == vals.shape()[2] && axes[1].n == vals.shape()[1] &&
         axes[2].n == vals.shape()[0]);
  _mat.reset(new float3D(boost::extents[axes[2].n][axes[1].n][axes[0].n]));
  setData(_mat->data());
  for (long long k = 0; k < axes[2].n; k++) {
    for (long long j = 0; j < axes[1].n; j++) {
      for (long long i = 0; i < axes[0].n; i++) {
        (*_mat)[k][j][i] = vals[k][j][i];
      }
    }
  }
}
void float3DReg::initData(std::shared_ptr<SEP::hypercube> hyp,
                          std::shared_ptr<float3D> vals) {
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);

  assert(axes.size() == 3);
  assert(axes[0].n == vals->shape()[2] && axes[1].n == vals->shape()[1] &&
         axes[2].n == vals->shape()[0]);
  _mat.reset(new float3D(boost::extents[axes[2].n][axes[1].n][axes[0].n]));
  setData(_mat->data());
  for (long long k = 0; k < axes[2].n; k++) {
    for (long long j = 0; j < axes[1].n; j++) {
      for (long long i = 0; i < axes[0].n; i++) {
        (*_mat)[k][j][i] = (*vals)[k][j][i];
      }
    }
  }
}
