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
            self.cppMode = self.kw["fromCpp"]
        elif "fromHyper" in self.kw:
            self.cppMode = getCppSepVector(self.kw["fromHyper"], self.kw)

    def getCpp(self):
        """Return the associated cpp object"""
        return self.cppMode

    def clip(self, bclip, eclip):
        """Clip dataset
                bclip - Minimum value to clip to
                eclip - Maximum value to clip to"""
        self.cppMode.clip(bclip, eclip)

    def cent(self, pct, jsamp=1):
        """Calculate the percentile of a dataset
                pct - Percentile of the dataset
                jsamp - Sub-sampling of dartaset"""
        return self.cppMode.cent(pct, jsamp)

    def getStorageType(self):
        """Return type of storage"""
        return self.storage

    def zero(self):
        """Function to zero out a vector"""
        self.cppMode.set(0.)

    def set(self, val):
        """Function to a vector to a value"""
        self.cppMode.set(val)

    def getHyper(self):
        """Return the hypercube associated with the vector"""
        return Hypercube.hypercube(hypercube=self.cppMode.getHyper())

    def getNdArray(self):
        """Return a numpy version of the array (same memory"""
        return numpy.array(self.cppMode, copy=False)

    def window(self, **kw):
        """Window a vector return another vector (of the same dimension
            specify min1..min6, max1...max6, f1...f6, j1...j6, n1...n6, or
            any of these by lists.
            Can not specify n and min or max """
        axes = self.getHyper().axes
        ndim = len(axes)
        for i in range(1, ndim + 1):
            nset = False
            fset = False
            jset = False
            if "n%d" % i in kw:
                nset = True
                n = int(kw["n%d" % i])
            if "f%d" % i in kw:
                jset = True
                j = int(kw["j%d" % i])
            if "j%d" % i in kw:
                fset = True
                f = int(kw["f%d" % i])
            biSet = False
            eiSet = False
            if "min%d" % i in kw:
                bi = int(float(kw["min" %
                                  i] - axes[i - 1].o) / axes[i - 1].d + .5)
                biSet = True
            if "max%d" % i in kw:
                ei = int(float(kw["max" %
                                  i] - axes[i - 1].o) / axes[i - 1].d + .5)
                eiSet = True
            if fset:
                if axes[i - 1].n <= f:
                    raise Exception(
                        "invalid f%d=%d parameter n%d of data=%d" %
                        (i, f, i, axes[
                            i - 1].n))
            if nset:
                if axes[i - 1].n < n:
                    raise Exception(
                        "invalid n%d=%d parameter n%d of data=%d" %
                        (i, n, i, axes[
                            i - 1].n))
            if jset and j <= 0:
                raise Exception("invalid j%d=%d " % (i, j))
            if not jset:
                j = 1
            if not nset:
                if not fset:
                    if not biSet:
                        f = 0
                    elif bi < 0 or bi >= axes[i - 1].n:
                        raise Exception("Invalid min%d=%f" %
                                        (i, kw["min%d" % i]))
                    else:
                        f = bi
                if eiSet:
                    if ei <= f or ei >= axes[i - 1].n:
                        raise Exception("Invalid max%d=%f" %
                                        (i, kw["max%d" % i]))
                    else:
                        n = (ei - f - 1) / j + 1
                if not biSet and not eiSet and not jset and not fset:
                    n = axes[i - 1].n
                    j = 1
                    f = 0
        