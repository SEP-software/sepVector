#include <floatHyper.h>
#include <hypercube.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>
#include <tbb/tbb.h>
#include <iostream>
#include <random>
#include "int1DReg.h"
using namespace SEP;
void floatHyper::add(const std::shared_ptr<floatHyper> vec2)
{
  if (!checkSame(vec2))
    throw(std::string("Vectors not of the same space"));
  std::shared_ptr<floatHyper> vec2H =
      std::dynamic_pointer_cast<floatHyper>(vec2);
    float *v=getVals(),*v2=vec2->getVals();

  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        v[i] += v2[i];
                    });
  calcCheckSum();
}
void floatHyper::mult(const std::shared_ptr<floatHyper> vec2)
{
  if (!checkSame(vec2))
    throw(std::string("Vectors not of the same space"));
  std::shared_ptr<floatHyper> vec2H =
      std::dynamic_pointer_cast<floatHyper>(vec2);
    float *v=getVals(),*v2=vec2->getVals();

  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        v[i] *= v2[i];
                    });
  calcCheckSum();
}
void floatHyper::clipVector(const std::shared_ptr<floatHyper> beg,
                            const std::shared_ptr<floatHyper> end)
{
  if (!checkSame(beg))
    throw(std::string("Vectors not of the same space"));
  if (!checkSame(end))
    throw(std::string("Vectors not of the same space"));
    float *v=getVals(),*bv=beg->getVals(),*ev=end->getVals();

  std::shared_ptr<floatHyper> begH = std::dynamic_pointer_cast<floatHyper>(beg);
  std::shared_ptr<floatHyper> endH = std::dynamic_pointer_cast<floatHyper>(end);
  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        v[i] = std::min(ev[i],
                                            std::max(bv[i], v[i]));
                    });
  calcCheckSum();
}
void floatHyper::scaleAdd(std::shared_ptr<floatHyper> vec2, const double sc1,
                          const double sc2)
{
  if (!checkSame(vec2))
    throw(std::string("Vectors not of the same space"));
    float *v=getVals(),*v2=vec2->getVals();

  std::shared_ptr<floatHyper> vec2H =
      std::dynamic_pointer_cast<floatHyper>(vec2);

  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        v[i] = v[i] * sc1 + sc2 * v2[i];
                    });
  calcCheckSum();
}

float floatHyper::cent(const long long iv, const int js) const
{
  long long n = getHyper()->getN123() / js;
  float *x = new float[n];
  // float *x = (float *)malloc(sizeof(float) * n);
  const float *in = getCVals();
  if (js < 1)
    throw SEPException(std::string("j must be positive ") + std::to_string(js));
  for (auto i = 0; i < n; i++)
  {
    x[i] = in[i * js];
  }
  double w = (double)(iv) / (double)n;
  long long q =
      std::max((long long)0, std::min((long long)(n - 1), (long long)(w * n)));
  // std::cerr << "looking for " << q << " " << n << " " <<
  // getHyper()->getN123()
  //        << std::endl;

  float *i, *j, ak;
  float *low, *hi, buf, *k;
  for (low = x, hi = x + n - 1, k = x + q; low < hi;)
  {
    ak = *k;
    i = low;
    j = hi;
    do
    {
      while (*i < ak)
        i++;
      while (*j > ak)
        j--;
      if (i <= j)
      {
        buf = *i;
        *i++ = *j;
        *j-- = buf;
      }
    } while (i <= j);
    if (j < k)
      low = i;
    if (k < i)
      hi = j;
  }
  float m = *k;
  delete[] x;
  // free(x);
  return m;
}
void floatHyper::clip(const float bclip, const float eclip, bool outer)
{
  if (spaceOnly())
    throw(std::string("Vectors not allocated"));
        float *v=getVals();

  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      if (outer)
                      {
                        for (long long i = r.begin(); i != r.end(); ++i)
                          v[i] = std::min(eclip, std::max(bclip, v[i]));
                      }
                      else
                      {
                        for (long long i = r.begin(); i != r.end(); ++i)
                        {
                          if (v[i] < eclip && v[i] > bclip)
                            v[i] = 0;
                        }
                      }
                    });
  calcCheckSum();
}
void floatHyper::signum()
{
  if (spaceOnly())
    throw(std::string("Vectors not allocated"));
  float *v=getVals();
  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                      {
                        if (v[i] > 1e-20)
                          v[i] = 1;
                        else if (v[i] < -1e-20)
                          v[i] = -1;
                        else
                          v[i] = 0;
                      }
                    });

  calcCheckSum();
}
void floatHyper::scale(double sc)
{
  if (spaceOnly())
    throw(std::string("Vectors not allocated"));
      float *v=getVals();

  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        v[i] = v[i] * sc;
                    });
  calcCheckSum();
}
void floatHyper::random()
{
  if (spaceOnly())
    throw(std::string("Vectors not allocated"));
      float *v=getVals();

  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        v[i] = ((double)rand() / (RAND_MAX)) - .5;
                    });
  calcCheckSum();
}

double floatHyper::norm(const int n) const
{
    const float *vs=getCVals();

  double dt = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()), 0.,
      [&](const tbb::blocked_range<size_t> &r, double v) {
        if (n == 1)
        {
          for (size_t i = r.begin(); i != r.end(); ++i)
          {
            v += (double)fabsf(vs[i]);
          }
        }
        else
        {
          for (size_t i = r.begin(); i != r.end(); ++i)
          {
            v += (double)vs[i] * (double)vs[i];
          }
        }
        return v;
      },
      [](double a, double b) { return a + b; });
  if (n == 2)
    return sqrtf(dt);

  return dt;
}
void floatHyper::set(const float val)
{
    float *v=getVals();

  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        v[i] = val;
                    });

  calcCheckSum();
}
void floatHyper::calcHisto(std::shared_ptr<int1DReg> &histo, float mn,
                           float mx)
{
  long long nelem = histo->getHyper()->getN123();
  float delta = (mx - mn) / (nelem - 1);
  float idelta = 1. / delta;
    float *v=getVals();

  std::vector<int> h = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()),
      std::vector<int>(nelem, 0),
      [&](const tbb::blocked_range<size_t> &r, std::vector<int> tmp) {
        for (size_t i = r.begin(); i != r.end(); ++i)
        {
          int ielem = std::max(
              (long long)0,
              std::min(nelem - 1, (long long)((v[i] - mn) * idelta)));
          tmp[ielem] += 1;
        }
        return tmp;
      },
      [&](std::vector<int> tmp1, std::vector<int> tmp2) {
        std::vector<int> tmp = tmp1;
        for (int i = 0; i < nelem; i++)
          tmp[i] += tmp2[i];
        return tmp;
      });
  for (long long i = 0; i < nelem; i++)
  {
    histo->getVals()[i] = h[i];
  }
}

double floatHyper::dot(const std::shared_ptr<floatHyper> vec2) const
{
  if (!checkSame(vec2))
    throw(std::string("Vectors not of the same space"));
  std::shared_ptr<floatHyper> vec2H =
      std::dynamic_pointer_cast<floatHyper>(vec2);
      const float *vs=getCVals(),*v2=getCVals();


  double dot = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()), 0.,
      [&](const tbb::blocked_range<size_t> &r, double v) {
        for (size_t i = r.begin(); i != r.end(); ++i)
        {
          v += (double)vs[i] * (double)v2[i];
        }
        return v;
      },
      [](double a, double b) { return a + b; });

  return dot;
}
void floatHyper::createMask(const float zero, const float err)
{

    float *v=getVals();

  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                      {
                        if (fabs(v[i] - zero) > err)

                          v[i] = 0.;
                        else
                          v[i] = 1;
                      }
                    });
  calcCheckSum();
}

void floatHyper::infoStream(const int lev, std::stringstream &x)
{
  getHyper()->infoStream(x);
  const float *v=getCVals();
  if (spaceOnly())
    x << "Only space\n";
  else
  {
    x << "Allocated\n";
    long long npts = std::min((const long long)lev, getHyper()->getN123());
    for (long long i = 0; i < npts; i++)
      x << std::to_string(i) << std::string(" ") << std::to_string(v[i])
        << std::endl;
  }
}
void floatHyper::softClip(const float scale)
{
  float sc2 = scale * scale;
    float *v=getVals();

  tbb::parallel_for(tbb::blocked_range<long long>(0, getHyper()->getN123()),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                        v[i] = scale * v[i] /
                                   sqrtf(1. + sc2 * v[i] * v[i]);
                    });
  calcCheckSum();
}

double floatHyper::absMax() const
{
    const float *vs=getCVals();

  float val = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()), -1e31,
      [&](const tbb::blocked_range<size_t> &r, float v) {
        for (size_t i = r.begin(); i != r.end(); ++i)
        {
          v = std::max(v, fabsf(vs[i]));
        }
        return v;
      },
      [](float a, float b) {
        if (a > b)
          return a;
        return b;
      });
  return (double)val;
}
double floatHyper::max() const
{
    const float *vs=getCVals();

  float val = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()), -1e31,
      [&](const tbb::blocked_range<size_t> &r, float v) {
        for (size_t i = r.begin(); i != r.end(); ++i)
        {
          v = std::max(v, vs[i]);
        }
        return v;
      },
      [](float a, float b) {
        if (a > b)
          return a;
        return b;
      });
  return (double)val;
}
double floatHyper::min() const
{
    const float *vs=getCVals();

  float val = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, getHyper()->getN123()), 1e31,
      [&](const tbb::blocked_range<size_t> &r, float v) {
        for (size_t i = r.begin(); i != r.end(); ++i)
        {
          v = std::min(v, vs[i]);
        }
        return v;
      },
      [](float a, float b) {
        if (a > b)
          return b;
        return a;
      });
  return (double)val;
}

void floatHyper::calcCheckSum()
{
  long long nsect = ceilf((double)getHyper()->getN123() / (double)100000);
  std::vector<float> sz(nsect, 100000);
  std::vector<uint32_t> sum1(nsect), sum2(nsect);
  sz[nsect - 1] = getHyper()->getN123() - (nsect - 1) * 100000;
  uint32_t mx = 4294967295;
  const float *v=getCVals();

  tbb::parallel_for(tbb::blocked_range<long long>(0, nsect),
                    [&](const tbb::blocked_range<long long> &r) {
                      for (long long i = r.begin(); i != r.end(); ++i)
                      {
                        sum1[i] = 0;
                        sum2[i] = 0;
                        uint32_t *data =
                            (uint32_t *)(&v[r.begin() * 100000]);
                        for (long long j = 0; j < sz[i]; j++)
                        {
                          sum1[i] = (sum1[i] + data[j]) % mx;
                          sum2[i] = (sum2[i] + sum1[i]) % mx;
                        }
                      }
                    });

  uint32_t sum1t = 0, sum2t = 0;
  for (long long i = 0; i < nsect; i++)
  {
    sum1t = (sum1t + sum1[i]) % mx;
    sum2t = (sum2t + sum2[i]) % mx;
  }
  setCheckSum(sum2t * 2 ^ 32 + sum1t);
}

bool floatHyper::checkSame(const std::shared_ptr<floatHyper> vec2) const
{

  if (!vec2)
  {
    throw SEPException("Vec2 is not allocated");
    return false;
  }
  bool b;
  try
  {
    b = getHyper()->checkSame(vec2->getHyper());
  }
  catch (SEPException &e)
  {
    return false;
    throw SEPException(e.getMessage());
  }

  return b;
}

void floatHyper::copyVals(const float *vals){
   memcpy(getVals(), vals, getHyper()->getN123()*sizeof(float));
}
