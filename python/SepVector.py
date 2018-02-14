import pyHypercube
import pySepVector
import Hypercube
import numpy


def getSepVector(hyper,*args):
		h=hyper.getCpp()
		if len(hyper.axes) ==1:
			x= pySepVector.float1DReg(h)
			if len(args)==1:
				y=numpy.array(x,copy=False)
				if isinstance(args[0],numpy.ndarray) or isinstance(args[0],list):
					for i in range(y.shape[0]):
						y[i]=args[0][i]
		elif len(hyper.axes) ==2:
			x= pySepVector.float2DReg(h)
			if len(args)==1:
				y=numpy.array(x,copy=False)
				if isinstance(args[0],numpy.ndarray) or isinstance(args[0],list):
					for i2 in range(y.shape[0]):
						for i1 in range(y.shape[1]):
							y[i2][i1]=args[0][i2][i1]
		elif len(hyper.axes) ==3:
			x= pySepVector.float3DReg(h)
			if len(args)==1:
				y=numpy.array(x,copy=False)
				if isinstance(args[0],numpy.ndarray) or isinstance(args[0],list):
					for i3 in range(y.shape[0]):
						for i2 in range(y.shape[1]):
							for i1 in range(y.shape[2]):
								y[i3][i2][i1]=args[0][i3][i2][i1]
		elif len(hyper.axes) ==4:
			x= pySepVector.float4DReg(h)
			if len(args)==1:
				y=numpy.array(x,copy=False)
				if isinstance(args[0],numpy.ndarray) or isinstance(args[0],list):
					for i4 in range(y.shape[0]):
						for i3 in range(y.shape[1]):
							for i2 in range(y.shape[2]):
								for i1 in range(y.shape[3]):
									y[i4][i3][i2][i1]=args[0][i3][i3][i2][i1]
		return x


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