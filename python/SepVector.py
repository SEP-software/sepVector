import pyHypercube
import pySepVector
import Hypercube
import numpy


def getSepVector(hyper,**keys):
		h=hyper.getCpp()
		myt="float"
		if "type" in keys:
			myt=keys["type"]
		if myt == "float":
			x=getFloatVector(hyper)
		elif myt=="complex":
			x=getComplexVector(hyper)
		elif myt=="double":
			x=getDoubleVector(hyper)
		elif myt=="int":
			x=getIntVector(hyper)
		elif myt=="byte":
			x=getByteVector(hyper)
		else:
			raise Exception("Unknown type"%myt)

		if "fill" in keys:
			checkSanity(myt,hyper,keys["fill"])

		if len (hyper.axes)==1:
			y=numpy.array(x,copy=False)
			for i1 in range(hyper.axes[0].n):
				y[i]=keys["fill"][i1]
		elif len(hyper.axes)==2:
			for i2 in range(hyper.axes[1].n):
				for i1 in range(hyper.axes[0].n):
					y[i2][i1]=keys["fill"][i2][i1]
		elif len(hyper.axes)==3:
			for i3 in range(hyper.axes[2].n):
				for i2 in range(hyper.axes[1].n):
					for i1 in range(hyper.axes[0].n):
						y[i3][i2][i1]=keys["fill"][i3][i2][i1]				
		elif len(hyper.axes)==4:
			for i4 in range(hyper.axes[3].n):
				for i3 in range(hyper.axes[2].n):
					for i2 in range(hyper.axes[1].n):
						for i1 in range(hyper.axes[0].n):
							y[i4][i3][i2][i1]=keys["fill"][i4][i3][i2][i1]
		elif len(hyper.axes)==5:
			for i5 in range(hyper.axes[4].n):
				for i4 in range(hyper.axes[3].n):
					for i3 in range(hyper.axes[2].n):
						for i2 in range(hyper.axes[1].n):
							for i1 in range(hyper.axes[0].n):
								y[i5][i4][i3][i2][i1]=keys["fill"][i5][i4][i3][i2][i1]	
		elif len(hyper.axes)==6:
			for i6 in range(hyper.axes[5].n):
				for i5 in range(hyper.axes[4].n):
					for i4 in range(hyper.axes[3].n):
						for i3 in range(hyper.axes[2].n):
							for i2 in range(hyper.axes[1].n):
								for i1 in range(hyper.axes[0].n):
									y[i6][i5][i4][i3][i2][i1]=keys["fill"][i6][i5][i4][i3][i2][i1]	
		return x;


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

def checkSanity(myt,hyper,fill):
	if isinstance(fill,list):
		if len(hyper.axes) !=1:
			raise Exception("If passing a list for fill must be 1-D array")
		return
	if not isinstance(fill, numpy.ndarray):
		raise Exception("Must pass ndarray as initializer")
	if myt=="float" and fill.dtype!=numpy.float32:
		raise Exception("Must numpy.float32 to fill a floatHyer")
	if myt=="int" and fill.dtype!=numpy.int32:
		raise Exception("Must numpy.int32 to fill a intHyper")	
	if myt=="double" and fill.dtype!=numpy.float64:
		raise Exception("Must numpy.float64 to fill a doubleHyper")
	if myt=="complex" and fill.dtype!=numpy.complex64:
		raise Exception("Must numpy.complex64 to fill a complexHyper")
	if myt=="byte" and fill.dtype!=numpy.int8:
		raise Exception("Must numpy.int8 to fill a byteHyper")

	if len(fill.shape) != len(hyper.axes):
		raise Exception("Fill and hyper not the same number of dimensions")

	for i in range(fill.shape):
		if hyper.axes[i].n != fill.shape[len(fill.shape)-1-i]:
			raise Exception("Fill and hyper not the same size axis %d"%(i+1))



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