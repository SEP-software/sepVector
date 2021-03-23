
#include <iostream>

#include "regSpace.h"
using namespace SEP;
void regSpace::checkWindow(const int n, const int nw, const int fw,
                           const int jw) const
{
  if (fw < 0)
    throw(SEPException(std::string("fw must be 0 or greater=") +
                       std::to_string(fw)));
  if (jw < 1)
    throw(SEPException(std::string("jw must be 1 or greater=") +
                       std::to_string(jw)));
  if (nw < 1)
    throw(SEPException(std::string("nw must be 1 or greater=") +
                       std::to_string(nw)));
  if (fw + jw * (nw - 1) >= n)
    throw(SEPException(std::string("fw+jw*(nw-1) <n ") + std::to_string(fw) +
                       std::string("=fw jw=") + std::to_string(jw) +
                       std::string(" nw=") + std::to_string(nw) +
                       std::string(" n=") + std::to_string(n)));
}

std::vector<float> regSpace::axisToKey(const int ix) const
{
  int iaxis = ix - 1;
  long long naft = 1, nbef = 1, naxis;
  std::vector<axis> axes = getHyper()->getAxes();
  for (auto iax = 1; iax < axes.size(); iax++)
  {
    if (iax < iaxis && iax != 0)
      nbef = nbef * axes[iax].n;
    else if (iax == iaxis)
      naxis = axes[iax].n;
    else
      naft = naft * axes[iax].n;
  }

  long long i = 0;
  float o = axes[iaxis].o;
  float d = axes[iaxis].d;

  std::vector<float> key(nbef * naft * naxis);
  for (long long i3 = 0; i3 < naft; i3++)
  {
    for (long long i2 = 0; i2 < naxis; i2++)
    {
      for (long long i1 = 0; i1 < nbef; i1++, i++)
      {
        key[i] = o + i2 * d;
      }
    }
  }
  return key;
}

std::tuple<std::shared_ptr<hypercube>, std::vector<int>, std::vector<int>, std::vector<int> >
regSpace::sliceToWindow2D(const int iax1, const int iax2, const std::vector<int> beg,
                          const std::vector<int> end, const std::vector<int> ipos)
{

  int nsz = beg.size();
  std::vector<int> j(nsz, 1);
  std::vector<int> f(nsz, 0);
  std::vector<int> n(nsz, 1);

  // Figure out window
  for (auto i = 0; i < n.size(); i++)
  {
    f[i] = beg[i];
    if (iax1 == i || iax2 == i)
      n[i] = end[i] - beg[i];
    else
      f[i] = ipos[i];
  }
  std::vector<axis> axes, aIn = _hyper->getAxes();
  axes.push_back(aIn[iax1].n);
  axes.push_back(aIn[iax2].n);
  std::shared_ptr<hypercube> hyperOut(new hypercube(axes));
  return std::make_tuple(hyperOut, n, f, j);
}
/*!
     Calculate window params


     */
std::tuple<std::shared_ptr<hypercube>, std::vector<int>, std::vector<int>, std::vector<int> >
regSpace::sliceToWindow1D(const int iax1, const std::vector<int> beg,
                          const std::vector<int> end, const std::vector<int> ipos)
{

  int nsz = beg.size();
  std::vector<int> j(nsz, 1);
  std::vector<int> f(nsz, 0);
  std::vector<int> n(nsz, 1);

  // Figure out window
  for (auto i = 0; i < n.size(); i++)
  {
    f[i] = beg[i];
    if (iax1 == i)
      n[i] = end[i] - beg[i];
    else
      f[i] = ipos[i];
  }
  std::vector<axis> axes, aIn = _hyper->getAxes();
  axes.push_back(aIn[iax1].n);
  std::shared_ptr<hypercube> hyperOut(new hypercube(axes));
  return std::make_tuple(hyperOut, n, f, j);
}

/*!
        Return how to loop through a dataset to return a slice with arbitray
       orientations

        \param  nd of the dataset
        \param iax1 Fast axis of output traverse
        \param rev1 Whether or not reverse fast axis
        \param iax2 Slow axis of output trarvers
        \param rev2 Whether or not to reverse slow axis
        \param inA Input pointer
        \param outA Output pointer
        \param esize Element size

    */

void regSpace::doTraverse2D(const std::vector<int> &n, const int iax1, const bool rev1,
                            const int iax2, const bool rev2, const void *inA, void *outA, const int esize)
{
  int f1, j1, f2, j2;
  std::tie(f1, j1, f2, j2) = calcTraverse2D(n, iax1, rev1, iax2, rev2);
  int ip2 = f2, ip1 = f1, i = 0;
  const char *inC = (char *)inA;
  char *outC = (char *)outA;
  for (auto i2 = 0; i2 < n[iax2]; i2++, ip2 += j2)
  {
    ip1 = f1;
    for (auto i1 = 0; i1 < n[iax1]; i1++, i++, ip1 += j1)
    {
      memcpy(outC + i * esize, inC + (ip1 + ip2) * esize, esize);
    }
  }
}
/*!
        Return how to loop through a dataset to return a slice with arbitray
       orientations

        \param  nd of the dataset
        \param iax1 Fast axis of output traverse
        \param rev1 Whether or not reverse fast axis
        \param f1  First element to grab along fast axis
        \param j1  Skip every j1 elements along fast axis
        \param iax2 Slow axis of output trarvers
        \param rev2 Whether or not to reverse slow axis
        \param f2   First element of slow axis
        \param j2 Skip every j2 element along slow axis
    */
std::tuple<int, int, int, int> regSpace::calcTraverse2D(
    const std::vector<int> &nd, const int iax1, const bool rev1,
    const int iax2, const bool rev2)
{
  int f1, j1, f2, j2;
  if (iax2 > iax1)
  {
    if (!rev1)
    {
      f1 = 0;
      j1 = 1;
    }
    else
    {
      f1 = nd[iax1] - 1;
      j1 = -1;
    }
    if (!rev2)
    {
      f2 = 0;
      j2 = nd[iax1];
    }
    else
    {
      f2 = (nd[iax2] - 1) * nd[iax1];
      j2 = -nd[iax1];
    }
  }
  else
  {
    if (!rev2)
    {
      f2 = 0;
      j2 = 1;
    }
    else
    {
      f2 = nd[iax2] - 1;
      j2 = -1;
    }
    if (!rev1)
    {
      f1 = 0;
      j1 = nd[iax2];
    }
    else
    {
      f1 = (nd[iax1] - 1) * nd[iax2];
      j1 = -nd[iax2];
    }
  }
  return std::make_tuple(f1, j1, f2, j2);
}

/*!
        Return how to loop through a dataset to return a slice with arbitray
       orientations

        \param  nd of the dataset
        \param iax1 Fast axis of output traverse
        \param rev1 Whether or not reverse fast axis
        \param iax2 Slow axis of output trarvers
        \param rev2 Whether or not to reverse slow axis
        \param inA Input pointer
        \param outA Output pointer
        \param esize Element size

    */

void regSpace::doTraverse1D(const std::vector<int> &nd, const int iax1, const bool rev1,
                            const void *inA, void *outA, const int esize)
{
  int f1, j1;
  std::tie(f1, j1) = calcTraverse1D(nd, iax1, rev1);
  int ip1 = f1, i = 0;
  const char *inC = (char *)inA;
  char *outC = (char *)outA;
  for (auto i1 = 0; i1 < nd[iax1]; i1++, i++, ip1 += j1)
    memcpy(outC + i * esize, inC + ip1 * esize, esize);
}
/*!
        Return how to loop through a dataset to return a slice with arbitray
       orientations

        \param  nd of the dataset
        \param iax1 Fast axis of output traverse
        \param rev1 Whether or not reverse fast axis
        \param f1  First element to grab along fast axis
        \param j1  Skip every j1 elements along fast axis
       
    */
std::tuple<int, int> calcTraverse1D(
    const std::vector<int> &nd, const int iax1, const bool rev1)
{

  int f1 = 0, j1 = 1;
  if (rev1)
  {
    f1 = nd[iax1] - 1;
    j1 = -1;
  }
  return std::make_tuple(f1, j1);
}
