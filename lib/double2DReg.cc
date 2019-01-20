#include <double2DReg.h>
using namespace SEP;

std::shared_ptr<double2DReg> double2DReg::clone() const {
  if (getSpaceOnly()) {
    std::shared_ptr<double2DReg> x(new double2DReg(getHyper()));

    return x;
  } else {
    std::shared_ptr<double2DReg> x(new double2DReg(getHyper(), *_mat));

    return x;
  }
}
std::shared_ptr<double2DReg> double2DReg::cloneSpace() const {
  std::shared_ptr<double2DReg> x(new double2DReg(getHyper()));
  x->_mat = 0;
  x->setSpace();

  return x;
}

void double2DReg::initNoData(std::shared_ptr<SEP::hypercube> hyp) {
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);
  if (2 != axes.size()) throw(SEPException("must be 2-D hypercube"));

  _mat.reset(new double2D(boost::extents[axes[1].n][axes[0].n]));
  setData(_mat->data());
}
void double2DReg::initData(std::shared_ptr<SEP::hypercube> hyp,
                           const double2D &vals) {
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);

  _mat.reset(new double2D(boost::extents[axes[1].n][axes[0].n]));
  setData(_mat->data());
  for (long long j = 0; j < axes[1].n; j++) {
    for (long long i = 0; i < axes[0].n; i++) {
      (*_mat)[j][i] = vals[j][i];
    }
  }
}
std::shared_ptr<double2DReg> double2DReg::window(
    const std::vector<int> &nw, const std::vector<int> &jw,
    const std::vector<int> &fw) const {
  const std::vector<SEP::axis> axes = getHyper()->getAxes();
  if (nw.size() != axes.size()) throw(SEPException("nw must of length 2"));
  if (fw.size() != axes.size()) throw(SEPException("fw must of length 2"));
  if (jw.size() != axes.size()) throw(SEPException("jw must of length 2"));
  std::vector<axis> aout;
  for (int i = 0; i < axes.size(); i++) {
    checkWindow(axes[i].n, nw[i], fw[i], jw[i]);
    aout.push_back(
        axis(nw[i], axes[i].o + axes[i].d * fw[i], axes[i].d * jw[i]));
  }
  std::shared_ptr<hypercube> hypOut(new hypercube(aout));
  std::shared_ptr<double2DReg> out(new double2DReg(hypOut));
  for (int i1 = 0; i1 < nw[1]; i1++) {
    for (int i0 = 0; i0 < nw[0]; i0++) {
      (*out->_mat)[i1][i0] = (*_mat)[fw[1] + i1 * jw[1]][fw[0] + i0 * jw[0]];
    }
  }

  return out;
}