#ifndef complex_hyper_h
#define complex_hyper_h 1
#include <hypercube.h>
#include <complex>
#include <cstdint>
#include <sstream>
#include "regSpace.h"

namespace SEP {
/*!
  A regular sampled function that stores complex float values. Storage is
  actually done in inherited classes (1-D,2-D,3-D)
*/
class complexHyper : public regSpace {
 public:
  /*!
Initializer for complexHyper class. Only used by inherited class
*/
  complexHyper() { ; }
  /*!
     Return whether or not this just containing space information
  */
  bool getSpaceOnly() const { return _spaceOnly; }
  //! Add vector to another vector  self+=vec
  /*!
    \param vec Vector to add to the current vector
  */
  virtual void add(std::shared_ptr<complexHyper> vec);
  //! Fill vector with random number
  virtual void random();
  /*!
   Multiply vector by another vector

   self*=vec2
*/
  virtual void mult(std::shared_ptr<complexHyper> vec2);
  /*!
   Set a pointer to the storage for the dataset.
   Storage is handled by child classes.

   \param ptr  Pointer to allocated memory
*/
  void setData(std::complex<float> *ptr) {
    _vals = ptr;
    setNotSpace();
    setMemPtr((void *)ptr, sizeof(std::complex<float>));
  }
  /*!  Set that this is only vector space with no storage
   */
  virtual void setSpace() { _spaceOnly = true; }
  /*!  Set that this has storage along with the vector sapce
   */
  virtual void setNotSpace() { _spaceOnly = false; }
  /*!
   Return whether or not this just containing space information
*/
  inline bool getSpaceOnly() const { return _spaceOnly; }
  //! Calculate checksum for data

  void calcCheckSum();
  /*!  Store checksum va;iue

\param val Value of checksum to store
*/
  void setCheckSum(const uint64_t x) { _checkSum = x; }
  /*!
   Whether or not the current vector exists in a different space

   \param vec2 Vector space to compare to
*/
  bool isDifferent(std::shared_ptr<complexHyper> vec2) {
    calcCheckSum();
    if (vec2->getCheckSum() != getCheckSum()) return true;
    return false;
  }
  /*!
Set the valule of vector to 0

*/
  void zero() {
    std::complex<float> val = {0., 0.};
    set(val);
  }
  /*!
   Set the valule of vector to a given value

   \param val Value to set vector to
 */
  void set(const std::complex<float> val);
  /*!
      Return the pointer to the memory for the vector
  */
  std::complex<float> *getVals() { return _vals; }
  /*!
  Return the pointer to the memory for the vector with const tag
*/
  const std::complex<float> *getCVals() const { return _vals; }
  /*!  Return  information about vector (debugging)

 \param lev  Level of debugging information to provide
 \param str  Stream to add debugging info to
 */
  virtual void infoStream(const int lev, std::stringstream &x);
  /*!  Check to see if current vector belongs to the same space as vec2

 \param vec2 Vector to check the space with
 */

  virtual bool checkSame(const std::shared_ptr<SEP::complexHyper> vec2) const;
  ///! Return checksum value

  uint64_t getCheckSum() { return _checkSum; }
  std::string _vecType;  ///< Name for vector type

 private:
  std::complex<float> *_vals;  ///< Storage for vector
  bool _spaceOnly;             ///< Whether or not vector is only vector space

  uint64_t _checkSum;  ///< Checksum value
};

}  // namespace SEP
#endif
