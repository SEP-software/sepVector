#ifndef double4d_reg_h
#define double4d_reg_h 1
#include "boost/multi_array.hpp"

#include <doubleHyper.h>

typedef boost::multi_array<double, 4> double4D;
namespace SEP {
/*!
A regular sampled 4-D function with double storage
*/
class double4DReg : public doubleHyper {
 public:
  /*!
 Create a 4-D double vector from a hypercube
 \param hyper Hypercube describing RSF
 */
  double4DReg(std::shared_ptr<SEP::hypercube> hyper) { initNoData(hyper); }
  /*!
Create a 4-D double vector from just lengths
     \param n1,n2,n3,n4 Dimensions of the hypercube

*/
  double4DReg(const int n1, const int n2, const int n3, const int n4) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    a.push_back(SEP::axis(n3));
    a.push_back(SEP::axis(n4));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  /*!
    Create a 4-D double vector from axes
         \param a1,a2,a3,a4 Axes if the hypercube

    */
  double4DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
              const SEP::axis &a4) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);
    a.push_back(a4);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initNoData(hyp);
  }
  /*!
Create a 4-D double vector from a hypercube
      \param hyper Hypercube describing RSF
      \param vals Vaules for the vector

*/
  double4DReg(std::shared_ptr<SEP::hypercube> hyper, const double4D &vals) {
    initData(hyper, vals);
  }
  /*!
  Create a 4-D double vector from just lengths
       \param n1,n2,n3,n4 Dimensions of the hypercube
       \param vals Vaules for the vector

  */
  double4DReg(const int n1, const int n2, const int n3, const int n4,
              double4D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(SEP::axis(n1));
    a.push_back(SEP::axis(n2));
    a.push_back(SEP::axis(n3));
    a.push_back(SEP::axis(n4));
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  /*!
 Create a -D double vector from axes
      \param a1,a2,a3,a4 Axes if the hypercube
      \param vals Vaules for the vector
 */
  double4DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
              const SEP::axis &a4, double4D &vals) {
    std::vector<SEP::axis> a;
    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);
    a.push_back(a4);
    std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
    initData(hyp, vals);
  }
  /*!
    Allocate data for vector
    */
  void allocate() {
    std::vector<int> ns = getHyper()->getNs();
    _mat.reset(new double4D(boost::extents[ns[3]][ns[2]][ns[1]][ns[0]]));

    setData(_mat->data());
    ;
  }

  /*!
  Return a subset of the vector
  \param nw,fw,jw Windowing parameters
  */
  std::shared_ptr<double4DReg> window(const std::vector<int> &nw,
                                      const std::vector<int> &fw,
                                      const std::vector<int> &jw) const;
  /*!
 Make a copy of the vector
 */
  std::shared_ptr<double4DReg> clone() const;
  /*!
 Make a copy of the vector space
 */
  std::shared_ptr<double4DReg> cloneSpace() const;
  /*!
   Deallocate storage for vector, turn into vector space
    */
  virtual void cleanMemory() {
    _mat = 0;
    setSpace();
  }
  std::shared_ptr<double4D> _mat;  ///< Storage for vector

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
  void initData(std::shared_ptr<SEP::hypercube> hyper, const double4D &vals);
};
}  // namespace SEP
#endif
