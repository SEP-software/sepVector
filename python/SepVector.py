import pyHypercube
import pySepVector
import Hypercube
import numpy




class vector:
	"""Generic sepVector class"""
	def __init__(self,**kw):
      if "fromCpp" in kw:
      	self.cppMode=kw["fromCpp"]
      elif "fromHyper" in kw:
      	self.cppMode=getCppSepVector(kw["fromHyper"],kw)

	def getCpp(self):
		"""Return the associated cpp object"""
		return self.cppMode

	def getStorageType(self):
		"""Return type of storage"""
		return self.storage

	def getHyper(self):
		"""Return the hypercube associated with the vector"""
		return Hypercube.hypercube(hypercube=self.cppMode.getHyper())

	def getNdArray(self):
		return np.array(self.cppMode,copy=False)


def floatVector:
	"""Generic float vector class"""
	def __init__(self,**kw):
		super().__init__(kw)
		self.storage="dataFloat"
    def norm(self,N):
		"""Function to compute vector N-norm"""
    	self.cppMode.norm(N)
    def zero(self):
		"""Function to zero out a vector"""
		self.cppMode.zero()
	def scale(self,sc):
		 """Function to scale a vector"""	
		 self.cppMode.scale(sc)
	def rand(self):
		"""Function to fill with random numbers"""
		self.cppMode.rand()
	def clone(self):
		"""Function to clone (deep copy) a vector"""
		return self.cppMode.clone()
	def cloneSpace(self):
		"""Funtion tor return the space of a vector"""
		return self.cppMode.cloneSpace()
	def scaleAdd(self,vec2,sc1,sc2):
		"""self=self*sc1+sc2*vec2"""
		self.cppMode.scaleAdd(vec2,sc1,sc2)
	def dot(self,vec2):
		"""Compute dot product of two vectors"""
		return self.cppMode.dot(vec2)
    def multiply(self,vec2):
    	"""self=vec2*self"""
    	self.cppMode.multiply(vec2)
    def isDifferent(self,vec2):
    	"""Function to check if two vectors belong to the same vector space"""
    	return self.cppMode.isDifferent(vec2)   

def doubleVector:
	"""Generic double vector class"""
	def __init__(self,**kw):
		super().__init__(kw)
		self.storage="dataDouble"
    def norm(self,N):
		"""Function to compute vector N-norm"""
    	self.cppMode.norm(N)
    def zero(self):
		"""Function to zero out a vector"""
		self.cppMode.zero()
	def scale(self,sc):
		 """Function to scale a vector"""	
		 self.cppMode.scale(sc)
	def rand(self):
		"""Function to fill with random numbers"""
		self.cppMode.rand()
	def clone(self):
		"""Function to clone (deep copy) a vector"""
		return self.cppMode.clone()
	def cloneSpace(self):
		"""Funtion tor return the space of a vector"""
		return self.cppMode.cloneSpace()
	def scaleAdd(self,vec2,sc1,sc2):
		"""self=self*sc1+sc2*vec2"""
		self.cppMode.scaleAdd(vec2,sc1,sc2)
	def dot(self,vec2):
		"""Compute dot product of two vectors"""
		return self.cppMode.dot(vec2)
    def multiply(self,vec2):
    	"""self=vec2*self"""
    	self.cppMode.multiply(vec2)
    def isDifferent(self,vec2):
    	"""Function to check if two vectors belong to the same vector space"""
    	return self.cppMode.isDifferent(vec2)   
def intVector:
	"""Generic int vector class"""
	def __init__(self,**kw):
		super().__init__(kw)
		self.storage="dataInt"

def complexVector:
	"""Generic complex vector class"""
	def __init__(self,**kw):
		super().__init__(kw)
		self.storage="dataComplex"

def byteVector:
	"""Generic byte vector class"""
	def __init__(self,**kw):
		super().__init__(kw)
		self.storage="dataByte"

def getSepVector(hyper,**keys):
	""" Get a sepVector object"""
	myt="dataFloat"
	if "storage" in keys:
		myt=keys["storage"]
	if myt == "datFloat":
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
		raise Exception("Unknown type"%myt)

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
		return pySepVector.float4DReg(h)
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
		return pySepVector.complex4DReg(h)
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
		return pySepVector.byte4DReg(h)
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
		return pySepVector.double4DReg(h)
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
		return pySepVector.int4DReg(h)
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