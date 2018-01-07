#pragma once
#include "boost/multi_array.hpp"
#include<floatHyper.h>
typedef boost::multi_array<float, 1> float1D;
namespace giee{
class float1DReg: public floatHyper{
  public:
    float1DReg(std::shared_ptr<SEP::hypercube> hyper){
       initNoData(hyper);
    }
    float1DReg(int n){
       std::vector<SEP::axis>  a(1,SEP::axis(n));
       std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
       initNoData(hyp);
    
    }
    float1DReg(SEP::axis&a){
       std::vector<SEP::axis> as(1,a);
        std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(as));
       initNoData(hyp);
    }
    float1DReg(std::shared_ptr<SEP::hypercube> hyper, const float1D &vals){
       initData(hyper,vals);
    }
    float1DReg(int n, float1D &vals){
        std::vector<SEP::axis>  a(1,SEP::axis(n));
       std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(a));
       initData(hyp,vals);
    }
    float1DReg(SEP::axis &a, float1D &vals){
       std::vector<SEP::axis> as(1,a);
       std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(as));
       initData(hyp,vals);
    
    }
    
    std::shared_ptr<Vector> clone() const;
    std::shared_ptr<Vector> cloneSpace()const;
    virtual void cleanMemory(){
      _mat=0;
      setSpace();
    }
    std::shared_ptr<float1D> _mat;

  protected:
    void initNoData(std::shared_ptr<SEP::hypercube> hyp);
    void initData(std::shared_ptr<SEP::hypercube> hyp,const float1D &vals);


};

}
