import pyHypercube
import pySepVector
import Hypercube
import numpy
import pyVector




class vector(pyVector.vector):
	"""Generic sepVector class"""
	def __init__(self):
		"""Initialize a vector object"""
		if "fromCpp" in self.kw:
			self.cppMode=self.kw["fromCpp"]
		elif "fromHyper" in self.kw:
			self.cppMode=getCppSepVector(self.kw["fromHyper"],self.kw)

	def getCpp(self):
		"""Return the associated cpp object"""
		return self.cppMode

	def getStorageType(self):
		"""Return type of storage"""
		return self.storage
	def zero(self):
		"""Function to zero out a vector"""
		self.cppMode.zero()
	def set(self,val):
		"""Function to a vector to a value"""
		self.cppMode.set(val)
	def getHyper(self):
		"""Return the hypercube associated with the vector"""
		return Hypercube.hypercube(hypercube=self.cppMode.getHyper())

	def getNdArray(self):
		"""Return a numpy version of the array (same memory"""
		return numpy.array(self.cppMode,copy=False)
	def window(self,**kw):
		"""Window a vector return another vector (of the same dimension
		    specify min1..min6, max1...max6, f1...f6, j1...j6, n1...n6, or
		    any of these by lists.
		    Can not specify n and min or max """
		axes=getHyper().axes
		ndim=len(axes)
		for i in range(1,ndim+1):
			nset=False
			fset=False
			jset=False
			if "n%d"%i in kw: 
				nset=True
				n=int(kw["n%d"%i])
			if "f%d"%i in kw: 
				jset=True
				j=int(kw["j%d"%i])
			if "j%d"%i in kw: 
				fset=True
				f=int(kw["f%d"%i])
			biSet=False
			eiSet=False
			if "min%d"%i in kw:
				bi=int(float(kw["min"%i] - axes[i-1].o)/axes[i-1].d+.5)
				biSet=True
			if "max%d"%i in kw:
				ei=int(float(kw["max"%i] - axes[i-1].o)/axes[i-1].d+.5)	
				eiSet=True		
			if fset:
				if axes[i-1].n <= f:
					raise Exception("invalid f%d=%d parameter n%d of data=%d"%(i,f,i,axes[i-1].n))
			if nset:
				if axes[i-1].n < n:
					raise Exception("invalid n%d=%d parameter n%d of data=%d"%(i,n,i,axes[i-1].n))
			if jset and j <=0:
				raise Exception("invalid j%d=%d "%(i,j))
			if not jset:
				j=1
			if not nset:
				if not fset:
					if not biSet:
						f=0
					elif bi < 0 or bi >= axes[i-1].n:
						raise Exception("Invalid min%d=%f"%(i,kw["min%d"%i]))
					else:
						f=bi
				if  eiSet:
					if ei <=f or ei >= axes[i-1].n:
						raise Exception("Invalid max%d=%f"%(i,kw["max%d"%i]))
					else:
						n=(ei-f-1)/j+1
			elif not fset:
				if not biSet:
					f=0
				elif bi < 0 || bi >= axes[i-1].n:
					raise Exception("Invalid min%d=%f"%(i,kw["min%d"%i]))
				else:
					f=fi
			if axes[i-1].n < (1+f+j*(n-1)):
				raise Exception("Invalid window parameter")


	def checkSame(self,vec2):
		"""Function to check if two vectors belong to the same vector space"""
		return self.getCpp().checkSame(vec2.getCpp())

class floatVector(vector):
	"""Generic float vector class"""
	def __init__(self,**kw):
		self.kw=kw
		super().__init__()
		self.storage="dataFloat"
	def norm(self,N=2):
		"""Function to compute vector N-norm"""
		self.cppMode.norm(N)

	def scale(self,sc):
		"""Function to scale a vector"""	
		self.cppMode.scale(sc)
	def rand(self):
		"""Function to fill with random numbers"""
		self.cppMode.rand()
	def clone(self):
		"""Function to clone (deep copy) a vector"""
		return floatVector(fromCpp=self.cppMode.clone())
	def cloneSpace(self):
		"""Funtion tor return the space of a vector"""
		return floatVector(fromCpp=self.cppMode.cloneSpace())
	def scaleAdd(self,vec2,sc1=1.,sc2=1.):
		"""self=self*sc1+sc2*vec2"""
		self.cppMode.scaleAdd(vec2.cppMode,sc1,sc2)
	def copy(self,vec2):
		"""Copy vec2 into self"""
		self.scaleAdd(vec2,0.,1.)
	def dot(self,vec2):
		"""Compute dot product of two vectors"""
		return self.cppMode.dot(vec2.cppMode)
	def multiply(self,vec2):
		"""self=vec2*self"""
		self.cppMode.multiply(vec2.cppMode)
	def norm(self,nrm=2):
		"""Return the norm of a vector"""
		return self.cppMode.norm(nrm)
	def isDifferent(self,vec2):
		"""Function to check if two vectors belong to the same vector space"""
		return self.cppMode.isDifferent(vec2.cppMode)   

class doubleVector(vector):
	"""Generic double vector class"""
	def __init__(self,**kw):
		self.kw=kw
		super().__init__()
		self.storage="dataDouble"
	def norm(self,N=2):
		"""Function to compute vector N-norm"""
		self.cppMode.norm(N)

	def scale(self,sc):
		"""Function to scale a vector"""	
		self.cppMode.scale(sc)
	def rand(self):
		"""Function to fill with random numbers"""
		self.cppMode.rand()
	def clone(self):
		"""Function to clone (deep copy) a vector"""
		return doubleVector(fromCpp=self.cppMode.clone())
	def copy(self,vec2):
		"""Copy vec2 into self"""
		self.scaleAdd(vec2,0.,1.)
	def cloneSpace(self):
		"""Funtion tor return the space of a vector"""
		return doubleVector(fromCpp=self.cppMode.cloneSpace())
	def scaleAdd(self,vec2,sc1=1.,sc2=1.):
		"""self=self*sc1+sc2*vec2"""
		self.cppMode.scaleAdd(vec2.cppMode,sc1,sc2)
	def dot(self,vec2):
		"""Compute dot product of two vectors"""
		return self.cppMode.dot(vec2.cppMode)
	def multiply(self,vec2):
		"""self=vec2*self"""
		self.cppMode.multiply(vec2.cppMode)
	def norm(self,nrm=2):
		"""Return the norm of a vector"""
		return self.cppMode.norm(nrm)
	def isDifferent(self,vec2):
		"""Function to check if two vectors belong to the same vector space"""
		return self.cppMode.isDifferent(vec2.cppMode)     
class intVector(vector):
	"""Generic int vector class"""
	def __init__(self,**kw):
		self.kw=kw
		super().__init__()
		self.storage="dataInt"

class complexVector(vector):
	"""Generic complex vector class"""
	def __init__(self,**kw):
		self.kw=kw
		super().__init__()
		self.storage="dataComplex"

class byteVector(vector):
	"""Generic byte vector class"""
	def __init__(self,**kw):
		self.kw=kw
		super().__init__()
		self.storage="dataByte"

def getSepVector(*args,**keys):
	""" Get a sepVector object
		Option 1 (supply hypercube):
			hyper, kw args
		Option 2 (build hypercube):
			ns=[] -list of sizes
			os=[] - list of origins
			ds=[] - list os sampling
			labels=[] list of labels
			axes=[] list of axes
		storage= StorageType (dataFloat[default],dataComplex,dataDouble,dataInt,dataByte)
	"""
	myt="dataFloat"
	if len(args)==1:
		hyper=args[0]
	elif len(args>1):
		if "axes" in keys or "ns" in keys:
		hyper=Hypercube.hypercube(**keys)
	else:
		raise Exception("Must supply Hypercube or ns/axes")

	if "storage" in keys:
		myt=keys["storage"]
	if myt == "dataFloat":
		x=getFloatVector(hyper)
		return floatVector(fromCpp=x)
	elif myt=="dataComplex":
		x=getComplexVector(hyper)
		return complexVector(fromCpp=x)
	elif myt=="dataDouble":
		x=getDoubleVector(hyper)
		return doubleVector(fromCpp=x)
	elif myt=="dataInt":
		x=getIntVector(hyper)
		return intVector(fromCpp=x)
	elif myt=="dataByte":
		x=getByteVector(hyper)
		return byteVector(fromCpp=x)
	else:
		raise Exception("Unknown type %s"%myt)

def getCppSepVector(hyper,**keys):
		h=hyper.getCpp()
		myt="dataFloat"
		if "storage" in keys:
			myt=keys["storage"]
		if myt == "datFloat":
			x=getFloatVector(hyper)
		elif myt=="dataComplex":
			x=getComplexVector(hyper)
		elif myt=="dataDouble":
			x=getDoubleVector(hyper)
		elif myt=="dataInt":
			x=getIntVector(hyper)
		elif myt=="dataByte":
			x=getByteVector(hyper)
		else:
			raise Exception("Unknown type"%myt)

		


def getFloatVector(hyper):
	h=hyper.getCpp()
	if len(hyper.axes) ==1:
		return pySepVector.float1DReg(h)
	elif len(hyper.axes) ==2:
		return pySepVector.float2DReg(h)	
	elif len(hyper.axes) ==3:
		return pySepVector.float3DReg(h)	
	elif len(hyper.axes) ==4:
		return pySepVector.float4DReg(h)	
	elif len(hyper.axes) ==5:
		return pySepVector.float5DReg(h)
	elif len(hyper.axes) ==6:
		return pySepVector.float6DReg(h)	

def getComplexVector(hyper):
	h=hyper.getCpp()

	if len(hyper.axes) ==1:
		return pySepVector.complex1DReg(h)
	elif len(hyper.axes) ==2:
		return pySepVector.complex2DReg(h)	
	elif len(hyper.axes) ==3:
		return pySepVector.complex3DReg(h)	
	elif len(hyper.axes) ==4:
		return pySepVector.complex4DReg(h)	
	elif len(hyper.axes) ==5:
		return pySepVector.complex5DReg(h)
	elif len(hyper.axes) ==6:
		return pySepVector.complex6DReg(h)

def getByteVector(hyper):
	h=hyper.getCpp()

	if len(hyper.axes) ==1:
		return pySepVector.byte1DReg(h)
	elif len(hyper.axes) ==2:
		return pySepVector.byte2DReg(h)	
	elif len(hyper.axes) ==3:
		return pySepVector.byte3DReg(h)	
	elif len(hyper.axes) ==4:
		return pySepVector.byte4DReg(h)	
	elif len(hyper.axes) ==5:
		return pySepVector.byte5DReg(h)
	elif len(hyper.axes) ==6:
		return pySepVector.byte6DReg(h)

def getDoubleVector(hyper):
	h=hyper.getCpp()
	if len(hyper.axes) ==1:
		return pySepVector.double1DReg(h)
	elif len(hyper.axes) ==2:
		return pySepVector.double2DReg(h)	
	elif len(hyper.axes) ==3:
		return pySepVector.double3DReg(h)	
	elif len(hyper.axes) ==4:
		return pySepVector.double4DReg(h)	
	elif len(hyper.axes) ==5:
		return pySepVector.double5DReg(h)
	elif len(hyper.axes) ==6:
		return pySepVector.double6DReg(h)

def getIntVector(hyper):
	if len(hyper.axes) ==1:
		return pySepVector.int1DReg(h)
	elif len(hyper.axes) ==2:
		return pySepVector.int2DReg(h)	
	elif len(hyper.axes) ==3:
		return pySepVector.int3DReg(h)	
	elif len(hyper.axes) ==4:
		return pySepVector.int4DReg(h)	
	elif len(hyper.axes) ==5:
		return pySepVector.int5DReg(h)
	elif len(hyper.axes) ==6:
		return pySepVector.int6DReg(h)



def readColTextFile(file):
	f=open(file)
	lines=f.readlines()
	array=[]
	for line in lines:
		parts=line.split()
		vec1=[]
		for x in parts:
			try:
				y=float(x)
				vec1.append(y)
			except:
				y=x
		array.append(vec1)
	array2=[]
	for i in range(len(array[0])):
		lst=[]
		for j in range(len(array)):
			lst.append(array[j][i])
		array2.append(lst)
	return array2
