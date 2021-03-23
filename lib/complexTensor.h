#ifndef complex_tensor_h
#define complex_tensor_h 1
#include "SEPException.h"
#include "Vector.h"
#include "complexHyper.h"
#include "regSpace.h"
#include "xtensor/xtensor.hpp"
#include <cstdint>
#include <hypercube.h>
#include <iostream>
#include <sstream>

/*!
  A regular sampled function that stores std::complex<float> values
*/
namespace SEP
{
    /*!
    A regular sampled 7-D function with std::complex<float> storage
    */
    class complexTensor7D : public complexHyper
    {
    public:
        /*!
         Create a 7-D std::complex<float> vector from a hypercube
              \param hyper Hypercube describing RSF

         */
        complexTensor7D(std::shared_ptr<SEP::hypercube> hyper)
        {
            initNoData(hyper);
        }
        /*!
       Create a 7-D std::complex<float> vector from just lengths
            \param n1,n2,n3,n4,n5,n6,n7 Dimensions of the hypercube

       */
        complexTensor7D(const int n1, const int n2, const int n3, const int n4,
                        const int n5, const int n6, const int n7)
        {
            std::vector<SEP::axis> a;
            std::vector<int> ns = {n1, n2, n3, n4, n5, n6, n7};
            for (int n : ns)
                a.push_back(n);
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
      Create a 7-D std::complex<float> vector from axes
          \param a1,a2,a3,a4,a5,a6, a7 Axes if the hypercube

      */
        complexTensor7D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
                        const SEP::axis &a4, const SEP::axis &a5, const SEP::axis &a6, const SEP::axis &a7)
        {
            std::vector<SEP::axis> a = {a1, a2, a3, a4, a5, a6, a7};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
       Create a 7-D std::complex<float> vector from a hypercube
            \param hyper Hypercube describing RSF
            \param vals Values to fill vector with

       */
        complexTensor7D(const std::shared_ptr<SEP::hypercube> hyper, const std::complex<float> *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
        /*!
      Create a 7-D std::complex<float> vector from just lengths
          \param n1,n2,n3,n4,n5,n6,n7 Dimensions of the hypercube
          \param vals Values to fill vector with

      */
        complexTensor7D(const int n1, const int n2, const int n3, const int n4,
                        const int n5, const int n6, const int n7, const std::complex<float> *vals)
        {
            std::vector<SEP::axis> a;
            std::vector<int> ns = {n1, n2, n3, n4, n5, n6, n7};
            for (int n : ns)
                a.push_back(n);

            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
            copyVals(vals);
        }
        /*!
       Create a 7-D std::complex<float> vector from axes
            \param a1,a2,a3,a4,a5,a6,a7 Axes if the hypercube
            \param vals Values to fill vector with
       */
        complexTensor7D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
                        const SEP::axis &a4, const SEP::axis &a5, const SEP::axis &a6, const SEP::axis &a7,
                        const std::complex<float> *vals)
        {
            std::vector<SEP::axis> a = {a1, a2, a3, a4, a5, a6, a7};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initData(hyp, vals);
        }
        /*!
           Allocate data for vector
           */
        void allocate()
        {
            std::vector<int> ns = getHyper()->getNs();
            xt::xtensor<std::complex<float>, 7>::shape_type shape = {(size_t)ns[6], (size_t)ns[5], (size_t)ns[4],
                                                                     (size_t)ns[3], (size_t)ns[2], (size_t)ns[1], (size_t)ns[0]};
            mat = xt::xtensor<std::complex<float>, 7>::from_shape(shape);
            setData(mat.data());
        }
        /*!
      Make a copy of the vector
      */
        std::shared_ptr<complexTensor7D> clone() const;
        /*!
       Make a copy of the vector space
       */
        std::shared_ptr<complexTensor7D> cloneSpace() const;
        /*!
                                        Return a subset of the vector
                                        \param nw,fw,jw Windowing parameters
                                        */
        std::shared_ptr<complexTensor7D> window(const std::vector<int> &nw,
                                                const std::vector<int> &fw,
                                                const std::vector<int> &jw) const;
        /*!
        Deallocate storage for vector, turn into vector space
         */
        virtual void cleanMemory()
        {
            mat = {{{{{{{0}}}}}}};
            setSpace();
        }
        xt::xtensor<std::complex<float>, 7> mat; ///< Storage for vector

    protected:
        /*!
        Initialize vector without providing data (zero)
        \param hyp Hypercube describing dataset
      */
        void initNoData(std::shared_ptr<SEP::hypercube> hyp);
        /*!
      Initialize with data
      \param hyper Hypercube describing space
      \param vals Data to copy in
      */
        void initData(std::shared_ptr<SEP::hypercube> hyper, const std::complex<float> *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
    };

    /*!
    A regular sampled 6-D function with std::complex<float> storage
    */
    class complexTensor6D : public complexHyper
    {
    public:
        /*!
         Create a 6-D std::complex<float> vector from a hypercube
              \param hyper Hypercube describing RSF

         */
        complexTensor6D(std::shared_ptr<SEP::hypercube> hyper)
        {
            initNoData(hyper);
        }
        /*!
       Create a 6-D std::complex<float> vector from just lengths
            \param n1,n2,n3,n4,n5,n6 Dimensions of the hypercube

       */
        complexTensor6D(const int n1, const int n2, const int n3, const int n4,
                        const int n5, const int n6)
        {
            std::vector<SEP::axis> a;
            std::vector<int> ns = {n1, n2, n3, n4, n5, n6};
            for (int n : ns)
                a.push_back(n);
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
      Create a 6-D std::complex<float> vector from axes
          \param a1,a2,a3,a4,a5,a6 Axes if the hypercube

      */
        complexTensor6D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
                        const SEP::axis &a4, const SEP::axis &a5, const SEP::axis &a6)
        {
            std::vector<SEP::axis> a = {a1, a2, a3, a4, a5, a6};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
       Create a 6-D std::complex<float> vector from a hypercube
            \param hyper Hypercube describing RSF
            \param vals Values to fill vector with

       */
        complexTensor6D(const std::shared_ptr<SEP::hypercube> hyper, const std::complex<float> *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
        /*!
      Create a 6-D std::complex<float> vector from just lengths
          \param n1,n2,n3,n4,n5,n6 Dimensions of the hypercube
          \param vals Values to fill vector with

      */
        complexTensor6D(const int n1, const int n2, const int n3, const int n4,
                        const int n5, const int n6, const std::complex<float> *vals)
        {
            std::vector<SEP::axis> a;
            std::vector<int> ns = {n1, n2, n3, n4, n5, n6};
            for (int n : ns)
                a.push_back(n);

            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
            copyVals(vals);
        }
        /*!
       Create a 6-D std::complex<float> vector from axes
            \param a1,a2,a3,a4,a5,a6 Axes if the hypercube
            \param vals Values to fill vector with
       */
        complexTensor6D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
                        const SEP::axis &a4, const SEP::axis &a5, const SEP::axis &a6,
                        const std::complex<float> *vals)
        {
            std::vector<SEP::axis> a = {a1, a2, a3, a4, a5, a6};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initData(hyp, vals);
        }
        /*!
           Allocate data for vector
           */
        void allocate()
        {
            std::vector<int> ns = getHyper()->getNs();
            xt::xtensor<std::complex<float>, 6>::shape_type shape = {(size_t)ns[5], (size_t)ns[4],
                                                                     (size_t)ns[3], (size_t)ns[2], (size_t)ns[1], (size_t)ns[0]};
            mat = xt::xtensor<std::complex<float>, 6>::from_shape(shape);
            setData(mat.data());
        }
        /*!
      Make a copy of the vector
      */
        std::shared_ptr<complexTensor6D> clone() const;
        /*!
       Make a copy of the vector space
       */
        std::shared_ptr<complexTensor6D> cloneSpace() const;
        /*!
                                        Return a subset of the vector
                                        \param nw,fw,jw Windowing parameters
                                        */
        std::shared_ptr<complexTensor6D> window(const std::vector<int> &nw,
                                                const std::vector<int> &fw,
                                                const std::vector<int> &jw) const;
        /*!
        Deallocate storage for vector, turn into vector space
         */
        virtual void cleanMemory()
        {
            mat = {{{{{{0}}}}}};
            setSpace();
        }
        xt::xtensor<std::complex<float>, 6> mat; ///< Storage for vector

    protected:
        /*!
        Initialize vector without providing data (zero)
        \param hyp Hypercube describing dataset
      */
        void initNoData(std::shared_ptr<SEP::hypercube> hyp);
        /*!
      Initialize with data
      \param hyper Hypercube describing space
      \param vals Data to copy in
      */
        void initData(std::shared_ptr<SEP::hypercube> hyper, const std::complex<float> *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
    };

    /*!
    A regular sampled 5-D function with std::complex<float> storage
    */
    class complexTensor5D : public complexHyper
    {
    public:
        /*!
         Create a 5-D std::complex<float> vector from a hypercube
              \param hyper Hypercube describing RSF

         */
        complexTensor5D(std::shared_ptr<SEP::hypercube> hyper)
        {
            initNoData(hyper);
        }
        /*!
       Create a 6-D std::complex<float> vector from just lengths
            \param n1,n2,n3,n4,n5  Dimensions of the hypercube

       */
        complexTensor5D(const int n1, const int n2, const int n3, const int n4,
                        const int n5)
        {
            std::vector<SEP::axis> a;
            std::vector<int> ns = {n1, n2, n3, n4, n5};
            for (int n : ns)
                a.push_back(n);
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
      Create a 6-D std::complex<float> vector from axes
          \param a1,a2,a3,a4,a5,a6 Axes if the hypercube

      */
        complexTensor5D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
                        const SEP::axis &a4, const SEP::axis &a5)
        {
            std::vector<SEP::axis> a = {a1, a2, a3, a4, a5};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
       Create a 5-D std::complex<float> vector from a hypercube
            \param hyper Hypercube describing RSF
            \param vals Values to fill vector with

       */
        complexTensor5D(const std::shared_ptr<SEP::hypercube> hyper, const std::complex<float> *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
        /*!
      Create a 5-D std::complex<float> vector from just lengths
          \param n1,n2,n3,n4,n5 Dimensions of the hypercube
          \param vals Values to fill vector with

      */
        complexTensor5D(const int n1, const int n2, const int n3, const int n4,
                        const int n5, const std::complex<float> *vals)
        {
            std::vector<SEP::axis> a;
            std::vector<int> ns = {n1, n2, n3, n4, n5};
            for (int n : ns)
                a.push_back(n);

            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
            copyVals(vals);
        }
        /*!
       Create a 5-D std::complex<float> vector from axes
            \param a1,a2,a3,a4,a5 Axes if the hypercube
            \param vals Values to fill vector with
       */
        complexTensor5D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
                        const SEP::axis &a4, const SEP::axis &a5,
                        const std::complex<float> *vals)
        {
            std::vector<SEP::axis> a = {a1, a2, a3, a4, a5};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initData(hyp, vals);
        }
        /*!
           Allocate data for vector
           */
        void allocate()
        {
            std::vector<int> ns = getHyper()->getNs();
            xt::xtensor<std::complex<float>, 5>::shape_type shape = {(size_t)ns[4],
                                                                     (size_t)ns[3], (size_t)ns[2], (size_t)ns[1], (size_t)ns[0]};
            mat = xt::xtensor<std::complex<float>, 5>::from_shape(shape);
            setData(mat.data());
        }
        /*!
      Make a copy of the vector
      */
        std::shared_ptr<complexTensor5D> clone() const;
        /*!
       Make a copy of the vector space
       */
        std::shared_ptr<complexTensor5D> cloneSpace() const;
        /*!
                                        Return a subset of the vector
                                        \param nw,fw,jw Windowing parameters
                                        */
        std::shared_ptr<complexTensor5D> window(const std::vector<int> &nw,
                                                const std::vector<int> &fw,
                                                const std::vector<int> &jw) const;
        /*!
        Deallocate storage for vector, turn into vector space
         */
        virtual void cleanMemory()
        {
            mat = {{{{{0}}}}};
            setSpace();
        }
        xt::xtensor<std::complex<float>, 5> mat; ///< Storage for vector

    protected:
        /*!
        Initialize vector without providing data (zero)
        \param hyp Hypercube describing dataset
      */
        void initNoData(std::shared_ptr<SEP::hypercube> hyp);
        /*!
      Initialize with data
      \param hyper Hypercube describing space
      \param vals Data to copy in
      */
        void initData(std::shared_ptr<SEP::hypercube> hyper, const std::complex<float> *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
    };

    /*!
    A regular sampled 4-D function with std::complex<float> storage
    */
    class complexTensor4D : public complexHyper
    {
    public:
        /*!
         Create a 4-D std::complex<float> vector from a hypercube
              \param hyper Hypercube describing RSF

         */
        complexTensor4D(std::shared_ptr<SEP::hypercube> hyper)
        {
            initNoData(hyper);
        }
        /*!
       Create a 4-D std::complex<float> vector from just lengths
            \param n1,n2,n3,n4 Dimensions of the hypercube

       */
        complexTensor4D(const int n1, const int n2, const int n3, const int n4)
        {
            std::vector<SEP::axis> a;
            std::vector<int> ns = {n1, n2, n3, n4};
            for (int n : ns)
                a.push_back(n);
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
      Create a 4-D std::complex<float> vector from axes
          \param a1,a2,a3,a4 Axes if the hypercube

      */
        complexTensor4D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
                        const SEP::axis &a4)
        {
            std::vector<SEP::axis> a = {a1, a2, a3, a4};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
       Create a 4-D std::complex<float> vector from a hypercube
            \param hyper Hypercube describing RSF
            \param vals Values to fill vector with

       */
        complexTensor4D(const std::shared_ptr<SEP::hypercube> hyper, const std::complex<float> *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
        /*!
      Create a 4-D std::complex<float> vector from just lengths
          \param n1,n2,n3,n4  Dimensions of the hypercube
          \param vals Values to fill vector with

      */
        complexTensor4D(const int n1, const int n2, const int n3, const int n4, const std::complex<float> *vals)
        {
            std::vector<SEP::axis> a;
            std::vector<int> ns = {n1, n2, n3, n4};
            for (int n : ns)
                a.push_back(n);

            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
            copyVals(vals);
        }
        /*!
       Create a 4-D std::complex<float> vector from axes
            \param a1,a2,a3,a4 Axes if the hypercube
            \param vals Values to fill vector with
       */
        complexTensor4D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
                        const SEP::axis &a4,
                        const std::complex<float> *vals)
        {
            std::vector<SEP::axis> a = {a1, a2, a3, a4};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initData(hyp, vals);
        }
        /*!
           Allocate data for vector
           */
        void allocate()
        {
            std::vector<int> ns = getHyper()->getNs();
            xt::xtensor<std::complex<float>, 4>::shape_type shape = {
                (size_t)ns[3], (size_t)ns[2], (size_t)ns[1], (size_t)ns[0]};
            mat = xt::xtensor<std::complex<float>, 4>::from_shape(shape);
            setData(mat.data());
        }
        /*!
      Make a copy of the vector
      */
        std::shared_ptr<complexTensor4D> clone() const;
        /*!
       Make a copy of the vector space
       */
        std::shared_ptr<complexTensor4D> cloneSpace() const;
        /*!
                                        Return a subset of the vector
                                        \param nw,fw,jw Windowing parameters
                                        */
        std::shared_ptr<complexTensor4D> window(const std::vector<int> &nw,
                                                const std::vector<int> &fw,
                                                const std::vector<int> &jw) const;
        /*!
        Deallocate storage for vector, turn into vector space
         */
        virtual void cleanMemory()
        {
            mat = {{{{0}}}};
            setSpace();
        }
        xt::xtensor<std::complex<float>, 4> mat; ///< Storage for vector

    protected:
        /*!
        Initialize vector without providing data (zero)
        \param hyp Hypercube describing dataset
      */
        void initNoData(std::shared_ptr<SEP::hypercube> hyp);
        /*!
      Initialize with data
      \param hyper Hypercube describing space
      \param vals Data to copy in
      */
        void initData(std::shared_ptr<SEP::hypercube> hyper, const std::complex<float> *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
    };

    /*!
    A regular sampled 3-D function with std::complex<float> storage
    */
    class complexTensor3D : public complexHyper
    {
    public:
        /*!
         Create a 3-D std::complex<float> vector from a hypercube
              \param hyper Hypercube describing RSF

         */
        complexTensor3D(std::shared_ptr<SEP::hypercube> hyper)
        {
            initNoData(hyper);
        }
        /*!
       Create a 3-D std::complex<float> vector from just lengths
            \param n1,n2,n3  Dimensions of the hypercube

       */
        complexTensor3D(const int n1, const int n2, const int n3)
        {
            std::vector<SEP::axis> a;
            std::vector<int> ns = {n1, n2, n3};
            for (int n : ns)
                a.push_back(n);
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
      Create a 3-D std::complex<float> vector from axes
          \param a1,a2,a3  Axes if the hypercube

      */
        complexTensor3D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3)
        {
            std::vector<SEP::axis> a = {a1, a2, a3};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
       Create a 3-D std::complex<float> vector from a hypercube
            \param hyper Hypercube describing RSF
            \param vals Values to fill vector with

       */
        complexTensor3D(const std::shared_ptr<SEP::hypercube> hyper, const std::complex<float> *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
        /*!
      Create a 3-D std::complex<float> vector from just lengths
          \param n1,n2,n3   Dimensions of the hypercube
          \param vals Values to fill vector with

      */
        complexTensor3D(const int n1, const int n2, const int n3, const std::complex<float> *vals)
        {
            std::vector<SEP::axis> a;
            std::vector<int> ns = {n1, n2, n3};
            for (int n : ns)
                a.push_back(n);

            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
            copyVals(vals);
        }
        /*!
       Create a 3-D std::complex<float> vector from axes
            \param a1,a2,a3 Axes if the hypercube
            \param vals Values to fill vector with
       */
        complexTensor3D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
                        const std::complex<float> *vals)
        {
            std::vector<SEP::axis> a = {a1, a2, a3};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initData(hyp, vals);
        }
        /*!
           Allocate data for vector
           */
        void allocate()
        {
            std::vector<int> ns = getHyper()->getNs();
            xt::xtensor<std::complex<float>, 3>::shape_type shape = {
                (size_t)ns[2], (size_t)ns[1], (size_t)ns[0]};
            mat = xt::xtensor<std::complex<float>, 3>::from_shape(shape);
            setData(mat.data());
        }
        /*!
      Make a copy of the vector
      */
        std::shared_ptr<complexTensor3D> clone() const;
        /*!
       Make a copy of the vector space
       */
        std::shared_ptr<complexTensor3D> cloneSpace() const;
        /*!
                                        Return a subset of the vector
                                        \param nw,fw,jw Windowing parameters
                                        */
        std::shared_ptr<complexTensor3D> window(const std::vector<int> &nw,
                                                const std::vector<int> &fw,
                                                const std::vector<int> &jw) const;
        /*!
        Deallocate storage for vector, turn into vector space
         */
        virtual void cleanMemory()
        {
            mat = {{{{0}}}};
            setSpace();
        }
        xt::xtensor<std::complex<float>, 3> mat; ///< Storage for vector

    protected:
        /*!
        Initialize vector without providing data (zero)
        \param hyp Hypercube describing dataset
      */
        void initNoData(std::shared_ptr<SEP::hypercube> hyp);
        /*!
      Initialize with data
      \param hyper Hypercube describing space
      \param vals Data to copy in
      */
        void initData(std::shared_ptr<SEP::hypercube> hyper, const std::complex<float> *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
    };

    /*!
    A regular sampled 2-D function with std::complex<float> storage
    */
    class complexTensor2D : public complexHyper
    {
    public:
        /*!
         Create a 2-D std::complex<float> vector from a hypercube
              \param hyper Hypercube describing RSF

         */
        complexTensor2D(std::shared_ptr<SEP::hypercube> hyper)
        {
            initNoData(hyper);
        }

        /*!
          Create a 2-D std::complex<float> vector from a 7-D std::complex<float>

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param iax2 - Second axis
          \param rev2 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        complexTensor2D(const std::shared_ptr<complexTensor7D> old, const int iax1,
                        const bool rev1, const int iax2, const bool rev2,
                        const std::vector<int> &ipos, const std::vector<int> &beg,
                        const std::vector<int> &end);

        /*!
          Create a 2-D std::complex<float> vector from a 6-D std::complex<float>

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param iax2 - Second axis
          \param rev2 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        complexTensor2D(const std::shared_ptr<complexTensor6D> old, const int iax1,
                        const bool rev1, const int iax2, const bool rev2,
                        const std::vector<int> &ipos, const std::vector<int> &beg,
                        const std::vector<int> &end);

        /*!
          Create a 2-D std::complex<float> vector from a 5-D std::complex<float>

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param iax2 - Second axis
          \param rev2 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        complexTensor2D(const std::shared_ptr<complexTensor5D> old, const int iax1,
                        const bool rev1, const int iax2, const bool rev2,
                        const std::vector<int> &ipos, const std::vector<int> &beg,
                        const std::vector<int> &end);

        /*!
          Create a 2-D std::complex<float> vector from a 4-D std::complex<float>

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param iax2 - Second axis
          \param rev2 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        complexTensor2D(const std::shared_ptr<complexTensor4D> old, const int iax1,
                        const bool rev1, const int iax2, const bool rev2,
                        const std::vector<int> &ipos, const std::vector<int> &beg,
                        const std::vector<int> &end);

        /*!
          Create a 2-D std::complex<float> vector from a 3-D std::complex<float>

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param iax2 - Second axis
          \param rev2 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        complexTensor2D(const std::shared_ptr<complexTensor3D> old, const int iax1,
                        const bool rev1, const int iax2, const bool rev2,
                        const std::vector<int> &ipos, const std::vector<int> &beg,
                        const std::vector<int> &end);

        /*!
          Create a 2-D std::complex<float> vector from a 2-D std::complex<float>

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param iax2 - Second axis
          \param rev2 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        complexTensor2D(const std::shared_ptr<complexTensor2D> old, const int iax1,
                        const bool rev1, const int iax2, const bool rev2,
                        const std::vector<int> &ipos, const std::vector<int> &beg,
                        const std::vector<int> &end);

        /*!
       Create a 2-D std::complex<float> vector from just lengths
            \param n1,n2   Dimensions of the hypercube

       */
        complexTensor2D(const int n1, const int n2)
        {
            std::vector<SEP::axis> a;
            std::vector<int> ns = {n1, n2};
            for (int n : ns)
                a.push_back(n);
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }

        /*!
      Create a 2-D std::complex<float> vector from axes
          \param a1,a2  Axes if the hypercube

      */
        complexTensor2D(const SEP::axis &a1, const SEP::axis &a2)
        {
            std::vector<SEP::axis> a = {a1, a2};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
       Create a 2-D std::complex<float> vector from a hypercube
            \param hyper Hypercube describing RSF
            \param vals Values to fill vector with

       */
        complexTensor2D(const std::shared_ptr<SEP::hypercube> hyper, const std::complex<float> *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
        /*!
      Create a 2-D std::complex<float> vector from just lengths
          \param n1,n2   Dimensions of the hypercube
          \param vals Values to fill vector with

      */
        complexTensor2D(const int n1, const int n2, const std::complex<float> *vals)
        {
            std::vector<SEP::axis> a;
            std::vector<int> ns = {n1, n2};
            for (int n : ns)
                a.push_back(n);

            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
            copyVals(vals);
        }
        /*!
       Create a 2-D std::complex<float> vector from axes
            \param a1,a2  Axes if the hypercube
            \param vals Values to fill vector with
       */
        complexTensor2D(const SEP::axis &a1, const SEP::axis &a2,
                        const std::complex<float> *vals)
        {
            std::vector<SEP::axis> a = {a1, a2};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initData(hyp, vals);
        }
        /*!
           Allocate data for vector
           */
        void allocate()
        {
            std::vector<int> ns = getHyper()->getNs();
            xt::xtensor<std::complex<float>, 2>::shape_type shape = {
                (size_t)ns[1], (size_t)ns[0]};
            mat = xt::xtensor<std::complex<float>, 2>::from_shape(shape);
            setData(mat.data());
        }
        /*!
      Make a copy of the vector
      */
        std::shared_ptr<complexTensor2D> clone() const;
        /*!
       Make a copy of the vector space
       */
        std::shared_ptr<complexTensor2D> cloneSpace() const;
        /*!
                                        Return a subset of the vector
                                        \param nw,fw,jw Windowing parameters
                                        */
        std::shared_ptr<complexTensor2D> window(const std::vector<int> &nw,
                                                const std::vector<int> &fw,
                                                const std::vector<int> &jw) const;
        /*!
        Deallocate storage for vector, turn into vector space
         */
        virtual void cleanMemory()
        {
            mat = {{{{0}}}};
            setSpace();
        }
        xt::xtensor<std::complex<float>, 2> mat; ///< Storage for vector

    protected:
        /*!
        Initialize vector without providing data (zero)
        \param hyp Hypercube describing dataset
      */
        void initNoData(std::shared_ptr<SEP::hypercube> hyp);
        /*!
      Initialize with data
      \param hyper Hypercube describing space
      \param vals Data to copy in
      */
        void initData(std::shared_ptr<SEP::hypercube> hyper, const std::complex<float> *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
    };

    /*!
    A regular sampled 1-D function with std::complex<float> storage
    */
    class complexTensor1D : public complexHyper
    {
    public:
        /*!
         Create a 1-D std::complex<float> vector from a hypercube
              \param hyper Hypercube describing RSF

         */
        complexTensor1D(std::shared_ptr<SEP::hypercube> hyper)
        {
            initNoData(hyper);
        }
        /*!
       Create a 1-D std::complex<float> vector from just lengths
            \param n1   Dimensions of the hypercube

       */
        complexTensor1D(const int n1)
        {
            std::vector<SEP::axis> a;
            std::vector<int> ns = {n1};
            for (int n : ns)
                a.push_back(n);
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }

        /*!
      Create a 1-D std::complex<float> vector from axes
          \param a1   Axes if the hypercube

      */
        complexTensor1D(const SEP::axis &a1)
        {
            std::vector<SEP::axis> a = {a1};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
       Create a 1-D std::complex<float> vector from a hypercube
            \param hyper Hypercube describing RSF
            \param vals Values to fill vector with

       */
        complexTensor1D(const std::shared_ptr<SEP::hypercube> hyper, const std::complex<float> *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }

        /*!
          Create a 1-D std::complex<float> vector from a 2-D std::complex<float>

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        complexTensor1D(const std::shared_ptr<complexTensor2D> old, const int iax1,
                        const bool rev1,
                        const std::vector<int> &ipos, const std::vector<int> &beg,
                        const std::vector<int> &end);

        /*!
          Create a 1-D std::complex<float> vector from a 3-D std::complex<float>

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        complexTensor1D(const std::shared_ptr<complexTensor3D> old, const int iax1,
                        const bool rev1,
                        const std::vector<int> &ipos, const std::vector<int> &beg,
                        const std::vector<int> &end);
        /*!
          Create a 1-D std::complex<float> vector from a 4-D std::complex<float>

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        complexTensor1D(const std::shared_ptr<complexTensor4D> old, const int iax1,
                        const bool rev1,
                        const std::vector<int> &ipos, const std::vector<int> &beg,
                        const std::vector<int> &end);
        /*!
          Create a 1-D std::complex<float> vector from a 1-D std::complex<float>

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        complexTensor1D(const std::shared_ptr<complexTensor1D> old, const int iax1,
                        const bool rev1,
                        const std::vector<int> &ipos, const std::vector<int> &beg,
                        const std::vector<int> &end);
        /*!
          Create a 1-D std::complex<float> vector from a 5-D std::complex<float>

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        complexTensor1D(const std::shared_ptr<complexTensor5D> old, const int iax1,
                        const bool rev1,
                        const std::vector<int> &ipos, const std::vector<int> &beg,
                        const std::vector<int> &end);
        /*!
          Create a 1-D std::complex<float> vector from a 6-D std::complex<float>

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        complexTensor1D(const std::shared_ptr<complexTensor6D> old, const int iax1,
                        const bool rev1,
                        const std::vector<int> &ipos, const std::vector<int> &beg,
                        const std::vector<int> &end);
        /*!
          Create a 1-D std::complex<float> vector from a 7-D std::complex<float>

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        complexTensor1D(const std::shared_ptr<complexTensor7D> old, const int iax1,
                        const bool rev1,
                        const std::vector<int> &ipos, const std::vector<int> &beg,
                        const std::vector<int> &end);

        /*!
      Create a 1-D std::complex<float> vector from just lengths
          \param n1    Dimensions of the hypercube
          \param vals Values to fill vector with

      */
        complexTensor1D(const int n1, const std::complex<float> *vals)
        {
            std::vector<SEP::axis> a;
            std::vector<int> ns = {n1};
            for (int n : ns)
                a.push_back(n);

            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
            copyVals(vals);
        }
        /*!
       Create a 1-D std::complex<float> vector from axes
            \param a1   Axes if the hypercube
            \param vals Values to fill vector with
       */
        complexTensor1D(const SEP::axis &a1,
                        const std::complex<float> *vals)
        {
            std::vector<SEP::axis> a = {a1};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initData(hyp, vals);
        }
        /*!
           Allocate data for vector
           */
        void allocate()
        {
            std::vector<int> ns = getHyper()->getNs();
            xt::xtensor<std::complex<float>, 1>::shape_type shape = {
                (size_t)ns[0]};
            mat = xt::xtensor<std::complex<float>, 1>::from_shape(shape);
            setData(mat.data());
        }
        /*!
      Make a copy of the vector
      */
        std::shared_ptr<complexTensor1D> clone() const;
        /*!
       Make a copy of the vector space
       */
        std::shared_ptr<complexTensor1D> cloneSpace() const;
        /*!
                                        Return a subset of the vector
                                        \param nw,fw,jw Windowing parameters
                                        */
        std::shared_ptr<complexTensor1D> window(const std::vector<int> &nw,
                                                const std::vector<int> &fw,
                                                const std::vector<int> &jw) const;
        /*!
        Deallocate storage for vector, turn into vector space
         */
        virtual void cleanMemory()
        {
            mat = {0};
            setSpace();
        }
        xt::xtensor<std::complex<float>, 1> mat; ///< Storage for vector

    protected:
        /*!
        Initialize vector without providing data (zero)
        \param hyp Hypercube describing dataset
      */
        void initNoData(std::shared_ptr<SEP::hypercube> hyp);
        /*!
      Initialize with data
      \param hyper Hypercube describing space
      \param vals Data to copy in
      */
        void initData(std::shared_ptr<SEP::hypercube> hyper, const std::complex<float> *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
    };

} // namespace SEP

#endif