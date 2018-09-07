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
std::cerr<<"WHAT 1"<<std::endl;
  const std::vector<SEP::axis> axes = hyp->getAxes();
std::cerr<<"WHAT 2"<<std::endl;
  setHyper(hyp);
std::cerr<<"WHATf1"<<std::endl;

  std::cerr<<"NMM "<<axes.size()<<std::endl;
  assert(axes.size() == 3);
std::cerr<<"WHAT 3 "axes[2].n<<" 2-1 "<<axes[1].n<<" "<<axes[0].n<<std::endl;

  _mat.reset(new float3D(boost::extents[axes[2].n][axes[1].n][axes[0].n]));
std::cerr<<"WHAT 4"<<std::endl;
  setData(_mat->data());
std::cerr<<"WHAT 5"<<std::endl;
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
