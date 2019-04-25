#ifndef int5d_reg_h
#define int5d_reg_h 1
#include "boost/multi_array.hpp"

#include <intHyper.h>

typedef boost::multi_array<int, 5> int5D;
namespace SEP {
/*!
A regular sampled 5-D function with integer storage
*/
class int5DReg : public intHyper {
 public:
  /*!
 Create a 5-D integer vector from a hypercube
      \param hyper Hypercube describing RSF

 */
  int5DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  /*!
Create a 5-D integer vector from just lengths
    \param n1,n2,n3,n4,n5 Dimensions of the hypercube

*/
  int5DReg(const int n1, const int n2, const int n3, const int n4,
           const int n5) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    a.push_back(SEP::axis(n3));
    a.push_back(SEP::axis(n4));
    a.push_back(SEP::axis(n5));

    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  /*!
 Create a 5-D integer vector from axes
      \param a1,a2,a3,a4,a5 Axes if the hypercube

 */
  int5DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
           const SEP::axis &a4, const SEP::axis &a5) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);
    a.push_back(a4);
    a.push_back(a5);

    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  /*!
Create a 5-D integer vector from a hypercube
     \param hyper Hypercube describing RSF
     \param vals Values to fill vector with

*/
  int5DReg(std::shared_ptr<SEP::hypercube> hyper, const int5D &vals) {
    initData(hyper, vals);
  }
  /*!
Create a 5-D integer vector from just lengths
  \param n1,n2,n3,n4,n5 Dimensions of the hypercube
  \param vals Values to fill vector with

*/
  int5DReg(const int n1, const int n2, const int n3, const int n4, const int n5,
           int5D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    a.push_back(SEP::axis(n3));
    a.push_back(SEP::axis(n4));
    a.push_back(SEP::axis(n5));

    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  /*!
 Create a 5-D integer vector from axes
      \param a1,a2,a3,a4,a5 Axes if the hypercube
      \param vals Values to fill vector with
 */
  int5DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
           const SEP::axis &a4, const SEP::axis &a5, int5D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);
    a.push_back(a4);
    a.push_back(a5);

    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  /*!
   Allocate data for vector
   */
  void allocate() {
    std::vector<int> ns = getHyper()->getNs();
    _mat.reset(new int5D(boost::extents[ns[4]][ns[3]][ns[2]][ns[1]][ns[0]]));

    setData(_mat->data());
    ;
  }
  /*!
      Return a subset of the vector
      \param nw,fw,jw Windowing parameters
      */
  std::shared_ptr<int5DReg> window(const std::vector<int> &nw,
                                   const std::vector<int> &fw,
                                   const std::vector<int> &jw) const;
  /*!
Make a copy of the vector
*/
  std::shared_ptr<int5DReg> clone() const;
  /*!
Make a copy of the vector space
*/
  std::shared_ptr<int5DReg> cloneSpace() const;
  /*!
 Deallocate storage for vector, turn into vector space
  */
  virtual void cleanMemory() {
    _mat = 0;
    setSpace();
  }
  std::shared_ptr<int5D> _mat;  ///< Storage for vector

 private:
  /*!
Initialize without data
\param hyper Hypercube describing space
*/
  void initNoData(std::shared_ptr<SEP::hypercube> hyper);
  /*!
Initialize with data
\param hyper Hypercube describing space
\param vals Data to copy in
*/
  void initData(std::shared_ptr<SEP::hypercube> hyper, const int5D &vals);
};
}  // namespace SEP
#endif
