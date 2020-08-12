#ifndef float7D_reg_h
#define float7D_reg_h 1
#include <floatHyper.h>
#include "boost/multi_array.hpp"


typedef boost::multi_array<float, 7> float7D;
namespace SEP {
    /*!
    A regular sampled 7-D function with float storage
    */
    class float7DReg : public floatHyper {
    public:
        /*!
         Create a 7-D float vector from a hypercube
              \param hyper Hypercube describing RSF

         */
        float7DReg(std::shared_ptr<SEP::hypercube> hyper) {
            initNoData(hyper);
        }
        /*!
       Create a 7-D float vector from just lengths
            \param n1,n2,n3,n4,n5,n6,n7 Dimensions of the hypercube

       */
        float7DReg(const int n1, const int n2, const int n3, const int n4,
            const int n5, const int n6, const int n7) {
            std::vector<SEP::axis> a;
            a.push_back(SEP::axis(n1));
            a.push_back(SEP::axis(n2));
            a.push_back(SEP::axis(n3));
            a.push_back(SEP::axis(n4));
            a.push_back(SEP::axis(n5));
            a.push_back(SEP::axis(n6));
            a.push_back(SEP::axis(n7));

            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
      Create a 7-D float vector from axes
          \param a1,a2,a3,a4,a5,a6, a7 Axes if the hypercube

      */
        float7DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
            const SEP::axis &a4, const SEP::axis &a5, const SEP::axis &a6, const SEP::axis &a7) {
            std::vector<SEP::axis> a;
            a.push_back(a1);
            a.push_back(a2);
            a.push_back(a3);
            a.push_back(a4);
            a.push_back(a5);
            a.push_back(a6);
            a.push_back(a7);

            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initNoData(hyp);
        }
        /*!
       Create a 7-D float vector from a hypercube
            \param hyper Hypercube describing RSF
            \param vals Values to fill vector with

       */
        float7DReg(std::shared_ptr<SEP::hypercube> hyper, const float7D &vals) {
            initData(hyper, vals);
        }
        /*!
      Create a 6-D float vector from just lengths
          \param n1,n2,n3,n4,n5,n6,n7 Dimensions of the hypercube
          \param vals Values to fill vector with

      */
        float7DReg(const int n1, const int n2, const int n3, const int n4,
            const int n5, const int n6, const int n7, float7D &vals) {
            std::vector<SEP::axis> a;
            a.push_back(SEP::axis(n1));
            a.push_back(SEP::axis(n2));
            a.push_back(SEP::axis(n3));
            a.push_back(SEP::axis(n4));
            a.push_back(SEP::axis(n5));
            a.push_back(SEP::axis(n6));
            a.push_back(SEP::axis(n7));

            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initData(hyp, vals);
        }
        /*!
       Create a 7-D float vector from axes
            \param a1,a2,a3,a4,a5,a6,a7 Axes if the hypercube
            \param vals Values to fill vector with
       */
        float7DReg(const SEP::axis &a1, const SEP::axis &a2, const SEP::axis &a3,
            const SEP::axis &a4, const SEP::axis &a5, const SEP::axis &a6, const SEP::axis &a7,
            float7D &vals) {
            std::vector<SEP::axis> a;
            a.push_back(a1);
            a.push_back(a2);
            a.push_back(a3);
            a.push_back(a4);
            a.push_back(a5);
            a.push_back(a6);
            a.push_back(a7);

            std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
            initData(hyp, vals);
        }
        /*!
           Allocate data for vector
           */
        void allocate() {
            std::vector<int> ns = getHyper()->getNs();
            _mat.reset(
                new float7D(boost::extents[ns[6]][ns[5]][ns[4]][ns[3]][ns[2]][ns[1]][ns[0]]));

            setData(_mat->data());
            ;
        }
        /*!
      Make a copy of the vector
      */
        std::shared_ptr<float7DReg> clone() const;
        /*!
       Make a copy of the vector space
       */
        std::shared_ptr<float7DReg> cloneSpace() const;
        /*!
                                        Return a subset of the vector
                                        \param nw,fw,jw Windowing parameters
                                        */
        std::shared_ptr<float7DReg> window(const std::vector<int> &nw,
            const std::vector<int> &fw,
            const std::vector<int> &jw) const;
        /*!
        Deallocate storage for vector, turn into vector space
         */
        virtual void cleanMemory() {
            _mat = 0;
            setSpace();
        }
        std::shared_ptr<float7D> _mat;  ///< Storage for vector

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
        void initData(std::shared_ptr<SEP::hypercube> hyper, const float7D &vals);
    };
}  // namespace SEP
#endif
