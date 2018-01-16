import hypercube_int
import numPyVec_int
import sys



class sepVec(numpy.ndarray):

	def __init__(self, *args,**kw):
      self._n=[]
      self._o=[]
      self._d=[]
      self._label=[]

    def initFromNumPyPy(self,numPy,n,o,d,label):



    def initFromNumPyC(self,numC):
      ndim=numC.getHyper().getNdim();
      for i in len(dim):
      	j=i+1
      	self._n.push_back(numC.getHyper().getAxis(j).n);
      	self._o.push_back(numC.getHyper().getAxis(j).o);
      	self._d.push_back(numC.getHyper().getAxis(j).d);
      	self._label.push_back(numC.getHyper().getAxis(j).label);
      	self._C=numP


    def getAxis(self,iax):
      if iax> len(self._n) or iax <1:
      	  print("Requesting axis %d out of range 1..%d"%(iax,len(self._n)))
      	  sys.exit(-1);
      return self._n[iax-1],self._o[iax-1],self._d[iax-1],self._label[iax-1];

    def getAxes(self):
      n=[]
      o=[]
      d=[]
      label=[]
      for i in len(self._n):
      	n.push_back(self._n[i]);
      	o.push_back(self._o[i]);
      	d.push_back(self._d[i]);
      	label.push_back(self._label[i]);
      return n,o,d,label




