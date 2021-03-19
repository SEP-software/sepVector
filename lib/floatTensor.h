#ifndef float_tensor_h
#define float_tensor_h 1
#include "SEPException.h"
#include "Vector.h"
#include "int1DReg.h"
#include "regSpace.h"
#include "xtensor/xarray.hpp"
#include <cstdint>
#include <hypercube.h>
#include <iostream>
#include <sstream>

namespace SEP {
/*!
  A regular sampled function that stores float values
*/
class floatTensor {
public:
  /*!
  Initializer for floatTensor class
  */
  floatTensor() { ; }
  /*!
  Initialize vector with length 
    \param n1 length of first axis
  */
  floatTensor(const int n1){
     std::vector<axis> axes;
     axes.push_back(axis(n1));
     initAxes(axes);
  }
   /*!
  Initialize vector with length 
    \param n1 length of first axis
    \param n2 length of second axis

  */
  floatTensor(const int n1,const int n2){
    std::vector<axis> axes:
     axes.push_back(axis(n1));
     axes.push_back(axis(n2));
     initAxes(axes);
}
   /*!
  Initialize vector with length 
    \param n1 length of first axis
    \param n2 length of second axis
    \param n3 length of second axis
    \param n4 length of second axis
    \param n5 length of second axis
    \param n6 length of second axis
    \param n7 length of second axis
    \param n8 length of second axis

  */
  floatTensor(const int n1,const int n2,const int n3,const  int n4, const int n5, const int n6, const int n7, const int n8){
    std::vector<axis> axes:
     axes.push_back(axis(n1));
     axes.push_back(axis(n2));
    axes.push_back(axis(n3));
     axes.push_back(axis(n4));
     axes.push_back(axis(n5));
     axes.push_back(axis(n6));
     axes.push_back(axis(n7));
     axes.push_back(axis(n8));
     initAxes(axes);
}  
   /*!
  Initialize vector with length
    \param n1 length of first axis
    \param n2 length of second axis
    \param n3 length of second axis
    \param n4 length of second axis
    \param n5 length of second axis
    \param n6 length of second axis
    \param n7 length of second axis

  */
  floatTensor(const int n1,const int n2,const int n3, const int n4,const  int n5,const  int n6, const int n7){
    std::vector<axis> axes:
     axes.push_back(axis(n1));
     axes.push_back(axis(n2));
    axes.push_back(axis(n3));
     axes.push_back(axis(n4));
     axes.push_back(axis(n5));
     axes.push_back(axis(n6));
     axes.push_back(axis(n7));
     initAxes(axes);
}  
   /*!
  Initialize vector with length 
    \param n1 length of first axis
    \param n2 length of second axis
    \param n3 length of second axis
    \param n4 length of second axis
    \param n5 length of second axis
    \param n6 length of second axis
    \param n7 length of second axis

  */
  floatTensor(const int n1,const int n2,const int n3,const  int n4, const int n5, const int n6){
    std::vector<axis> axes:
     axes.push_back(axis(n1));
     axes.push_back(axis(n2));
    axes.push_back(axis(n3));
     axes.push_back(axis(n4));
     axes.push_back(axis(n5));
     axes.push_back(axis(n6));
     initAxes(axes);
}  
   /*!
  Initialize vector with length 
    \param n1 length of first axis
    \param n2 length of second axis
    \param n3 length of second axis
    \param n4 length of second axis
    \param n5 length of second axis
    \param n6 length of second axis

  */
  floatTensor(const int n1,const int n2,const int n3, const int n4, const int n5){
    std::vector<axis> axes:
     axes.push_back(axis(n1));
     axes.push_back(axis(n2));
    axes.push_back(axis(n3));
     axes.push_back(axis(n4));
     axes.push_back(axis(n5));
     initAxes(axes);
}  
   /*!
  Initialize vector with length 
    \param n1 length of first axis
    \param n2 length of second axis
    \param n3 length of second axis
    \param n4 length of second axis

  */
  floatTensor(const int n1,const int n2,const int n3, const int n4){
    std::vector<axis> axes:
     axes.push_back(axis(n1));
     axes.push_back(axis(n2));
    axes.push_back(axis(n3));
     axes.push_back(axis(n4));
     initAxes(axes);
}  
   /*!
  Initialize vector with length 
    \param n1 length of first axis
    \param n2 length of second axis
    \param n3 length of second axis

  */
  floatTensor(const int n1,const int n2,const int n3){
    std::vector<axis> axes:
     axes.push_back(axis(n1));
     axes.push_back(axis(n2));
    axes.push_back(axis(n3));
     initAxes(axes);
}  
  /*!
  Initialize vector with axes 
    \param axes List of axes

  */
  floatTensor(const std::vector<axis> axes){
    initAxes(axes);
  }
   /*!
   Initialize vector 
    \param hyper Hypercube

  */
  floatTensor(const std::shared_ptr<hypercube> hyper){
    initHyper(hyper);
  }
     /* 
    \param axes List of axes
    \param dat Pointer to data

  */
  floatTensor(const std::vector<axis> axes, const float *dat){
    initAxes(axes);
    initData(dat);
  }
     /* 
    \param hyper Hypercube
    \param dat Pointer to data

  */
  floatTensor(const std::shared_ptr<hypercube> hyper,const float *dat){
    initHyper(axes);
    initData(dat);
  }
  /*!
  Initialize data 

    \param data Binary stream to fill values with
  */
 void initData(const float *dat);
   /*
   Initialize from a hypercube

    \param hyper Hypercube associated with dataset
  */
 void initHyper(const std::shared_ptr<hypercube> hyper);
 /* 
     Clone a vector
  
  */
 std::shared_ptr<floatTensor> clone() const{
    auto x= std::shared_ptr<floatTensor> x(new floatTensor(getHyper(),getCVal()));
   return x;
 }
/* Clone vector space

*/
std::shared_ptr<floatTensor> cloneSpace() const;
  x=std::shared_ptr<floatTensor> x(new floatTensor(getHyper());
  x->setSpace();
  return x;
}

  /*!
     Return whether or not this just containing space information
  */
  bool getSpaceOnly() const { return _spaceOnly; }
  //! Add vector to another vector  self+=vec
  /*!
    \param vec Vector to add to the current vector
  */
  void add(std::shared_ptr<floatTensor> vec);

  //! Scale vector self*=scale
  /*!
    \param val What to scale vector by
  */
  void scale(const double val);

  //! Add to vector scaling each self=self*sc1+vec*sc2
  /*!
    \param sc1 What to scale current vector by
    \param vec2 Other vector to scale add to current vector
    \param sc2 What to scale the second vector by
  */

  void scaleAdd(std::shared_ptr<floatTensor> vec2, const double sc1,
                const double sc2);

  /*
    \param mn  Minimum value for histogram
    \param mx  Maximum value for histogram
    \param histo Number of elements in the histogram
   */
  void calcHisto(std::shared_ptr<int1DReg> &histo, float mn, float mx);
  //! Fill vector with random number

  void random() ;
  /*!
     Signum function

      if a!=0:
         a[]/|a[]|
  */
  void signum();
  /*!
     Multiply vector by another vector

     self*=vec2
  */
  void mult(std::shared_ptr<floatTensor> vec2);
  /*!  Return the dot product of current vec and another vec
     return SUM(this[]*vec2[])
     \param vec2 Vector to calculate the dot prodcut with
     */
  double dot(std::shared_ptr<floatTensor> vec2) const;
  /*!  Return the pct value of the dataset

      \param pct Percentage value to return
      \param j   Approximate the answer by ony taking every jth value

     */

  float cent(const float pct, const int j) const {
    long long iv = std::max(
        (long long)0, std::min((long long)(getHyper()->getN123() * pct / 100.),
                               getHyper()->getN123() - 1));
    return cent(iv, j);
  }
  /*!  Return the iv value of the dataset if sorted low to high

    \param iv  Value of sorted data to return
    \param j   Approximate the answer by ony taking every jth value

   */
  float cent(const long long iv, const int j) const;
  /*!
      Clip a dataset
          a[]=std::min(eclip,max(bclip,a[]))

          or

          a[]=std::max(eclip,min(bclip,a[]))

      \param  bclip Minimum value
      \param  eclip Maximum value
      \param  outer Whether to clip values larger or smaller than clip values

*/
  void clip(const float bclip, const float eclip, bool outer = true);
  /*!
    Clip a dataset value by value
        a[]=std::min(eclip[],max(bclip[],a[]))

    \param  bclip Minimum value
    \param  eclip Maximum value


*/
  void clipVector(const std::shared_ptr<floatTensor> bclip,
                  const std::shared_ptr<floatTensor> eclip);
  /*!
     Create a mask from a vector. Useful for filling in missing data.

     if  abs(a[]-zero) < err:
        a[]=0
     else
         a[]=1

      \param  zero Value in dataset that indicates unknown
      \param err   Error bounds indicating zero value
  */
  void createMask(const float zero, const float err);

  //! Calculate checksum for data

  void calcCheckSum() ;
  /*!  Store checksum va;iue

\param val Value of checksum to store
*/
  void setCheckSum(const uint64_t val) { _checkSum = val; }
  /*!
     Whether or not the current vector exists in a different space

     \param vec2 Vector space to compare to
  */
  bool isDifferent(std::shared_ptr<floatTensor> vec2) {
    calcCheckSum();
    vec2->calcCheckSum();
    if (vec2->getCheckSum() != getCheckSum())
      return true;
    return false;
  }
  /*!
     Return the norm of the dataset.
       1 - sum(fabs|a[]|)
       2 - 1/2(a[]*a[])

     \param nrm Norm to calculate
  */
  double norm(const int nrm) const;
  /*!
     Set the valule of vector to a given value

     \param val Value to set vector to
   */
  void set(const float val);
  /*!
Set the valule of vector to 0

*/
  void zero() { this->set(0.); }

  /*!
      Return the pointer to the memory for the vector
  */
  float *getVals() { return arr->data(); }
  /*!
    Return the pointer to the memory for the vector with const tag
*/
  const float *getCVals() const { return arr->data(); }
  /*! Apply a softclip to vector
     vec=sc*vec /sqrt(1+sc*sc*vec*vec)

     \param sc Value to use in softclip

 */
void softClip(const float sc) ;
  //! Return the absolute maximum value of vector

double absMax() const ;
  //! Return the  minimum value of vector

  double min() const;
  //! Return the  maximum value of vector

  double max() const;
  /*!  Return  information about vector (debugging)

 \param lev  Level of debugging information to provide
 \param str  Stream to add debugging info to
 */
  void infoStream(const int lev, std::stringstream &str) ;
  /*!  Check to see if current vector belongs to the same space as vec2

   \param vec2 Vector to check the space with
   */
  bool checkSame(const std::shared_ptr<SEP::floatTensor> vec2) const;
  ///! Return checksum value

  uint64_t getCheckSum() { return _checkSum; }


  bool spaceOnly(){
    return _spaceOnly;
  }
  const std::shared_ptr<hypercube> getHyper() const{
    return _hyper;
  }

private:

  void initAxes(const std::vector<axis> axes){
    std::shared_ptr<hypercube> hyper(new hypercube(axes));
    initHyper(hyper);
  }
  void setSpace(){
     _spaceOnly=True;
  }
  void initHyper(std::shared_ptr<hypercube> hyper);
  bool _spaceOnly;
  std::shared_ptr<hypercube> _hyper;
  std::shared_ptr<xt::xarray<float>> arr;
  uint64_t _checkSum; ///< Checksum value
};

} // namespace SEP
#endif
