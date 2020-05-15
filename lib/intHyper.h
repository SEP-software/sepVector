#ifndef int_hyper_h
#define int_hyper_h 1
#include <hypercube.h>
#include <cstdint>
#include <sstream>
#include "regSpace.h"
namespace SEP {
/*!
  A regular sampled function that stores int values. Storage is actually done
  in inherited classes (1-D,2-D,3-D)
*/
class intHyper : public regSpace {
 public:
  /*!
Initializer for intHyper class. Only used by inherited class
*/
  intHyper() { ; }
  /*!
     Return whether or not this just containing space information
  */
  bool getSpaceOnly() const { return _spaceOnly; }
  //! Add vector to another vector  self+=vec
  /*!
    \param vec Vector to add to the current vector
  */
   void add(std::shared_ptr<intHyper> vec);
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
   void scaleAdd(std::shared_ptr<intHyper> vec2, const double sc1,
                        const double sc2);
  //! Fill vector with random number
   void random();
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
   void mult(std::shared_ptr<intHyper> vec2);
  /*!  Return the dot product of current vec and another vec
   return SUM(this[]*vec2[])
   \param vec2 Vector to calculate the dot prodcut with
   */
   double dot(std::shared_ptr<intHyper> vec2) const;
  /*!  Set that this is only vector space with no storage
   */
   void setSpace() { _spaceOnly = true; }
  /*!  Set that this has storage along with the vector sapce
   */
   void setNotSpace() { _spaceOnly = false; }
  /*!
   Create a mask from a vector. Useful for filling in missing data.

   if  abs(a[]-zero) < err:
      a[]=0
   else
       a[]=1

    \param  zero Value in dataset that indicates unknown
    \param err   Error bounds indicating zero value
*/
  void createMask(const int zero, const int err);
  /*!
   Set a pointer to the storage for the dataset.
   Storage is handled by child classes.

   \param ptr  Pointer to allocated memory
*/
  void setData(int *ptr) {
    _vals = ptr;
    setNotSpace();
    setMemPtr((void *)ptr, sizeof(int));
  }
  /*!  Return the pct value of the dataset

    \param pct Percentage value to return
    \param j   Approximate the answer by ony taking every jth value

   */
  int cent(const float pct, const int j) const {
    long long iv = std::max(
        (long long)0, std::min((long long)(getHyper()->getN123() * pct / 100.),
                               getHyper()->getN123() - 1));
    return cent(iv, j);
  }
  /*!  Return the iv value of the dataset if sorted low to high

  \param iv  Value of sorted data to return
  \param j   Approximate the answer by ony taking every jth value

 */
  int cent(const long long iv, const int j) const;
  /*!
    Clip a dataset
        a[]=std::min(eclip,max(bclip,a[]))

        or

        a[]=std::max(eclip,min(bclip,a[]))

    \param  bclip Minimum value
    \param  eclip Maximum value

*/
  void clip(const int bclip, const int eclip);
  //! Calculate checksum for data

  void calcCheckSum();
  /*!  Store checksum va;iue

\param val Value of checksum to store
*/
  void setCheckSum(const uint64_t val) { _checkSum = val; }
  /*!
   Whether or not the current vector exists in a different space

   \param vec2 Vector space to compare to
*/
  bool isDifferent(std::shared_ptr<intHyper> vec2) {
    calcCheckSum();
    if (vec2->getCheckSum() != getCheckSum()) return true;
    return false;
  }
  /*!
     Return the norm of the dataset.
       1 - sum(|a[]|)
       2 - 1/2(a[]*a[])

     \param nrm Norm to calculate
  */
  long long norm(const int nrm) const;
  /*!
   Set the valule of vector to a given value

   \param val Value to set vector to
 */
  void set(const int val);
  /*!
Set the valule of vector to 0

*/
  void zero() { set(0); }
  /*!
      Return the pointer to the memory for the vector
  */
  int *getVals() { return _vals; }
  /*!
  Return the pointer to the memory for the vector with const tag
*/
  const int *getCVals() const { return _vals; }
  /*! Apply a softclip to vector
   vec=sc*vec /sqrt(1+sc*sc*vec*vec)

   \param sc Value to use in softclip
*/
   void softClip(const float sc);
  //! Return the absolute maximum value of vector

   int absMax() const;
  //! Return the  minimum value of vector

  int min() const;
  //! Return the  maximum value of vector

  int max() const;
  /*!  Return  information about vector (debugging)

\param lev  Level of debugging information to provide
\param str  Stream to add debugging info to
*/
   void infoStream(const int lev, std::stringstream &str);
  /*!  Check to see if current vector belongs to the same space as vec2

 \param vec2 Vector to check the space with
 */

   bool checkSame(const std::shared_ptr<SEP::intHyper> vec2) const;
  ///! Return checksum value

  uint64_t getCheckSum() { return _checkSum; }

  bool _spaceOnly;       ///< Whether or not vector is only vector space
  std::string _vecType;  ///< Name for vector type

 private:
  int *_vals;          ///< Storage for vector
  uint64_t _checkSum;  ///< Checksum value
};

}  // namespace SEP
#endif
