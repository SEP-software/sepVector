%module numPyVec_int
%{ 
    #define SWIG_FILE_WITH_INIT
    #include "numPyVec.h"
using namespace SEP;
%}

%include "numPyVec.h"
