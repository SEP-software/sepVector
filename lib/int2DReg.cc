#include <int2DReg.h>
using namespace SEP;

std::shared_ptr<int2DReg> int2DReg::clone() const
{
  if (getSpaceOnly())
  {
    std::shared_ptr<int2DReg> x(new int2DReg(getHyper()));

    return x;
  }
  else
  {
    std::shared_ptr<int2DReg> x(new int2DReg(getHyper(), *_mat));

    return x;
  }
}
std::shared_ptr<int2DReg> int2DReg::cloneSpace() const
{
  std::shared_ptr<int2DReg> x(new int2DReg(getHyper()));
  x->_mat = 0;
  x->setSpace();

  return x;
}
int2DReg::int2DReg(const std::shared_ptr<int6DReg> old, const int iax1,
                   const bool rev1, const int iax2, const bool rev2,
                   const std::vector<int> &ipos, const std::vector<int> &beg,
                   std::vector<int> &end)
{
  std::vector<int> n, f, j;
  std::shared_ptr<hypercube> hyperOut;
  std::tie(hyperOut, n, f, j) = sliceToWindow2D(iax1, iax2, beg, end, ipos);
  std::shared_ptr<int6DReg> tmp = old->window(n, f, j);
  initNoData(hyperOut);
  doTraverse2D(n, iax1, rev1, iax2, rev2, tmp->getCVals(), getVals(), sizeof(int));
}
int2DReg::int2DReg(const std::shared_ptr<int5DReg> old, const int iax1,
                   const bool rev1, const int iax2, const bool rev2,
                   const std::vector<int> &ipos, const std::vector<int> &beg,
                   std::vector<int> &end)
{
  std::vector<int> n, f, j;
  std::shared_ptr<hypercube> hyperOut;
  std::tie(hyperOut, n, f, j) = sliceToWindow2D(iax1, iax2, beg, end, ipos);
  std::shared_ptr<int5DReg> tmp = old->window(n, f, j);
  initNoData(hyperOut);
  doTraverse2D(n, iax1, rev1, iax2, rev2, tmp->getCVals(), getVals(), sizeof(int));
}
int2DReg::int2DReg(const std::shared_ptr<int4DReg> old, const int iax1,
                   const bool rev1, const int iax2, const bool rev2,
                   const std::vector<int> &ipos, const std::vector<int> &beg,
                   std::vector<int> &end)
{
  std::vector<int> n, f, j;
  std::shared_ptr<hypercube> hyperOut;
  std::tie(hyperOut, n, f, j) = sliceToWindow2D(iax1, iax2, beg, end, ipos);
  std::shared_ptr<int4DReg> tmp = old->window(n, f, j);
  initNoData(hyperOut);
  doTraverse2D(n, iax1, rev1, iax2, rev2, tmp->getCVals(), getVals(), sizeof(int));
}
int2DReg::int2DReg(const std::shared_ptr<int3DReg> old, const int iax1,
                   const bool rev1, const int iax2, const bool rev2,
                   const std::vector<int> &ipos, const std::vector<int> &beg,
                   std::vector<int> &end)
{
  std::vector<int> n, f, j;
  std::shared_ptr<hypercube> hyperOut;
  std::tie(hyperOut, n, f, j) = sliceToWindow2D(iax1, iax2, beg, end, ipos);
  std::shared_ptr<int3DReg> tmp = old->window(n, f, j);
  initNoData(hyperOut);
  doTraverse2D(n, iax1, rev1, iax2, rev2, tmp->getCVals(), getVals(), sizeof(int));
}
int2DReg::int2DReg(const std::shared_ptr<int2DReg> old, const int iax1,
                   const bool rev1, const int iax2, const bool rev2,
                   const std::vector<int> &ipos, const std::vector<int> &beg,
                   std::vector<int> &end)
{
  std::vector<int> n, f, j;
  std::shared_ptr<hypercube> hyperOut;
  std::tie(hyperOut, n, f, j) = sliceToWindow2D(iax1, iax2, beg, end, ipos);
  std::shared_ptr<int2DReg> tmp = old->window(n, f, j);
  initNoData(hyperOut);
  doTraverse2D(n, iax1, rev1, iax2, rev2, tmp->getCVals(), getVals(), sizeof(int));
}
void int2DReg::initNoData(std::shared_ptr<SEP::hypercube> hyp)
{
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);

  if (axes.size() != 2)
    throw(SEPException(std::string("Axes size must be 2 is ") +
                       std::to_string(axes.size())));
  _mat.reset(new int2D(boost::extents[axes[1].n][axes[0].n]));
  setData(_mat->data());
}
void int2DReg::initData(std::shared_ptr<SEP::hypercube> hyp,
                        const int2D &vals)
{
  const std::vector<SEP::axis> axes = hyp->getAxes();
  setHyper(hyp);
  if (axes.size() != 2)
    throw(SEPException(std::string("Axes size must be 2 is ") +
                       std::to_string(axes.size())));
  if (axes[0].n != vals.shape()[1])
    throw(SEPException(std::string("Axis 1 not the same (") +
                       std::to_string(axes[0].n) + std::string(",") +
                       std::to_string(vals.shape()[1]) + std::string(")")));
  if (axes[1].n != vals.shape()[0])
    throw(SEPException(std::string("Axis 2 not the same (") +
                       std::to_string(axes[1].n) + std::string(",") +
                       std::to_string(vals.shape()[0]) + std::string(")")));

  _mat.reset(new int2D(boost::extents[axes[1].n][axes[0].n]));
  setData(_mat->data());
  for (long long j = 0; j < axes[1].n; j++)
  {
    for (long long i = 0; i < axes[0].n; i++)
    {
      (*_mat)[j][i] = vals[j][i];
    }
  }
}
std::shared_ptr<int2DReg> int2DReg::window(const std::vector<int> &nw,
                                           const std::vector<int> &fw,
                                           const std::vector<int> &jw) const
{
  const std::vector<SEP::axis> axes = getHyper()->getAxes();
  if (nw.size() != axes.size())
    throw(SEPException("nw must of length 2"));
  if (fw.size() != axes.size())
    throw(SEPException("fw must of length 2"));
  if (jw.size() != axes.size())
    throw(SEPException("jw must of length 2"));
  std::vector<axis> aout;
  for (int i = 0; i < axes.size(); i++)
  {
    checkWindow(axes[i].n, nw[i], fw[i], jw[i]);
    aout.push_back(
        axis(nw[i], axes[i].o + axes[i].d * fw[i], axes[i].d * jw[i]));
  }
  std::shared_ptr<hypercube> hypOut(new hypercube(aout));
  std::shared_ptr<int2DReg> out(new int2DReg(hypOut));
  for (int i1 = 0; i1 < nw[1]; i1++)
  {
    for (int i0 = 0; i0 < nw[0]; i0++)
    {
      (*out->_mat)[i1][i0] = (*_mat)[fw[1] + i1 * jw[1]][fw[0] + i0 * jw[0]];
    }
  }

  return out;
}