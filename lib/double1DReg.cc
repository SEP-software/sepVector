#include <double1DReg.h>
using namespace SEP;
std::shared_ptr<double1DReg> double1DReg::clone() const {
  if (getSpaceOnly()) {
    std::shared_ptr<double1DReg> x(new double1DReg(getHyper()));

    return x;
  } else {
    std::shared_ptr<double1DReg> x(new double1DReg(getHyper(), *_mat));
    return x;
  }
}
std::shared_ptr<double1DReg> double1DReg::cloneSpace() const {
  std::shared_ptr<double1DReg> x(new double1DReg(getHyper()));
  x->_mat = 0;
  x->setSpace();

  return x;
}
void double1DReg::initNoData(std::shared_ptr<SEP::hypercube> hyp) {
  setHyper(hyp);

  _vecType = "vec 1d float";
  const std::vector<SEP::axis> axes = hyp->getAxes();
  if (axes.size() != 1)
    throw(SEPException(std::string("Axes size must be 1 is ") +
                       std::to_string(axes.size())));
  _mat.reset(new double1D(boost::extents[axes[0].n]));
  setData(_mat->data());
}
void double1DReg::initData(std::shared_ptr<SEP::hypercube> hyp,
                           const double1D &vals) {
  setHyper(hyp);

  const std::vector<SEP::axis> axes = hyp->getAxes();
  if (axes.size() != 1)
    throw(SEPException(std::string("Axes size must be 1 is ") +
                       std::to_string(axes.size())));
  if (axes[0].n != vals.shape()[0])
    throw(SEPException(std::string("Axis 1 not the same (") +
                       std::to_string(axes[0].n) + std::string(",") +
                       std::to_string(vals.shape()[0]) + std::string(")")));
  _mat.reset(new double1D(boost::extents[axes[0].n]));
  setData(_mat->data());
  for (long long i = 0; i < axes[0].n; i++) (*_mat)[i] = vals[i];
}
std::shared_ptr<double1DReg> double1DReg::window(
    const std::vector<int> &nw, const std::vector<int> &jw,
    const std::vector<int> &fw) const {
  const std::vector<SEP::axis> axes = getHyper()->getAxes();
  if (nw.size() != axes.size()) throw(SEPException("nw must of length 1"));
  if (fw.size() != axes.size()) throw(SEPException("fw must of length 1"));
  if (jw.size() != axes.size()) throw(SEPException("jw must of length 1"));
  std::vector<axis> aout;
  for (int i = 0; i < axes.size(); i++) {
    checkWindow(axes[i].n, nw[i], fw[i], jw[i]);
    aout.push_back(
        axis(nw[i], axes[i].o + axes[i].d * fw[i], axes[i].d * jw[i]));
  }
  std::shared_ptr<hypercube> hypOut(new hypercube(aout));
  std::shared_ptr<double1DReg> out(new double1DReg(hypOut));
  for (int i0 = 0; i0 < nw[0]; i0++) {
    (*out->_mat)[i0] = (*_mat)[fw[0] + i0 * jw[0]];
  }

  return out;
}
