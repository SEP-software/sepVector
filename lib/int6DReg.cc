#include <int6DReg.h>

using namespace SEP;

std::shared_ptr<int6DReg> int6DReg::clone() const {
  if (getSpaceOnly()) {
    std::shared_ptr<int6DReg> x(new int6DReg(getHyper()));

    return x;
  } else {
    std::shared_ptr<int6DReg> x(new int6DReg(getHyper(), *_mat));

    return x;
  }
}
std::shared_ptr<int6DReg> int6DReg::cloneSpace() const {
  std::shared_ptr<int6DReg> x(new int6DReg(getHyper()));
  x->_mat = 0;

  x->setSpace();
  return x;
}

void int6DReg::initNoData(std::shared_ptr<SEP::hypercube> hyp) {
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);

  assert(axes.size() == 6);

  _mat.reset(new int6D(boost::extents[axes[5].n][axes[4].n][axes[3].n]
                                     [axes[2].n][axes[1].n][axes[0].n]));
  setData(_mat->data());
}
void int6DReg::initData(std::shared_ptr<SEP::hypercube> hyp,
                        const int6D &vals) {
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);

  assert(axes.size() == 6);
  assert(axes[0].n == vals.shape()[5] && axes[1].n == vals.shape()[4] &&
         axes[2].n == vals.shape()[3] && axes[3].n == vals.shape()[2] &&
         axes[4].n == vals.shape()[1] && axes[5].n == vals.shape()[0]

  );
  _mat.reset(new int6D(boost::extents[axes[5].n][axes[4].n][axes[3].n]
                                     [axes[2].n][axes[1].n][axes[0].n]));
  setData(_mat->data());
  for (size_t n = 0; n < axes[5].n; n++) {
    for (size_t m = 0; m < axes[4].n; m++) {
      for (long long l = 0; l < axes[3].n; l++) {
        for (long long k = 0; k < axes[2].n; k++) {
          for (long long j = 0; j < axes[1].n; j++) {
            for (long long i = 0; i < axes[0].n; i++) {
              (*_mat)[n][m][l][k][j][i] = vals[n][m][l][k][j][i];
            }
          }
        }
      }
    }
  }
}
