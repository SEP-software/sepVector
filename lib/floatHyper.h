#pragma once
#include "Operator.h"
#include<hypercube.h>
#include<cassert>
#include<sstream>
namespace giee{
class floatHyper: public Vector{
  protected:
   floatHyper(){;}
   
  public:
   void setHyper(std::shared_ptr<SEP::hypercube> h){
      _hyper=h;
   }   
   bool getSpaceOnly()const {return _spaceOnly;}
   virtual void add(std::shared_ptr<Vector>vec);
   virtual void scale(const double val);
   virtual void scaleAdd(const double sc1, std::shared_ptr<Vector>vec2,const double sc2);
   virtual void random();
   virtual double dot(std::shared_ptr<Vector>vec2) const;
   void setData(float *ptr){
      _vals=ptr;
      setNotSpace();
   }
   float *getVals(){return _vals;}
   const float *getCVals(){return _vals;}
    virtual void softClip(const float val);
    virtual float absMax() const ;
    float min() const ;
   virtual void infoStream(const int lev, std::stringstream &x);
   std::shared_ptr<SEP::hypercube>  getHyper()const{
   return _hyper;}
   virtual bool checkSame(const std::shared_ptr<giee::Vector> vec2, const bool checkAlloc=false) const;
   virtual void calcCheckSum();

  private:
     std::shared_ptr<SEP::hypercube>_hyper;
     float *_vals;
};

}

