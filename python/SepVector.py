import pyHypercube
import pySepVector
import Hypercube
import numpy




class vector:
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
		return numpy.array(self.cppMode,copy=False)
	def checkSame(self,vec2):
		"""Function to check if two vectors belong to the same vector space"""
		print("IN SEPVE checkSAME")
		print (self,"<-a b->",vec2);
		print (self.cppMode,"<-1 2->",vec2.getCpp());
		return self.getCpp().checkSame(vec2.getCpp())

class floatVector(vector):
	"""Generic float vector class"""
	def __init__(self,**kw):
		self.kw=kw
		super().__init__()
		self.storage="dataFloat"
	def norm(self,N):
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

class doubleVector(vector):
	"""Generic double vector class"""
	def __init__(self,**kw):
		self.kw=kw
		super().__init__()
		self.storage="dataDouble"
	def norm(self,N):
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

def getSepVector(hyper,**keys):
	""" Get a sepVector object"""
	myt="dataFloat"
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
