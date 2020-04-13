import unittest
import Hypercube
import SepIrregVector
import SepVector
import numpy as np

class TestIrreg(unittest.TestCase):

    def testKey(self):
        x=np.zeros(5,dtype=np.float32)
        x[0]=5
        x[1]=4
        x[2]=3
        x[3]=2
        x[4]=1
        ky=SepIrregVector.key(x)
        self.assertEqual(ky[0],5.)
        self.assertEqual(ky[1],4.)
        ky[0]=9.
        self.assertEqual(ky._vals[0],9.)
        self.assertEqual(5,ky.size())
        self.assertEqual(np.float32,ky.getDType())
    def testHeader(self):
        x=np.zeros(5,dtype=np.float32)
        x[0]=5
        x[1]=4
        x[2]=3
        x[3]=2
        x[4]=1
        ky=SepIrregVector.key(x)
        head=SepIrregVector.headerBlock(keys=dict(s_x=ky))
        self.assertEqual(head.s_x[0],5.)
        x[0]=9
        head.addKey("s_y",vals=x)
        self.assertEqual(head.s_x[0],5.)
        self.assertEqual(head.s_y[0],9.)
        head2=head.clone()
        self.assertEqual(head2.s_x[0],5.)
        self.assertEqual(head2.s_y[0],9.)
        self.assertTrue(head.checkSame(head2))
        head3=head.cloneSpace()
        self.assertTrue(head.checkSame(head3))
    def testGridding(self):
        x=np.zeros(10,dtype=np.float32)
        y=np.zeros(10,dtype=np.float32)
        for i in range(10):
            x[i]=i 
            y[i]=10-i
        head=SepIrregVector.headerBlock(keys=dict(s_x=SepIrregVector.key(x),s_y=SepIrregVector.key(y)))
        
        axes=[]
        axes.append(Hypercube.axis(n=10,o=0,d=1,label="s_x"))
        axes.append(Hypercube.axis(n=10,o=0,d=1,label="s_y"))
        head2=head.gridData(axes)[0]
        self.assertEqual(head2._nh,9)
        self.assertEqual(head2.s_x[0],9.)
        self.assertEqual(head2.s_y[0],1.)
        axes=[]
        axes.append(Hypercube.axis(n=3,o=0,d=3,label="s_x"))
        axes.append(Hypercube.axis(n=3,o=0,d=3,label="s_y"))        
        head3=head.gridData(axes)[0]
        self.assertEqual(head3._nh,5)
        self.assertEqual(head3.s_x[0],6.)
        self.assertEqual(head3.s_y[0],4.)


if __name__ == '__main__':
    unittest.main()
