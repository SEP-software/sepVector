#include <float2DReg.h>
#include "SEPException.h"
using namespace SEP;

std::shared_ptr<float2DReg> float2DReg::clone() const {
  if (getSpaceOnly()) {
    std::shared_ptr<float2DReg> x(new float2DReg(getHyper()));

    return x;
  } else {
    std::shared_ptr<float2DReg> x(new float2DReg(getHyper(), *_mat));

    return x;
  }
}
std::shared_ptr<float2DReg> float2DReg::cloneSpace() const {
  std::shared_ptr<float2DReg> x(new float2DReg(getHyper()));
  x->_mat = 0;
  x->setSpace();

  return x;
}
float2DReg::float2DReg(const std::shared_ptr<float6DReg> old, const int iax1,
                       const bool rev1, const int iax2, const bool rev2,
                       const std::vector<int> &ipos,
                       const std::vector<int> &beg,
                       const std::vector<int> &end) {
  std::vector<int> j(6, 1);
  std::vector<int> f(6, 0);
  std::vector<int> n(6, 1);
  std::vector<int> nd = old->getHyper()->getNs();
  // Figure out window
  for (auto i = 0; i < n.size(); i++) {
    f[i] = beg[i];
    if (iax1 == i || iax2 == i)
      n[i] = end[i] - beg[i];
    else
      f[i] = ipos[i];
  }

  std::shared_ptr<float6DReg> tmp = old->window(n, f, j);
  axis a1(n[iax1]), a2(n[iax2]);
  std::shared_ptr<hypercube> hyperOut(new hypercube(a1, a2));
  initNoData(hyperOut);
  int f1, j1, f2, j2;
  calcTraverse(n, iax1, rev1, f1, j1, iax2, rev2, f2, j2);
  int ip2 = f2, ip1 = f1, i = 0;
  float *outv = getVals();
  float *inv = tmp->getVals();

  for (auto i2 = 0; i2 < n[iax2]; i2++, ip2 += j2) {
    ip1 = f1;
    for (auto i1 = 0; i1 < n[iax1]; i1++, i++, ip1 += j1) {
      outv[i] = inv[ip1 + ip2];
    }
  }
}
float2DReg::float2DReg(const std::shared_ptr<float5DReg> old, const int iax1,
                       const bool rev1, const int iax2, const bool rev2,
                       const std::vector<int> &ipos,
                       const std::vector<int> &beg,
                       const std::vector<int> &end) {
  std::vector<int> j(5, 1);
  std::vector<int> f(5, 0);
  std::vector<int> n(5, 1);
  std::vector<int> nd = old->getHyper()->getNs();
  // Figure out window
  for (auto i = 0; i < n.size(); i++) {
    f[i] = beg[i];
    if (iax1 == i || iax2 == i)
      n[i] = end[i] - beg[i];
    else
      f[i] = ipos[i];
  }
  std::shared_ptr<float5DReg> tmp = old->window(n, f, j);
  axis a1(n[iax1]), a2(n[iax2]);
  std::shared_ptr<hypercube> hyperOut(new hypercube(a1, a2));
  initNoData(hyperOut);
  int f1, j1, f2, j2;
  calcTraverse(n, iax1, rev1, f1, j1, iax2, rev2, f2, j2);
  int ip2 = f2, ip1 = f1, i = 0;
  float *outv = getVals();
  float *inv = tmp->getVals();
  for (auto i2 = 0; i2 < n[iax2]; i2++, ip2 += j2) {
    ip1 = f1;
    for (auto i1 = 0; i1 < n[iax1]; i1++, i++, ip1 += j1) {
      outv[i] = inv[ip1 + ip2];
    }
  }
}
float2DReg::float2DReg(const std::shared_ptr<float4DReg> old, const int iax1,
                       const bool rev1, const int iax2, const bool rev2,
                       const std::vector<int> &ipos,
                       const std::vector<int> &beg,
                       const std::vector<int> &end) {
  std::vector<int> j(4, 1);
  std::vector<int> f(4, 0);
  std::vector<int> n(4, 1);
  std::vector<int> nd = old->getHyper()->getNs();
  // Figure out window
  for (auto i = 0; i < n.size(); i++) {
    f[i] = beg[i];
    if (iax1 == i || iax2 == i)
      n[i] = end[i] - beg[i];
    else
      f[i] = ipos[i];
  }
  std::shared_ptr<float4DReg> tmp = old->window(n, f, j);
  axis a1(n[iax1]), a2(n[iax2]);
  std::shared_ptr<hypercube> hyperOut(new hypercube(a1, a2));
  initNoData(hyperOut);
  int f1, j1, f2, j2;
  calcTraverse(n, iax1, rev1, f1, j1, iax2, rev2, f2, j2);
  int ip2 = f2, ip1 = f1, i = 0;
  float *outv = getVals();
  float *inv = tmp->getVals();
  for (auto i2 = 0; i2 < n[iax2]; i2++, ip2 += j2) {
    ip1 = f1;
    for (auto i1 = 0; i1 < n[iax1]; i1++, i++, ip1 += j1) {
      outv[i] = inv[ip1 + ip2];
    }
  }
}
float2DReg::float2DReg(const std::shared_ptr<float3DReg> old, const int iax1,
                       const bool rev1, const int iax2, const bool rev2,
                       const std::vector<int> &ipos,
                       const std::vector<int> &beg,
                       const std::vector<int> &end) {
  std::vector<int> j(3, 1);
  std::vector<int> f(3, 0);
  std::vector<int> n(3, 1);
  std::vector<int> nd = old->getHyper()->getNs();
  // Figure out window
  for (auto i = 0; i < n.size(); i++) {
    f[i] = beg[i];
    if (iax1 == i || iax2 == i)
      n[i] = end[i] - beg[i];
    else
      f[i] = ipos[i];
  }
  std::shared_ptr<float3DReg> tmp = old->window(n, f, j);
  axis a1(n[iax1]), a2(n[iax2]);
  std::shared_ptr<hypercube> hyperOut(new hypercube(a1, a2));
  initNoData(hyperOut);
  int f1, j1, f2, j2;
  calcTraverse(n, iax1, rev1, f1, j1, iax2, rev2, f2, j2);
  int ip2 = f2, ip1 = f1, i = 0;
  float *outv = getVals();
  float *inv = tmp->getVals();
  for (auto i2 = 0; i2 < n[iax2]; i2++, ip2 += j2) {
    ip1 = f1;
    for (auto i1 = 0; i1 < n[iax1]; i1++, i++, ip1 += j1) {
      outv[i] = inv[ip1 + ip2];
    }
  }
}
float2DReg::float2DReg(const std::shared_ptr<float2DReg> old, const int iax1,
                       const bool rev1, const int iax2, const bool rev2,
                       const std::vector<int> &ipos,
                       const std::vector<int> &beg,
                       const std::vector<int> &end) {
  std::vector<int> j(2, 1);
  std::vector<int> f(2, 0);
  std::vector<int> n(2, 1);
  std::vector<int> nd = old->getHyper()->getNs();
  // Figure out window

  for (auto i = 0; i < n.size(); i++) {
    f[i] = beg[i];
    if (iax1 == i || iax2 == i) {
      n[i] = end[i] - beg[i];
    } else
      f[i] = ipos[i];
  }

  /*
  f[0] = 0;
  f[1] = 0;
  n[0] = 10;
  n[1] = 10;
  */
  std::cerr << f[0] << "," << f[1] << "<-F" << std::endl;
  std::cerr << j[0] << "," << j[1] << "<-J" << std::endl;
  std::cerr << n[0] << "," << n[1] << "<-N" << std::endl;

  std::cerr << "where id ie 21 " << std::endl;
  std::shared_ptr<float2DReg> tmp = old->window(n, f, j);
  axis a1(n[iax1]), a2(n[iax2]);
  std::shared_ptr<hypercube> hyperOut(new hypercube(a1, a2));
  initNoData(hyperOut);
  int f1, j1, f2, j2;
  std::cerr << "where id ie 31 " << std::endl;

  calcTraverse(n, iax1, rev1, f1, j1, iax2, rev2, f2, j2);
  std::cerr << "where id ie 41 " << std::endl;

  int ip2 = f2, ip1 = f1, i = 0;

  float *outv = getVals();
  float *inv = tmp->getVals();

  for (auto i2 = 0; i2 < n[iax2]; i2++, ip2 += j2) {
    ip1 = f1;
    for (auto i1 = 0; i1 < n[iax1]; i1++, i++, ip1 += j1) {
      outv[i] = inv[ip1 + ip2];
      std::cerr << "WINDOW " << i1 << "," << i2 << " " << ip1 + ip2 << "  # "
                << i << std::endl;
    }
  }

  std::cerr << "where id ie 51 " << std::endl;
}

void float2DReg::initNoData(std::shared_ptr<SEP::hypercube> hyp) {
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);

  if (axes.size() != 2)
    throw SEPException(std::string("Expecting 2-D hyperube"));
  std::cerr << "ALOCATED " << axes[1].n << "," << axes[0].n << std::endl;
  _mat.reset(new float2D(boost::extents[axes[1].n][axes[0].n]));
  setData(_mat->data());
}
void float2DReg::initData(std::shared_ptr<SEP::hypercube> hyp,
                          const float2D &vals) {
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);

  if (axes.size() != 2)
    throw(SEPException(std::string("Axes size must be 3 is ") +
                       std::to_string(axes.size())));
  if (axes[0].n != vals.shape()[1])
    throw(SEPException(std::string("Axis 1 not the same (") +
                       std::to_string(axes[0].n) + std::string(",") +
                       std::to_string(vals.shape()[1]) + std::string(")")));
  if (axes[1].n != vals.shape()[0])
    throw(SEPException(std::string("Axis 2 not the same (") +
                       std::to_string(axes[1].n) + std::string(",") +
                       std::to_string(vals.shape()[0]) + std::string(")")));
  _mat.reset(new float2D(boost::extents[axes[1].n][axes[0].n]));
  setData(_mat->data());
  for (long long j = 0; j < axes[1].n; j++) {
    for (long long i = 0; i < axes[0].n; i++) {
      (*_mat)[j][i] = vals[j][i];
    }
  }
}
std::shared_ptr<float2DReg> float2DReg::window(
    const std::vector<int> &nw, const std::vector<int> &fw,
    const std::vector<int> &jw) const {
  const std::vector<SEP::axis> axes = getHyper()->getAxes();
  if (nw.size() != axes.size())
    throw SEPException(std::string("Expecting 2-D, got nw.size()=") +
                       std::to_string(nw.size()));

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
  std::shared_ptr<float2DReg> out(new float2DReg(hypOut));
  for (int i1 = 0; i1 < nw[1]; i1++) {
    for (int i0 = 0; i0 < nw[0]; i0++) {
      (*out->_mat)[i1][i0] = (*_mat)[fw[1] + i1 * jw[1]][fw[0] + i0 * jw[0]];
    }
  }

  return out;
}
