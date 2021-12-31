#ifndef int_tensor_h
#define int_tensor_h 1
#include "SEPException.h"
#include "Vector.h"
#include "longHyper.h"
#include "regSpace.h"
#include "xtensor/xtensor.hpp"
#include <cstdint>
#include <hypercube.h>
#include <iostream>
#include <sstream>

/*!
  A regular sampled function that stores int values
*/
namespace SEP
{
    /*!
    A regular sampled 7-D function with int storage
    */
    class longTensor7D : public longHyper
    {
    public:
        /*!
         Create a 7-D long vector from a hypercube
              \param hyper Hypercube describing RSF

         */
        longTensor7D(std::shared_ptr<SEP::hypercube> hyper)
        {
            initNoData(hyper);
        }
        /*!
       Create a 7-D int vector from just lengths
            \param n1,n2,n3,n4,n5,n6,n7 Dimensions of the hypercube

       */
        longTensor7D(const int n1, const int n2, const int n3, const int n4,
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
      Create a 7-D int vector from axes
          \param a1,a2,a3,a4,a5,a6, a7 Axes if the hypercube

      */
        longTensor7D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
                    const SEP::axis &a4, const SEP::axis &a5, const SEP::axis &a6, const SEP::axis &a7)
        {
            std::vector<SEP::axis> a = {a1, a2, a3, a4, a5, a6, a7};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
       Create a 7-D int vector from a hypercube
            \param hyper Hypercube describing RSF
            \param vals Values to fill vector with

       */
        longTensor7D(const std::shared_ptr<SEP::hypercube> hyper, const long long *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
        /*!
      Create a 7-D int vector from just lengths
          \param n1,n2,n3,n4,n5,n6,n7 Dimensions of the hypercube
          \param vals Values to fill vector with

      */
        longTensor7D(const int n1, const int n2, const int n3, const int n4,
                    const int n5, const int n6, const int n7, const long long *vals)
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
       Create a 7-D int vector from axes
            \param a1,a2,a3,a4,a5,a6,a7 Axes if the hypercube
            \param vals Values to fill vector with
       */
        longTensor7D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
                    const SEP::axis &a4, const SEP::axis &a5, const SEP::axis &a6, const SEP::axis &a7,
                    const long long *vals)
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
            xt::xtensor<long long, 7>::shape_type shape = {(size_t)ns[6], (size_t)ns[5], (size_t)ns[4],
                                                     (size_t)ns[3], (size_t)ns[2], (size_t)ns[1], (size_t)ns[0]};
            mat = xt::xtensor<long long, 7>::from_shape(shape);
            setData(mat.data());
        }
        /*!
      Make a copy of the vector
      */
        std::shared_ptr<longTensor7D> clone() const;
        /*!
       Make a copy of the vector space
       */
        std::shared_ptr<longTensor7D> cloneSpace() const;
        /*!
                                        Return a subset of the vector
                                        \param nw,fw,jw Windowing parameters
                                        */
        std::shared_ptr<longTensor7D> window(const std::vector<int> &nw,
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
        xt::xtensor<long long, 7> mat; ///< Storage for vector

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
        void initData(std::shared_ptr<SEP::hypercube> hyper, const long long *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
    };

    /*!
    A regular sampled 6-D function with int storage
    */
    class longTensor6D : public longHyper
    {
    public:
        /*!
         Create a 6-D int vector from a hypercube
              \param hyper Hypercube describing RSF

         */
        longTensor6D(std::shared_ptr<SEP::hypercube> hyper)
        {
            initNoData(hyper);
        }
        /*!
       Create a 6-D int vector from just lengths
            \param n1,n2,n3,n4,n5,n6 Dimensions of the hypercube

       */
        longTensor6D(const int n1, const int n2, const int n3, const int n4,
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
      Create a 6-D int vector from axes
          \param a1,a2,a3,a4,a5,a6 Axes if the hypercube

      */
        longTensor6D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
                    const SEP::axis &a4, const SEP::axis &a5, const SEP::axis &a6)
        {
            std::vector<SEP::axis> a = {a1, a2, a3, a4, a5, a6};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
       Create a 6-D int vector from a hypercube
            \param hyper Hypercube describing RSF
            \param vals Values to fill vector with

       */
        longTensor6D(const std::shared_ptr<SEP::hypercube> hyper, const long long *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
        /*!
      Create a 6-D int vector from just lengths
          \param n1,n2,n3,n4,n5,n6 Dimensions of the hypercube
          \param vals Values to fill vector with

      */
        longTensor6D(const int n1, const int n2, const int n3, const int n4,
                    const int n5, const int n6, const long long *vals)
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
       Create a 6-D int vector from axes
            \param a1,a2,a3,a4,a5,a6 Axes if the hypercube
            \param vals Values to fill vector with
       */
        longTensor6D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
                    const SEP::axis &a4, const SEP::axis &a5, const SEP::axis &a6,
                    const long long *vals)
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
            xt::xtensor<long long, 6>::shape_type shape = {(size_t)ns[5], (size_t)ns[4],
                                                     (size_t)ns[3], (size_t)ns[2], (size_t)ns[1], (size_t)ns[0]};
            mat = xt::xtensor<long long, 6>::from_shape(shape);
            setData(mat.data());
        }
        /*!
      Make a copy of the vector
      */
        std::shared_ptr<longTensor6D> clone() const;
        /*!
       Make a copy of the vector space
       */
        std::shared_ptr<longTensor6D> cloneSpace() const;
        /*!
                                        Return a subset of the vector
                                        \param nw,fw,jw Windowing parameters
                                        */
        std::shared_ptr<longTensor6D> window(const std::vector<int> &nw,
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
        xt::xtensor<long long, 6> mat; ///< Storage for vector

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
        void initData(std::shared_ptr<SEP::hypercube> hyper, const long long *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
    };

    /*!
    A regular sampled 5-D function with int storage
    */
    class longTensor5D : public longHyper
    {
    public:
        /*!
         Create a 5-D int vector from a hypercube
              \param hyper Hypercube describing RSF

         */
        longTensor5D(std::shared_ptr<SEP::hypercube> hyper)
        {
            initNoData(hyper);
        }
        /*!
       Create a 6-D int vector from just lengths
            \param n1,n2,n3,n4,n5  Dimensions of the hypercube

       */
        longTensor5D(const int n1, const int n2, const int n3, const int n4,
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
      Create a 6-D int vector from axes
          \param a1,a2,a3,a4,a5,a6 Axes if the hypercube

      */
        longTensor5D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
                    const SEP::axis &a4, const SEP::axis &a5)
        {
            std::vector<SEP::axis> a = {a1, a2, a3, a4, a5};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
       Create a 5-D int vector from a hypercube
            \param hyper Hypercube describing RSF
            \param vals Values to fill vector with

       */
        longTensor5D(const std::shared_ptr<SEP::hypercube> hyper, const long long *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
        /*!
      Create a 5-D int vector from just lengths
          \param n1,n2,n3,n4,n5 Dimensions of the hypercube
          \param vals Values to fill vector with

      */
        longTensor5D(const int n1, const int n2, const int n3, const int n4,
                    const int n5, const long long *vals)
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
       Create a 5-D int vector from axes
            \param a1,a2,a3,a4,a5 Axes if the hypercube
            \param vals Values to fill vector with
       */
        longTensor5D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
                    const SEP::axis &a4, const SEP::axis &a5,
                    const long long *vals)
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
            xt::xtensor<long long, 5>::shape_type shape = {(size_t)ns[4],
                                                     (size_t)ns[3], (size_t)ns[2], (size_t)ns[1], (size_t)ns[0]};
            mat = xt::xtensor<long long, 5>::from_shape(shape);
            setData(mat.data());
        }
        /*!
      Make a copy of the vector
      */
        std::shared_ptr<longTensor5D> clone() const;
        /*!
       Make a copy of the vector space
       */
        std::shared_ptr<longTensor5D> cloneSpace() const;
        /*!
                                        Return a subset of the vector
                                        \param nw,fw,jw Windowing parameters
                                        */
        std::shared_ptr<longTensor5D> window(const std::vector<int> &nw,
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
        xt::xtensor<long long, 5> mat; ///< Storage for vector

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
        void initData(std::shared_ptr<SEP::hypercube> hyper, const long long *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
    };

    /*!
    A regular sampled 4-D function with int storage
    */
    class longTensor4D : public longHyper
    {
    public:
        /*!
         Create a 4-D int vector from a hypercube
              \param hyper Hypercube describing RSF

         */
        longTensor4D(std::shared_ptr<SEP::hypercube> hyper)
        {
            initNoData(hyper);
        }
        /*!
       Create a 4-D int vector from just lengths
            \param n1,n2,n3,n4 Dimensions of the hypercube

       */
        longTensor4D(const int n1, const int n2, const int n3, const int n4)
        {
            std::vector<SEP::axis> a;
            std::vector<int> ns = {n1, n2, n3, n4};
            for (int n : ns)
                a.push_back(n);
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
      Create a 4-D int vector from axes
          \param a1,a2,a3,a4 Axes if the hypercube

      */
        longTensor4D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
                    const SEP::axis &a4)
        {
            std::vector<SEP::axis> a = {a1, a2, a3, a4};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
       Create a 4-D int vector from a hypercube
            \param hyper Hypercube describing RSF
            \param vals Values to fill vector with

       */
        longTensor4D(const std::shared_ptr<SEP::hypercube> hyper, const long long *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
        /*!
      Create a 4-D int vector from just lengths
          \param n1,n2,n3,n4  Dimensions of the hypercube
          \param vals Values to fill vector with

      */
        longTensor4D(const int n1, const int n2, const int n3, const int n4, const long long *vals)
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
       Create a 4-D int vector from axes
            \param a1,a2,a3,a4 Axes if the hypercube
            \param vals Values to fill vector with
       */
        longTensor4D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
                    const SEP::axis &a4,
                    const long long *vals)
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
            xt::xtensor<long long, 4>::shape_type shape = {
                (size_t)ns[3], (size_t)ns[2], (size_t)ns[1], (size_t)ns[0]};
            mat = xt::xtensor<long long, 4>::from_shape(shape);
            setData(mat.data());
        }
        /*!
      Make a copy of the vector
      */
        std::shared_ptr<longTensor4D> clone() const;
        /*!
       Make a copy of the vector space
       */
        std::shared_ptr<longTensor4D> cloneSpace() const;
        /*!
                                        Return a subset of the vector
                                        \param nw,fw,jw Windowing parameters
                                        */
        std::shared_ptr<longTensor4D> window(const std::vector<int> &nw,
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
        xt::xtensor<long long, 4> mat; ///< Storage for vector

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
        void initData(std::shared_ptr<SEP::hypercube> hyper, const long long *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
    };

    /*!
    A regular sampled 3-D function with int storage
    */
    class longTensor3D : public longHyper
    {
    public:
        /*!
         Create a 3-D int vector from a hypercube
              \param hyper Hypercube describing RSF

         */
        longTensor3D(std::shared_ptr<SEP::hypercube> hyper)
        {
            initNoData(hyper);
        }
        /*!
       Create a 3-D int vector from just lengths
            \param n1,n2,n3  Dimensions of the hypercube

       */
        longTensor3D(const int n1, const int n2, const int n3)
        {
            std::vector<SEP::axis> a;
            std::vector<int> ns = {n1, n2, n3};
            for (int n : ns)
                a.push_back(n);
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
      Create a 3-D int vector from axes
          \param a1,a2,a3  Axes if the hypercube

      */
        longTensor3D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3)
        {
            std::vector<SEP::axis> a = {a1, a2, a3};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
       Create a 3-D int vector from a hypercube
            \param hyper Hypercube describing RSF
            \param vals Values to fill vector with

       */
        longTensor3D(const std::shared_ptr<SEP::hypercube> hyper, const long long *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
        /*!
      Create a 3-D int vector from just lengths
          \param n1,n2,n3   Dimensions of the hypercube
          \param vals Values to fill vector with

      */
        longTensor3D(const int n1, const int n2, const int n3, const long long *vals)
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
       Create a 3-D int vector from axes
            \param a1,a2,a3 Axes if the hypercube
            \param vals Values to fill vector with
       */
        longTensor3D(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
                    const long long *vals)
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
            xt::xtensor<long long, 3>::shape_type shape = {
                (size_t)ns[2], (size_t)ns[1], (size_t)ns[0]};
            mat = xt::xtensor<long long, 3>::from_shape(shape);
            setData(mat.data());
        }
        /*!
      Make a copy of the vector
      */
        std::shared_ptr<longTensor3D> clone() const;
        /*!
       Make a copy of the vector space
       */
        std::shared_ptr<longTensor3D> cloneSpace() const;
        /*!
                                        Return a subset of the vector
                                        \param nw,fw,jw Windowing parameters
                                        */
        std::shared_ptr<longTensor3D> window(const std::vector<int> &nw,
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
        xt::xtensor<long long, 3> mat; ///< Storage for vector

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
        void initData(std::shared_ptr<SEP::hypercube> hyper, const long long *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
    };

    /*!
    A regular sampled 2-D function with int storage
    */
    class longTensor2D : public longHyper
    {
    public:
        /*!
         Create a 2-D int vector from a hypercube
              \param hyper Hypercube describing RSF

         */
        longTensor2D(std::shared_ptr<SEP::hypercube> hyper)
        {
            initNoData(hyper);
        }

        /*!
          Create a 2-D int vector from a 7-D int

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param iax2 - Second axis
          \param rev2 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        longTensor2D(const std::shared_ptr<longTensor7D> old, const int iax1,
                    const bool rev1, const int iax2, const bool rev2,
                    const std::vector<int> &ipos, const std::vector<int> &beg,
                    const std::vector<int> &end);

        /*!
          Create a 2-D int vector from a 6-D int

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param iax2 - Second axis
          \param rev2 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        longTensor2D(const std::shared_ptr<longTensor6D> old, const int iax1,
                    const bool rev1, const int iax2, const bool rev2,
                    const std::vector<int> &ipos, const std::vector<int> &beg,
                    const std::vector<int> &end);

        /*!
          Create a 2-D int vector from a 5-D int

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param iax2 - Second axis
          \param rev2 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        longTensor2D(const std::shared_ptr<longTensor5D> old, const int iax1,
                    const bool rev1, const int iax2, const bool rev2,
                    const std::vector<int> &ipos, const std::vector<int> &beg,
                    const std::vector<int> &end);

        /*!
          Create a 2-D int vector from a 4-D int

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param iax2 - Second axis
          \param rev2 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        longTensor2D(const std::shared_ptr<longTensor4D> old, const int iax1,
                    const bool rev1, const int iax2, const bool rev2,
                    const std::vector<int> &ipos, const std::vector<int> &beg,
                    const std::vector<int> &end);

        /*!
          Create a 2-D int vector from a 3-D int

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param iax2 - Second axis
          \param rev2 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        longTensor2D(const std::shared_ptr<longTensor3D> old, const int iax1,
                    const bool rev1, const int iax2, const bool rev2,
                    const std::vector<int> &ipos, const std::vector<int> &beg,
                    const std::vector<int> &end);

        /*!
          Create a 2-D int vector from a 2-D int

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param iax2 - Second axis
          \param rev2 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        longTensor2D(const std::shared_ptr<longTensor2D> old, const int iax1,
                    const bool rev1, const int iax2, const bool rev2,
                    const std::vector<int> &ipos, const std::vector<int> &beg,
                    const std::vector<int> &end);

        /*!
       Create a 2-D int vector from just lengths
            \param n1,n2   Dimensions of the hypercube

       */
        longTensor2D(const int n1, const int n2)
        {
            std::vector<SEP::axis> a;
            std::vector<int> ns = {n1, n2};
            for (int n : ns)
                a.push_back(n);
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }

        /*!
      Create a 2-D int vector from axes
          \param a1,a2  Axes if the hypercube

      */
        longTensor2D(const SEP::axis &a1, const SEP::axis &a2)
        {
            std::vector<SEP::axis> a = {a1, a2};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
       Create a 2-D int vector from a hypercube
            \param hyper Hypercube describing RSF
            \param vals Values to fill vector with

       */
        longTensor2D(const std::shared_ptr<SEP::hypercube> hyper, const long long *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
        /*!
      Create a 2-D int vector from just lengths
          \param n1,n2   Dimensions of the hypercube
          \param vals Values to fill vector with

      */
        longTensor2D(const int n1, const int n2, const long long *vals)
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
       Create a 2-D int vector from axes
            \param a1,a2  Axes if the hypercube
            \param vals Values to fill vector with
       */
        longTensor2D(const SEP::axis &a1, const SEP::axis &a2,
                    const long long *vals)
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
            xt::xtensor<long long, 2>::shape_type shape = {
                (size_t)ns[1], (size_t)ns[0]};
            mat = xt::xtensor<long long, 2>::from_shape(shape);
            setData(mat.data());
        }
        /*!
      Make a copy of the vector
      */
        std::shared_ptr<longTensor2D> clone() const;
        /*!
       Make a copy of the vector space
       */
        std::shared_ptr<longTensor2D> cloneSpace() const;
        /*!
                                        Return a subset of the vector
                                        \param nw,fw,jw Windowing parameters
                                        */
        std::shared_ptr<longTensor2D> window(const std::vector<int> &nw,
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
        xt::xtensor<long long, 2> mat; ///< Storage for vector

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
        void initData(std::shared_ptr<SEP::hypercube> hyper, const long long *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
    };

    /*!
    A regular sampled 1-D function with int storage
    */
    class longTensor1D : public longHyper
    {
    public:
        /*!
         Create a 1-D int vector from a hypercube
              \param hyper Hypercube describing RSF

         */
        longTensor1D(std::shared_ptr<SEP::hypercube> hyper)
        {
            initNoData(hyper);
        }
        /*!
       Create a 1-D int vector from just lengths
            \param n1   Dimensions of the hypercube

       */
        longTensor1D(const int n1)
        {
            std::vector<SEP::axis> a;
            std::vector<int> ns = {n1};
            for (int n : ns)
                a.push_back(n);
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }

        /*!
      Create a 1-D int vector from axes
          \param a1   Axes if the hypercube

      */
        longTensor1D(const SEP::axis &a1)
        {
            std::vector<SEP::axis> a = {a1};
            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
       Create a 1-D int vector from a hypercube
            \param hyper Hypercube describing RSF
            \param vals Values to fill vector with

       */
        longTensor1D(const std::shared_ptr<SEP::hypercube> hyper, const long long *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }

        /*!
          Create a 1-D int vector from a 2-D int

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        longTensor1D(const std::shared_ptr<longTensor2D> old, const int iax1,
                    const bool rev1,
                    const std::vector<int> &ipos, const std::vector<int> &beg,
                    const std::vector<int> &end);

        /*!
          Create a 1-D int vector from a 3-D int

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        longTensor1D(const std::shared_ptr<longTensor3D> old, const int iax1,
                    const bool rev1,
                    const std::vector<int> &ipos, const std::vector<int> &beg,
                    const std::vector<int> &end);
        /*!
          Create a 1-D int vector from a 4-D int

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        longTensor1D(const std::shared_ptr<longTensor4D> old, const int iax1,
                    const bool rev1,
                    const std::vector<int> &ipos, const std::vector<int> &beg,
                    const std::vector<int> &end);
        /*!
          Create a 1-D int vector from a 1-D int

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        longTensor1D(const std::shared_ptr<longTensor1D> old, const int iax1,
                    const bool rev1,
                    const std::vector<int> &ipos, const std::vector<int> &beg,
                    const std::vector<int> &end);
        /*!
          Create a 1-D int vector from a 5-D int

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        longTensor1D(const std::shared_ptr<longTensor5D> old, const int iax1,
                    const bool rev1,
                    const std::vector<int> &ipos, const std::vector<int> &beg,
                    const std::vector<int> &end);
        /*!
          Create a 1-D int vector from a 6-D int

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        longTensor1D(const std::shared_ptr<longTensor6D> old, const int iax1,
                    const bool rev1,
                    const std::vector<int> &ipos, const std::vector<int> &beg,
                    const std::vector<int> &end);
        /*!
          Create a 1-D int vector from a 7-D int

          \param old - Vector to grab from
          \param iax1 - Fast axis
          \param rev1 - Whether or not to reverse axis
          \param ipos Location if the subset to grab
          \param beg,end Begining and end of the subset to grab along  
          */

        longTensor1D(const std::shared_ptr<longTensor7D> old, const int iax1,
                    const bool rev1,
                    const std::vector<int> &ipos, const std::vector<int> &beg,
                    const std::vector<int> &end);

        /*!
      Create a 1-D int vector from just lengths
          \param n1    Dimensions of the hypercube
          \param vals Values to fill vector with

      */
        longTensor1D(const int n1, const long long *vals)
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
       Create a 1-D int vector from axes
            \param a1   Axes if the hypercube
            \param vals Values to fill vector with
       */
        longTensor1D(const SEP::axis &a1,
                    const long long *vals)
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
            xt::xtensor<long long, 1>::shape_type shape = {
                (size_t)ns[0]};
            mat = xt::xtensor<long long, 1>::from_shape(shape);
            setData(mat.data());
        }
        /*!
      Make a copy of the vector
      */
        std::shared_ptr<longTensor1D> clone() const;
        /*!
       Make a copy of the vector space
       */
        std::shared_ptr<longTensor1D> cloneSpace() const;
        /*!
                                        Return a subset of the vector
                                        \param nw,fw,jw Windowing parameters
                                        */
        std::shared_ptr<longTensor1D> window(const std::vector<int> &nw,
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
        xt::xtensor<long long, 1> mat; ///< Storage for vector

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
        void initData(std::shared_ptr<SEP::hypercube> hyper, const long long *vals)
        {
            initNoData(hyper);
            copyVals(vals);
        }
    };

} // namespace SEP

#endif