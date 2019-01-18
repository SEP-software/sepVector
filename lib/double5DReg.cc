#include <double5DReg.h>

using namespace SEP;

std::shared_ptr<double5DReg> double5DReg::clone() const {
  if (getSpaceOnly()) {
    std::shared_ptr<double5DReg> x(new double5DReg(getHyper()));

    return x;
  } else {
    std::shared_ptr<double5DReg> x(new double5DReg(getHyper(), *_mat));

    return x;
  }
}
std::shared_ptr<double5DReg> double5DReg::cloneSpace() const {
  std::shared_ptr<double5DReg> x(new double5DReg(getHyper()));
  x->_mat = 0;

  x->setSpace();
  return x;
}

void double5DReg::initNoData(std::shared_ptr<SEP::hypercube> hyp) {
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);

  assert(axes.size() == 5);

  _mat.reset(new double5D(
      boost::extents[axes[4].n][axes[3].n][axes[2].n][axes[1].n][axes[0].n]));
  setData(_mat->data());
}
void double5DReg::initData(std::shared_ptr<SEP::hypercube> hyp,
                           const double5D &vals) {
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);

  assert(axes.size() == 5);
  assert(axes[4].n == vals.shape()[0] && axes[3].n == vals.shape()[1] &&
         axes[2].n == vals.shape()[2] && axes[1].n == vals.shape()[3] &&
         axes[2].n == vals.shape()[2]);
  _mat.reset(new double5D(
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
std::shared_ptr<double5DReg> double5DReg::window(
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
  std::shared_ptr<double5DReg> out(new double5DReg(hypOut));
  for (int i4 = 0; i4 < nw[4]; i4++) {
    for (int i3 = 0; i3 < nw[3]; i3++) {
      for (int i2 = 0; i2 < nw[2]; i2++) {
        for (int i1 = 0; i1 < nw[1]; i1++) {
          for (int i0 = 0; i0 < nw[0]; i0++) {
            (*out->_mat)[i4][i3][i2][i1][i0] =
                (*_mat)[fw[4] + i4 * jw[4]][fw[3] + i3 * jw[3]]
                       [fw[2] + i2 * jw[2]][fw[1] + i1 * jw[1]]
                       [fw[0] + i0 * jw[0]];
          }
        }
      }
    }
  }
  return out;
}