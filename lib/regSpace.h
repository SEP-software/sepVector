#ifndef reg_space_h
#define reg_space_h 1
#include "SEPException.h"
#include "hypercube.h"
#include <string.h>
#include <tuple>
namespace SEP {
/*!
A class for regular sampled function (virtual)
*/
class regSpace {
public:
  /*!
   Initalizer for virtual regular sampled function class
*/
  regSpace() { ; }
  /*!
   Return the hypercube associated with the regular sampled function
*/
  std::shared_ptr<SEP::hypercube> getHyper() const { return _hyper; }
  /*!
   Set the hypercube that describes the regular sampled function
  */
  void setHyper(std::shared_ptr<SEP::hypercube> h) { _hyper = h->clone(); }
  /*!
    Set the memory associted with regular sampled function and the element
   size of the data

    \param ptr  Pointer associated with the data
    \param esize Element size sizeof(float),sizeof(int),etc
*/
  void setMemPtr(void *ptr, size_t esize) {
    _storage = ptr;
    _esize = esize;
  }
  /*!
   Checck to see if window parameters make sense

   \param n  Axis length
   \param nw Number of samples to grab
   \param fw First element to grab
   \param jw Samples to skip
 */

  void checkWindow(const int n, const int nw, const int fw, const int jw) const;
  /*!
  Given hypercube translate an axis to a key

  \param iax Axis to convert to a key
  */
  std::vector<float> axisToKey(const int iaxis) const;
  ///*  Return pointer to storage
  void *getCVoidPtr() const { return _storage; }
  ///*  Return pointer to storage
  void *getVoidPtr() { return _storage; }
  ///* Get the size of each element in  vector
  size_t getEsize() { return _esize; }
  ///* Remove the regular space object
  virtual ~regSpace() = default;
  /*! copyElements

    CopyElements - Copy the elements of another vector,
       size must be same but shape does not

       \param otherVec Vector to copy from
 */
  void copyElements(const std::shared_ptr<regSpace> otherVec);

protected:
  /*!
   Calculate window params


   */
  std::tuple<std::shared_ptr<hypercube>, std::vector<int>, std::vector<int>,
             std::vector<int>>
  sliceToWindow2D(const int iax1, const int iax2, const std::vector<int> beg,
                  const std::vector<int> end, const std::vector<int> ipos); /*
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
  */
  /*!
   Calculate window params


   */
  std::tuple<std::shared_ptr<hypercube>, std::vector<int>, std::vector<int>,
             std::vector<int>>
  sliceToWindow1D(const int iax1, const std::vector<int> beg,
                  const std::vector<int> end, const std::vector<int> ipos); /*
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
  */

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

  void doTraverse2D(const std::vector<int> &n, const int iax1, const bool rev1,
                    const int iax2, const bool rev2, const void *inA,
                    void *outA, const int esize); /*
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
*/
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
  std::tuple<int, int, int, int> calcTraverse2D(const std::vector<int> &nd,
                                                const int iax1, const bool rev1,
                                                const int iax2,
                                                const bool rev2); /*
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
                            */

  /*!
      Return how to loop through a dataset to return a slice with arbitray
     orientations

      \param  nd of the dataset
      \param iax1 Fast axis of output traverse
      \param rev1 Whether or not reverse fast axis
      \param iax2 Slow axis of output trarvers
      \param rev2 Whether or not to reverse slowopy axis
      \param inA Input pointer
      \param outA Output pointer
      \param esize Element size

  */

  void doTraverse1D(const std::vector<int> &nd, const int iax1, const bool rev1,
                    const void *inA, void *outA, const int esize);
  /*
  {
    int f1, j1;
    std::tie(f1, j1) = calcTraverse1D(nd, iax1, rev1);
    int ip1 = f1, i = 0;
    const char *inC = (char *)inA;
    char *outC = (char *)outA;
    for (auto i1 = 0; i1 < nd[iax1]; i1++, i++, ip1 += j1)
      memcpy(outC + i * esize, inC + ip1 * esize, esize);
  }
  */
  /*!
      Return how to loop through a dataset to return a slice with arbitray
     orientations

      \param  nd of the dataset
      \param iax1 Fast axis of output traverse
      \param rev1 Whether or not reverse fast axis
      \param f1  First element to grab along fast axis
      \param j1  Skip every j1 elements along fast axis

  */
  std::tuple<int, int> calcTraverse1D(const std::vector<int> &nd,
                                      const int iax1, const bool rev1);
  /*
  {

    int f1 = 0, j1 = 1;
    if (rev1)
    {
      f1 = nd[iax1] - 1;
      j1 = -1;
    }
    return std::make_tuple(f1, j1);
  }
  */

private:
  std::shared_ptr<SEP::hypercube>
      _hyper;     ///< Hypercube associated with the regular sampled function
  size_t _esize;  ///< Element size for each vector element
  void *_storage; ///< Pointer to storage for regular sampled function
};
} // namespace SEP
#endif
