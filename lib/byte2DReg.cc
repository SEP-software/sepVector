#include <byte2DReg.h>
using namespace SEP;

std::shared_ptr<byte2DReg> byte2DReg::clone() const {
  if (getSpaceOnly()) {
    std::shared_ptr<byte2DReg> x(new byte2DReg(getHyper()));

    return x;
  } else {
    std::shared_ptr<byte2DReg> x(new byte2DReg(getHyper(), *_mat));

    return x;
  }
}
std::shared_ptr<byte2DReg> byte2DReg::cloneSpace() const {
  std::shared_ptr<byte2DReg> x(new byte2DReg(getHyper()));
  x->_mat = 0;
  x->setSpace();

  return x;
}

void byte2DReg::initNoData(std::shared_ptr<SEP::hypercube> hyp) {
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);

  assert(axes.size() == 2);

  _mat.reset(new byte2D(boost::extents[axes[1].n][axes[0].n]));
  setData(_mat->data());
}
void byte2DReg::initData(std::shared_ptr<SEP::hypercube> hyp,
                         const byte2D &vals) {
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);

  assert(axes.size() == 2);
  assert(axes[0].n == vals.shape()[1] && axes[1].n == vals.shape()[0]);
  _mat.reset(new byte2D(boost::extents[axes[1].n][axes[0].n]));
  setData(_mat->data());
  for (long long j = 0; j < axes[1].n; j++) {
    for (long long i = 0; i < axes[0].n; i++) {
      (*_mat)[j][i] = vals[j][i];
    }
  }
}
std::shared_ptr<byte2DReg> byte2DReg::window(const std::vector<int> &nw,
                                             const std::vector<int> &jw,
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
  std::shared_ptr<byte2DReg> out(new byte2DReg(hypOut));
  for (int i1 = 0; i1 < nw[1]; i1++) {
    for (int i0 = 0; i0 < nw[0]; i0++) {
      (*out->_mat)[i1][i0] = (*_mat)[fw[1] + i1 * jw[1]][fw[0] + i0 * jw[0]];
    }
  }

  return out;
}