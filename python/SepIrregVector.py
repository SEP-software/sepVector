import Hypercube
import numba
import SepVector
import pyVector
import numpy as np 
import copy
import operator
class key:
    """Simple key object"""
    def __init__(self,val):
        """Initalize a key

            Optional:
              val - numpy array containing key values
        
        """
        if not isinstance(val, np.ndarray):
            raise Exception("Expecting nd array")
        if val.ndim != 1:
            raise Exception("Expecting 1-D array")
        self._vals=np.copy(val)


    def __getitem__(self,ith):
        """Return the ith header"""
        return self._vals[ith]
    
    def __setitem__(self,ith,val):
        """Set the ith header"""
        self._vals[ith]=val
    def __getslice__(self,ibeg,iend):
        """Return a range of headers from ibeg to iend"""
        return self._vals[ibeg:iend]
    
    def __setslice__(self,ibeg,iend,vals):
        """Set ar angle of header values (vals) from ibeg to iend"""
        self._vals[ibeg:iend]=vals

    def setKeyVals(self,vals):
        """
        Set the key vals for a header key"""
        self._vals=vals
    
    def size(self):
        """Return keys size"""
        return self._vals.shape[0]
    def getDType(self):
        """Return type of key np format"""
        return self._vals.dtype



class headerBlock:
    """Object to store headers"""
    def __init__(self,**kw):
        """
            Method 1:

                keys - A dictionary of keys object
            
            Method 2:
                nh - Create a empty header block only setting the number of headers

            Optional:
                drn - Data record number
                keyOrder - The order in which the keys should be stored
                grid - Grid associated with headers (must specify gridHyper also)
                gridHyper - Hypercube associated with grid (first axis is nt but unchecked)

        """
        self._nh=0

        self._keys={}

        self._drn=None
        self._keyOrder=[]
        self._orderSet=False
        self._grid=None
        self._gridHyper=None
        self._gridI=None
        if "keyOrder" in kw:
            self._orderSet=True
            self._keyOrder=kw["keyOrder"]

            if not isinstance(self._keyOrder,list):
                raise Exception("Expecting keyOrder to be a list is %s"%type(self._keyOrder))

        if "keys" in kw:
            self._keys=kw["keys"]
            if not isinstance(self._keys,dict):
                raise Exception("Expecting keys to be a dictionary of keys")
            for k,v in self._keys.items():
                if self._orderSet:
                    if k not in self._keyOrder:
                        raise Exception("Key must exist in keyorder if set")
                else:
                    self._keyOrder.append(k)
                if not isinstance(v,key):
                    raise Exception("Expecting a key as the value in the dictionary")
                if self._nh==0:
                    self._nh=v.size()
                else:
                    if self._nh!=v.size():
                        raise Exepction("Keys not all the same size")
        elif "nh" in kw:
            if not isinstance(kw["nh"],int):
                raise Exception("Expecting nh to be an int")
            self._nh=kw["nh"]
        else:
            raise Exception("Unknown initialization method")

        if "drn" in kw:
            if kw["drn"] is not None:
                self._drn=kw["drn"]
                if not isinstance(self._drn,np.ndarray):
                    raise Exception("Expecting drn to be a numpy array")
                if self._drn.dtype!=np._int32:
                    raise Exception("Expecting int32 numpy array")
                if self._drn.ndim !=1:
                    raise Exception("Expecting drn to be a 1-d array")
                if self._drn.shape[0]!=self._nh:
                    raise Exception("drn size does not match number of headers")
        if "grid" in kw:
            self._grid=kw["grid"]
            if not self._grid is None:
                if not isinstance(self._grid,SepVector.byteVector):
                    raise Exception("Grid must be a SepVector byte instead is ",type(self._grid))
                self._gridN=self._grid.getNdArray()
                if self._gridN.ndim!=1:
                    raise Exception("Expecting the grid to be 1-D instead ",self._gridN.ndim)
                if not "gridHyper" in kw:
                    raise Exception("Expecting gridHyper when grid is specified")
                self._gridHyper=kw["gridHyper"]
                if not isinstance(self._gridHyper,Hypercube.hypercube):
                    raise Exception("Expecting gridHyper to be a Hypercube.hypercube object instead is ",type(self._gridHyper))
                n=1
                print("what",self._gridHyper,"happened")
                for i in range(1,len(self._gridHyper.axes)):
                    n=n*self._gridHyper.axes[i].n
                    print("comparison ",n,self._gridN.shape[0])
                if n!= self._gridN.shape[0]:
                    print(self._gridHyper,n,self._gridN.shape[0])
                    raise Exception("Grid hyper n123/n[0] != size of grid %d %s %d"%(n,str(self._gridHyper),self._gridN.shape[0]))
    def clone(self):
        """Make a copy of headers"""
        return headerBlock(keys=self._keys,drn=self._drn,keyOrder=self._keyOrder,grid=self._grid,gridHyper=self._gridHyper)
  
    def cloneSpace(self):
        """Return just the space"""
        x=headerBlock(nh=self._nh)
        for k in self._keyOrder:
            x._keys[k]=None
        x._gridHyper=self._gridHyper
        return x

    def __getattr__(self, attr):
        """Default access is header key"""
        if attr in self._keys:
            return self._keys[attr]
        else:
            raise Exception("Unknown key %s"%attr)
    def size(self):
        """Return the number of headers"""
        return self._nh
            
  

    def getKey(self,name):
        """Get the header values associated with the key"""
        return self._keys[name]

    def setKey(self,name,vals):
        """Return key"""
        if vals.size() != self._nh:
            raise Exception("Key size doesn't match nh size")
        self._keys[name]=vals

    def checkSame(self,header2):
        """ Check to see if two header blocks are the same 
          for now we are just going to check nh and keys the same"""
        if self._nh != header2._nh:
            return False
        for k in self._keys:
            if k not in header2._keys:
                return False
        if self._gridHyper:
            if not header2.gridHyper:
                return False
            return self._gridHyper.checkSame(header2._gridHyper)
        return True

    def addKey(self,name,**kw):
        """
        Add a key

        name - keyname

        Method 1:
            vals - numpy 1-D array containing the vals 
            
        Method 2:
            typ - Type of array 
            """
        if name in self._keys:
            raise Exception("Key already exists can not add")
        if "vals" in kw:
            if not isinstance(kw["vals"],np.ndarray):
                raise Exception("Expecting vals to be a numpy array")
            self._keys[name]=key(kw["vals"])
        elif "typ" in kw:
            if not kw["typ"] in SepVector.SepVecTypeToDtype:
                raise Expception("Unsupported key type")
            ar=np.zeros((nh,),dtype=SepVector.SepVecTypeToDtype[kw["typ"]])
            self._keys[name]=key(ar)
        else: 
            raise Exception("Unknown initialization type")
        self._keyOrder.append(name)
        
    def enableGridAccess(self):
        """Create the ability to access through grid coordinates"""
        if self._grid is None:
            raise Exception("Can not enable grid access when grid is not assocated")
        self._gridI=np.zeros(self._gridN.shape[0],dtype=np.int32)
        createGrid(self._gridN,self._gridI)
    
    def getGridWindow(self,**kw):
        """Get a header window from the grid
            n#,f#,j#,min#,max# - Windowing parameters

            @returns headerBlock,traceNumbers
        
        """
        if self._grid is None:
            raise Exception("Can not get a grid window when grid has not been specified")
        if self._gridI is None:
            self.enableGridAccess()
        itrs=getHeaderNumbers(*kw)
        hdr=headerWindow(nh=its.shape[0])
        for k in self._key_order:
            ar=np.zeros(itrs.size(),dtype=key.getDType())
            extractKey(self._keys[i],itr,ar)
            hdr.addKey(k,vals=ar)
        return hdr,itrs
         
    def getCreateGrid(self):
        """Return a grid

        If no grid exists it means that we have just a header
        dataset and a grid of all 1s is returned"""
        if self._gridHyper:
            return self._grid
        else:
            g=SepVector.getSepVector(storage="dataByte",ns=[self._nh])
            g.getNdArray().fill(1)
            return g
    def putGridWindow(self,headers,**kw):
        """Put header window from the grid

        n#,f#,j#,min#,max# - Windowing parameters
        headers - Headerblock

        @returns traceNumbers 

        """
        if self._grid is None:
            raise Exception("Can not get a grid window when grid has not been specified")
        if self._gridI is None:
            self.enableGridAccess()
        itrs=getHeaderNumbers(*kw)
        for k,v in headers._keys.items():
            if not k in self._keys:
                raise Exception("trying to put key that doesn't exist")
            insertKey(v,itrs,self._keys[k])
    def __repr__(self):
        """Print info about headers"""
        if self._gridHyper:
            out="Grid hypercube\n%s\nkeys:\n"%str(self._gridHyper)
        else:
            out="%d headers\nkeys:\n"%self._nh
        for k in self._keyOrder:
            if len(k)<8:
                out+="\t%s \t \t \t %s\n"%(k,self._keys[k].getDType())
            elif len(k)<16:
                out+="\t%s \t \t %s\n"%(k,self._keys[k].getDType())
            else:
                out+="\t%s \t  %s\n"%(k,self._keys[k].getDType())
        return(out)
    def getKeyTypes(self):
        """Return the key types"""
        typ={}
        for k,v in self._keys.items():
            typ[k]=SepVector.dtypeToSepVecType[str(v.getDType())]
        return typ
    def getHeaderNumbers(self,**kw):
        """Get the header numbers assocaited with a window"""
        n_w,f_w,j_w=SepVector.fixWindow(self._gridHyper,**kw)
        n_g=self._gridHyper.getNs()
        nw=np.zeros(6)
        fw=np.zeros(6)
        jw=np.zeros(6)
        ng=np.zeros(6)
        nb=np.zeros(6)
        nb[0]=1
        for i in range(1,len(n_g)):
            nb[i]=n_b[i-1]*n_g[i]
            ng[i-1]=n_g[i]
            nw[i-1]=n_w[i]
            fw[i-1]=f_w[i]
            jw[i-1]=j_w[i]
        for i in range(len(n_g)-1,6):
            nb[i]=1
            nw[i]=1
            fw[i]=1
            jw[i]=1
        ntr=fastHeaderNumbers(ng,nw,fw,jw,nb,self._gridI)

    def gridData(self,axes):
        """
            Grid a data
            axes - n,o,d,key

            @return
             
             New header object with a grid 
        """
        arr=np.zeros((self._nh,8),dtype=np.int32)
        for i in range(len(axes)):
            if not axes[i].label in self._keys:
                raise Exception("Can not grid on unknown key %s axis=%d",axes[i].label,i+1)
            keyToInt(i,axes[i].n,axes[i].o,axes[i].d,self._keys[axes[i].label]._vals,arr)
        lst=arrToSortedTupleList(arr)
        n1,ngood=maxCellGood(lst)
        ns=numba.typed.List()
        n123=1
        for i in range(len(axes)):
            ns.append(axes[i].n)
            n123=n123*ns[i]
        for i in range(len(axes),6):
            ns.append(1)
        if n1==1:
            axes.insert(0,Hypercube.axis(n=1))
            gridHyper=Hypercube.hypercube(axes=axes)
            grdB=SepVector.getSepVector(ns=[n123],storage="dataByte")
            grdI,iorder=sortNoDuplicate(grdB.getNdArray(),lst,ns,n123,ngood)                
        else:
            ns.insert(0,n1)
            n123=n123*ns[0]
            axes.insert(0,Hypercube.axis(n=n1,label="trace_in_bin"))
            axes.insert(0,Hypercube.axis(n=1))
            gridHyper=Hypercube.hypercube(axes=axes)
            grdB=SepVector.getSepVector(ns=[n123],storage="dataByte")
            grdI,iorder=sortDuplicate(grdB.getNdArray(),lst,ns,n123,ngood,n1)
        headNew=headerBlock(nh=ngood)
        for k in self._keyOrder:
            a=np.zeros((ngood,),dtype=self._keys[k].getDType())
            extractKey(self._keys[k]._vals,iorder,a)
            headNew.addKey(k,vals=a)
        headNew._gridHyper=gridHyper
        headNew._grid=grdB
        headNew.gridI=grdI
        return headNew,iorder
@numba.jit(nopython=True)
def sortDuplicate(grdB,lst,ns,n123,ngood,n1):
    grdI=np.zeros(n123,dtype=np.int32)
    iorder=np.zeros(ngood,dtype=np.int32)
    nb=np.zeros(7,dtype=np.int64)
    nb[0]=1
    for i in range(6):
        nb[i+1]=nb[i]*ns[i+1]
    for i in range(grdB.shape[0]):
        grdI[i]=-1
    igood=0
    for i in range(len(lst)):
        if lst[i][7]==0:
            icell=lst[i][0]+nb[1]*lst[i][1]+nb[2]*lst[i][2]+nb[3]*lst[i][3]+nb[4]*lst[i][4]+nb[5]*lst[i][5]
            found=False
            ib=0
            while not found:
                if grdB[icell*n1+ib]==0:
                    found=True 
                else:
                    ib+=1
            grdB[icell*n1+ib]=1
            grdI[icell*n1+ib]=igood
            iorder[igood]=lst[i][6]
            igood+=1
    return grdI,iorder
@numba.jit(nopython=True)
def sortNoDuplicate(grdB,lst,ns,n123,ngood):
    grdI=np.zeros(n123,dtype=np.int32)
    iorder=np.zeros(ngood,dtype=np.int32)
    nb=np.zeros(7,dtype=np.int64)
    nb[0]=1
    for i in range(6):
        nb[i+1]=nb[i]*ns[i]
    for i in range(grdB.shape[0]):
        grdI[i]=-1
    igood=0
    for i in range(len(lst)):
        if lst[i][7]==0:
            icell=lst[i][0]+nb[1]*lst[i][1]+nb[2]*lst[i][2]+nb[3]*lst[i][3]+nb[4]*lst[i][4]+nb[5]*lst[i][5]
            grdB[icell]=1
            grdI[icell]=igood
            iorder[igood]=lst[i][6]
            igood+=1
    return grdI,iorder

            

        
@numba.jit(nopython=True)
def maxCellGood(lst):
    last=lst[0]
    nmax=1
    ncur=1
    ngood=0
    if last[7]==0:
        ngood=1
    for i in range(1,len(lst)):
        same=True
        if  lst[i][7]==0:
            ngood+=1
        good=True
        for j in range(6):
            if lst[i][j] != last[j]:
                good=False
        if not good:
            last=lst[i]
            if last[7]==0 and ncur >nmax:
                nmax=ncur
            ncur=1
        else:
            ncur+=1
    return nmax,ngood

def arrToSortedTupleList(arr):
    lst=numba.typed.List()
    for i in range(arr.shape[0]):
        lst.append(tuple([arr[i,0],arr[i,1],arr[i,2],arr[i,3],arr[i,4],arr[i,5],arr[i,6],arr[i,7]]))
    x= sorted(lst, key=operator.itemgetter(5,4,3,2,1,0))
    lst=numba.typed.List()
    for a in x:
        lst.append(a)
    return lst



@numba.jit(nopython=True)
def keyToInt(ikey,n,o,d,key,arr):
    for i in range(arr.shape[0]):
        arr[i,ikey]=round((key[i]-o)/d)
        if arr[i,ikey] < 0 or arr[i,ikey] >= n:
            arr[i,7]=1
        arr[i,6]=i 


@numba.jit(nopython=True)
def extractKey(inA,ith,outA):
    for i in range(ith.shape[0]):
        outA[i]=inA[ith[i]]

@numba.jit(nopython=True)
def insertKey(inA,ith,outA):
    for i in range(ith.shape[0]):
        outA[ith[i]]=inA[i]

@numba.jit(nopython=True)
def fastHeaderNumbers(ng,nw,fw,jw,nb,grd):
    itot=0
    for i5 in range(nw[5]):
        b5=(fw[5]+jw[5]*i5)*nb[5]
        for i4 in range(nw[4]):
            b4=(fw[4]+jw[4]*i4)*nb[4]
            for i3 in range(nw[3]):
                b3=(fw[3]+jw[3]*i3)*nb[3]
                for i2 in range(nw[2]):
                    b2=(fw[2]+jw[2]*i2)*nb[2]
                    for i1 in range(nw[1]):
                        b5=(fw[1]+jw[1]*i1)*nb[1]
                        for i0 in range(nw[0]):
                            i=fw[0]+jw[0]*i0+b1+b2+b3+b4+b5
                            if grd[i]>=-1:
                                itot+=1
    itrs=np.zeros(itot,dtype=np.int32)
    itot=0
    for i5 in range(nw[5]):
        b5=(fw[5]+jw[5]*i5)*nb[5]
        for i4 in range(nw[4]):
            b4=(fw[4]+jw[4]*i4)*nb[4]
            for i3 in range(nw[3]):
                b3=(fw[3]+jw[3]*i3)*nb[3]
                for i2 in range(nw[2]):
                    b2=(fw[2]+jw[2]*i2)*nb[2]
                    for i1 in range(nw[1]):
                        b5=(fw[1]+jw[1]*i1)*nb[1]
                        for i0 in range(nw[0]):
                            i=fw[0]+jw[0]*i0+b1+b2+b3+b4+b5
                            if grd[i]>=-1:
                                itrs[itot]=grd[i]
                                itot+=1 
    return itrs 

    

@numba.jit(nopython=True)
def createGrid(byteA,intA):
    i=0
    for i in numba.range(byte.shape[0]):
        if byteA[i]>0:
            intA[i]=i 
            i=i+1
        else:
            intA[i]=-1

class vector(pyVector.vectorIC):
    def __init__(self,**kw):
        """A block of traces with headers

            Method 1 (pass in all the components):
             traces = 2-D sepVector
             header  = A header block

             Method2:
             hyper = 2-D Hypercube with nt,ntraces
             dataType  = Type of data we are going to store (defaults to dataFloat)
        """
        if "traces" in kw:
            if not "header"  in kw:
                raise Exception("When providing traces must also provide header")
            self._header=kw["header"]
            if not isinstance(self._header,headerBlock):
                raise Exception("Expecting header to be a headerblock")
            
            if not isinstance(kw["traces"],SepVector.vector):
                raise Exception("Expecting keys to be a SepVector.vector")
            self._traces=kw["traces"]
            self._hyper=self._traces.getHyper()
            if len(self._hyper.axes)!=2:
                raise Exception("Only support 2-D hypercube. Axes size ",len(self._hyper.axes))
            if self._header._nh != self._hyper.axes[1].n:
                raise Exception("Header and data don't have the same number of traces")
        elif "hyper" in kw:
            self._hyper=kw["hyper"]
            if not isinstance(self._hyper,Hypercube.hypercube):
                raise Exception("Expecting hyper to be hypercube")
            if not "dataType" in kw:
                kw["dataType"]="dataFloat"
                self._traces=SepVector.getSepVector(hyper,storage=kw["dataType"])
            self._headers=headers(self._hyper.axes[1].n)
            
        super().__init__(self._traces.getNdArray())
    def clip(self, bclip, eclip):
        """Clip dataset
                bclip - Minimum value to clip to
                eclip - Maximum value to clip to"""
        self._traces.clip(bclip,eclip)
    def cent(self, pct, jsamp=1):
        """Calculate the percentile of a dataset
                pct - Percentile of the dataset
                jsamp - Sub-sampling of dartaset"""
        return self._traces.cent(pct, jsamp)

    def getStorageType(self):
        """Return type of storage"""
        return self._traces.getStorageType()

    def zero(self):
        """Function to zero out a vector"""
        self._traces.zero()
        return self

    def set(self, val):
        """Function to a vector to a value"""
        self._traces.set(val)
        return self

    def getHyper(self):
        """Return the hypercube associated with the vector"""
        return self._hyper

    def getNdArray(self):
        """Return a numpy version of the array (same memory"""
        return self._traces.getNdArray()
    def getHyper(self):
        """Get the hypercube associated with dataset"""
        axes=[]
        axes.append(self._traces.getHyper().axes[0])
        if self._header._gridHyper:
            for i in range(1,len(self._header._gridHyper.axes)):
                axes.append(self._header._gridHyper.axes[i])
        else:
            axes.append(Hypercube.axis(n=self._header._nh))
        return Hypercube.hypercube(axes=axes)

    def checkSame(self, vec2):
        """Function to check if two vectors belong to the same vector space"""
        if not isinstance(vec2,vector):
            return False
        return self._header.checkSame(vec2._header)

    def norm(self, N=2):
        """Function to compute vector N-norm"""
        self._traces.norm(N)
        return self
    def scale(self, sc):
        """Function to scale a vector"""
        self._traces.scale(sc)
        return self

    def __repr__(self):
        """Override print method"""
        return "Irregular vector \n%s\n%s"%(str(self._header),str(self._traces))


    def rand(self):
        """Function to fill with random numbers"""
        self._traces.rand()
        return self

    def clone(self):
        """Function to clone (deep copy) a vector"""
        return vector(traces=self._traces.clone(), header=self._header.clone())

    def clipVector(self, low, high):
        """Clip vector element by element vec=min(high,max(low,vec))"""
        self._traces.clipVector(low,high)
        return self

    def cloneSpace(self):
        """Funtion tor return the space of a vector"""
        return vector(traces=self._traces.cloneSpace(),header=self._header.clonseSpace())

    def scaleAdd(self, vec2, sc1=1., sc2=1.):
        """self = self * sc1 + sc2 * vec2"""
        self._traces.scaleAdd(vec2, sc1, sc2)
        return self

    def copy(self, vec2):
        """Copy vec2 into self"""
        self._traces.scaleAdd(vec2, 0., 1.)
        return self

    def dot(self, vec2):
        """Compute dot product of two vectors"""
        return self._traces.dot(vec2.cppMode)

    def multiply(self, vec2):
        """self = vec2 * self"""
        self._traces.mult(vec2.cppMode)
        return self

    def norm(self, nrm=2):
        """Return the norm of a vector"""
        return self._traces.norm(nrm)


    def enableGridAccess(self):
        """Create the ability to access through grid coordinates"""
        self._header.enableGridAccess()
    
    def getGridWindow(self,**kw):
        """Get a header window from the grid
           n#,f#,j# - Windowing parameters

            @returns traceBlock
        
        """
        header,traceNums=self._heaeder.getGridWindow(nwind,fwind,jwind)
        ax2=Hypercube.axis(n=traceNums.shape[0]);
        hyper=Hypercube.hypercube(axes=[self._hyper.axes[0],ax2])
        dat=SepVector.getSepVector(hyper,storage=self.traces.getStorageType())
        getTraces(traceNum,self._traces.getNdArray(),dat.getNdArray())
        return vector(traces=dat,header=header)
    
    def putGridWindow(self,block,**kw):
            """Put header window from the grid
            
           n#,f#,j# - Windowing parameters
            headers - Headerblock

            """
            traceNums=self._header.putGridWindow(nwind,fwind,jwind,block._header)
            putTraces(traceNum,block._traces,self._traces)
    def gridData(self,axes):
        """
            Grid a data
            axes - n,o,d,key

            @return
             
             New header object with a grid 
        """
        head,iorder=self._header.gridData(axes)
        axs=[]
        axs.append(self._traces.getHyper().axes[0])
        axs.append(Hypercube.axis(n=iorder.shape[0]))
        trNew=SepVector.getSepVector(axes=axs,storage=self._traces.getStorageType())
        getTraces(iorder,self._traces.getNdArray(),trNew.getNdArray())
        return vector(traces=trNew,header=head)

@numba.jit(nopython=True,parallel=True)
def getTraces(num,ina,outa):
    """Copy traces from big to small"""
    for i2 in numba.prange(num.shape[0]):
        for i1 in range(ina.shape[1]):
            outa[i2,i1]=ina[num[i2],i1]
@numba.jit(nopython=True,parallel=True)
def putTraces(num,ina,outa):
    """Copy traces from small to big"""
    for i2 in numba.prange(num.shape[0]):
        outa[num[i2],:]=ina[i2,:]   
