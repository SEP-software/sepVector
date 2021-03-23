#include <float1DReg.h>
using namespace SEP;
std::shared_ptr<float1DReg> float1DReg::clone() const
{
  if (getSpaceOnly())
  {
    std::shared_ptr<float1DReg> x(new float1DReg(getHyper()));

    return x;
  }
  else
  {
    std::shared_ptr<float1DReg> x(new float1DReg(getHyper(), *_mat));
    return x;
  }
}
std::shared_ptr<float1DReg> float1DReg::cloneSpace() const
{
  std::shared_ptr<float1DReg> x(new float1DReg(getHyper()));
  x->_mat = 0;
  x->setSpace();

  return x;
}
float1DReg::float1DReg(const std::shared_ptr<float6DReg> old, const int iax1,
                       const bool rev, const std::vector<int> &ipos,
                       const std::vector<int> &beg,
                       const std::vector<int> &end)
{
  std::vector<int> n, f, j;
  std::shared_ptr<hypercube> hyperOut;
  std::tie(hyperOut, n, f, j) = sliceToWindow1D(iax1, beg, end, ipos);
  std::shared_ptr<float6DReg> tmp = old->window(n, f, j);
  initNoData(hyperOut);
  doTraverse1D(n, iax1, rev, tmp->getCVals(), getVals(), sizeof(float));
}

float1DReg::float1DReg(const std::shared_ptr<float5DReg> old, const int iax1,
                       const bool rev, const std::vector<int> &ipos,
                       const std::vector<int> &beg,
                       const std::vector<int> &end)
{
  std::vector<int> n, f, j;
  std::shared_ptr<hypercube> hyperOut;
  std::tie(hyperOut, n, f, j) = sliceToWindow1D(iax1, beg, end, ipos);
  std::shared_ptr<float5DReg> tmp = old->window(n, f, j);
  initNoData(hyperOut);
  doTraverse1D(n, iax1, rev, tmp->getCVals(), getVals(), sizeof(float));
}

float1DReg::float1DReg(const std::shared_ptr<float4DReg> old, const int iax1,
                       const bool rev, const std::vector<int> &ipos,
                       const std::vector<int> &beg,
                       const std::vector<int> &end)
{
  std::vector<int> n, f, j;
  std::shared_ptr<hypercube> hyperOut;
  std::tie(hyperOut, n, f, j) = sliceToWindow1D(iax1, beg, end, ipos);
  std::shared_ptr<float4DReg> tmp = old->window(n, f, j);
  initNoData(hyperOut);
  doTraverse1D(n, iax1, rev, tmp->getCVals(), getVals(), sizeof(float));
}

float1DReg::float1DReg(const std::shared_ptr<float3DReg> old, const int iax1,
                       const bool rev, const std::vector<int> &ipos,
                       const std::vector<int> &beg,
                       const std::vector<int> &end)
{
  std::vector<int> n, f, j;
  std::shared_ptr<hypercube> hyperOut;
  std::tie(hyperOut, n, f, j) = sliceToWindow1D(iax1, beg, end, ipos);
  std::shared_ptr<float3DReg> tmp = old->window(n, f, j);
  initNoData(hyperOut);
  doTraverse1D(n, iax1, rev, tmp->getCVals(), getVals(), sizeof(float));
}

float1DReg::float1DReg(const std::shared_ptr<float2DReg> old, const int iax1,
                       const bool rev, const std::vector<int> &ipos,
                       const std::vector<int> &beg,
                       const std::vector<int> &end)
{
  std::vector<int> n, f, j;
  std::shared_ptr<hypercube> hyperOut;
  std::tie(hyperOut, n, f, j) = sliceToWindow1D(iax1, beg, end, ipos);
  std::shared_ptr<float2DReg> tmp = old->window(n, f, j);
  initNoData(hyperOut);
  doTraverse1D(n, iax1, rev, tmp->getCVals(), getVals(), sizeof(float));
}

float1DReg::float1DReg(const std::shared_ptr<float1DReg> old, const int iax1,
                       const bool rev, const std::vector<int> &ipos,
                       const std::vector<int> &beg,
                       const std::vector<int> &end)
{
  std::vector<int> n, f, j;
  std::shared_ptr<hypercube> hyperOut;
  std::tie(hyperOut, n, f, j) = sliceToWindow1D(iax1, beg, end, ipos);
  std::shared_ptr<float1DReg> tmp = old->window(n, f, j);
  initNoData(hyperOut);
  doTraverse1D(n, iax1, rev, tmp->getCVals(), getVals(), sizeof(float));
}

void float1DReg::initNoData(std::shared_ptr<SEP::hypercube> hyp)
{
  setHyper(hyp);

  _vecType = "vec 1d float";
  const std::vector<SEP::axis> axes = hyp->getAxes();
  if (axes.size() != 1)
    throw(SEPException(std::string("Axes size must be 1 is ") +
                       std::to_string(axes.size())));
  _mat.reset(new float1D(boost::extents[axes[0].n]));
  setData(_mat->data());
}
void float1DReg::initData(std::shared_ptr<SEP::hypercube> hyp,
                          const float1D &vals)
{
  setHyper(hyp);

  const std::vector<SEP::axis> axes = hyp->getAxes();
  if (axes.size() != 1)
    throw(SEPException(std::string("Axes size must be 1 is ") +
                       std::to_string(axes.size())));
  if (axes[0].n != vals.shape()[0])
    throw(SEPException(std::string("Axis 1 not the same (") +
                       std::to_string(axes[0].n) + std::string(",") +
                       std::to_string(vals.shape()[0]) + std::string(")")));
  _mat.reset(new float1D(boost::extents[axes[0].n]));
  setData(_mat->data());
  for (long long i = 0; i < axes[0].n; i++)
    (*_mat)[i] = vals[i];
}
std::shared_ptr<float1DReg> float1DReg::window(
    const std::vector<int> &nw, const std::vector<int> &fw,
    const std::vector<int> &jw) const
{
  const std::vector<SEP::axis> axes = getHyper()->getAxes();
  if (nw.size() != axes.size())
    throw(SEPException("nw must of length 1"));
  if (fw.size() != axes.size())
    throw(SEPException("fw must of length 1"));
  if (jw.size() != axes.size())
    throw(SEPException("jw must of length 1"));
  std::vector<axis> aout;
  for (int i = 0; i < axes.size(); i++)
  {
    checkWindow(axes[i].n, nw[i], fw[i], jw[i]);
    aout.push_back(
        axis(nw[i], axes[i].o + axes[i].d * fw[i], axes[i].d * jw[i]));
  }
  std::shared_ptr<hypercube> hypOut(new hypercube(aout));
  std::shared_ptr<float1DReg> out(new float1DReg(hypOut));
  for (int i0 = 0; i0 < nw[0]; i0++)
  {
    (*out->_mat)[i0] = (*_mat)[fw[0] + i0 * jw[0]];
  }

  return out;
}
