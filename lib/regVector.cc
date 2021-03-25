#include "regVector.h"
#include "sepVectorConfig.h"
using namespace SEP;
std::shared_ptr<regSpace> SEP::vecFromHyper(
    const std::shared_ptr<hypercube> hyper, const dataType typ, const bool g1)
{
    std::vector<axis> axesIn = hyper->getAxes(), axesOut;
    int ndim = hyper->getNdim();
    if (g1)
        ndim = hyper->getNdimG1();
    for (int i = 0; i < ndim; i++)
    {
        axesOut.push_back(axesIn[i]);
    }

    std::shared_ptr<hypercube> hyper2(new hypercube(axesOut));
    switch (typ)
    {
    case DATA_FLOAT:
        switch (ndim)
        {
        case 1:
        {
            std::shared_ptr<float1DReg> a(new float1DReg(hyper2));
            return a;
        }
        break;
        case 2:
        {
            std::shared_ptr<float2DReg> a(new float2DReg(hyper2));
            return a;
        }
        break;
        case 3:
        {
            std::shared_ptr<float3DReg> a(new float3DReg(hyper2));
            return a;
        }
        break;
        case 4:
        {
            std::shared_ptr<float4DReg> a(new float4DReg(hyper2));
            return a;
        }
        break;
        case 5:
        {
            std::shared_ptr<float5DReg> a(new float5DReg(hyper2));
            return a;
        }
        break;
        case 6:
        {
            std::shared_ptr<float6DReg> a(new float6DReg(hyper2));
            return a;
        }
        break;
        case 7:
        {
            std::shared_ptr<float7DReg> a(new float7DReg(hyper2));
            return a;
        }
        break;
        }
        break;
    case DATA_COMPLEXDOUBLE:
        switch (ndim)
        {
        case 1:
        {
            std::shared_ptr<complexDouble1DReg> a(new complexDouble1DReg(hyper2));
            return a;
        }
        break;
        case 2:
        {
            std::shared_ptr<complexDouble2DReg> a(new complexDouble2DReg(hyper2));
            return a;
        }
        break;
        case 3:
        {
            std::shared_ptr<complexDouble3DReg> a(new complexDouble3DReg(hyper2));
            return a;
        }
        break;
        case 4:
        {
            std::shared_ptr<complexDouble4DReg> a(new complexDouble4DReg(hyper2));
            return a;
        }
        break;
        case 5:
        {
            std::shared_ptr<complexDouble5DReg> a(new complexDouble5DReg(hyper2));
            return a;
        }
        break;
        case 6:
        {
            std::shared_ptr<complexDouble6DReg> a(new complexDouble6DReg(hyper2));
            return a;
        }
        break;
        case 7:
        {
            std::shared_ptr<complexDouble7DReg> a(new complexDouble7DReg(hyper2));
            return a;
        }
        break;
        }

    case DATA_COMPLEX:
        switch (ndim)
        {
        case 1:
        {
            std::shared_ptr<complex1DReg> a(new complex1DReg(hyper2));
            return a;
        }
        break;
        case 2:
        {
            std::shared_ptr<complex2DReg> a(new complex2DReg(hyper2));
            return a;
        }
        break;
        case 3:
        {
            std::shared_ptr<complex3DReg> a(new complex3DReg(hyper2));
            return a;
        }
        break;
        case 4:
        {
            std::shared_ptr<complex4DReg> a(new complex4DReg(hyper2));
            return a;
        }
        break;
        case 5:
        {
            std::shared_ptr<complex5DReg> a(new complex5DReg(hyper2));
            return a;
        }
        break;
        case 6:
        {
            std::shared_ptr<complex6DReg> a(new complex6DReg(hyper2));
            return a;
        }
        break;
        case 7:
        {
            std::shared_ptr<complex7DReg> a(new complex7DReg(hyper2));
            return a;
        }
        break;
        }

        break;
    case DATA_BYTE:
        switch (ndim)
        {
        case 1:
        {
            std::shared_ptr<byte1DReg> a(new byte1DReg(hyper2));
            return a;
        }
        break;
        case 2:
        {
            std::shared_ptr<byte2DReg> a(new byte2DReg(hyper2));
            return a;
        }
        break;
        case 3:
        {
            std::shared_ptr<byte3DReg> a(new byte3DReg(hyper2));
            return a;
        }
        break;
        case 4:
        {
            std::shared_ptr<byte4DReg> a(new byte4DReg(hyper2));
            return a;
        }
        break;
        case 5:
        {
            std::shared_ptr<byte5DReg> a(new byte5DReg(hyper2));
            return a;
        }
        break;
        case 6:
        {
            std::shared_ptr<byte6DReg> a(new byte6DReg(hyper2));
            return a;
        }
        break;
        }

        break;
    case DATA_SHORT:
        switch (ndim)
        {
        case 1:
        {
            std::shared_ptr<short1DReg> a(new short1DReg(hyper2));
            return a;
        }
        break;
        }
        break;
    case DATA_INT:
        switch (ndim)
        {
        case 1:
        {
            std::shared_ptr<int1DReg> a(new int1DReg(hyper2));
            return a;
        }
        break;
        case 2:
        {
            std::shared_ptr<int2DReg> a(new int2DReg(hyper2));
            return a;
        }
        break;
        case 3:
        {
            std::shared_ptr<int3DReg> a(new int3DReg(hyper2));
            return a;
        }
        break;
        case 4:
        {
            std::shared_ptr<int4DReg> a(new int4DReg(hyper2));
            return a;
        }
        break;
        case 5:
        {
            std::shared_ptr<int5DReg> a(new int5DReg(hyper2));
            return a;
        }
        break;
        case 6:
        {
            std::shared_ptr<int6DReg> a(new int6DReg(hyper2));
            return a;
        }
        break;
        }

        break;
    case DATA_DOUBLE:
        switch (ndim)
        {
        case 1:
        {
            std::shared_ptr<double1DReg> a(new double1DReg(hyper2));
            return a;
        }
        break;
        case 2:
        {
            std::shared_ptr<double2DReg> a(new double2DReg(hyper2));
            return a;
        }
        break;
        case 3:
        {
            std::shared_ptr<double3DReg> a(new double3DReg(hyper2));
            return a;
        }
        break;
        case 4:
        {
            std::shared_ptr<double4DReg> a(new double4DReg(hyper2));
            return a;
        }
        break;
        case 5:
        {
            std::shared_ptr<double5DReg> a(new double5DReg(hyper2));
            return a;
        }
        break;
        case 6:
        {
            std::shared_ptr<double6DReg> a(new double6DReg(hyper2));
            return a;
        }
        break;
        case 7:
        {
            std::shared_ptr<double7DReg> a(new double7DReg(hyper2));
            return a;
        }
        break;
        }

        break;
    default:
        throw(SEPException(std::string("Unhandled data type")));
    }
    return nullptr;
}

std::shared_ptr<regSpace> SEP::tensorFromHyper(
    const std::shared_ptr<hypercube> hyper, const dataType typ, const bool g1)
{
    std::vector<axis> axesIn = hyper->getAxes(), axesOut;
    int ndim = hyper->getNdim();
    if (g1)
        ndim = hyper->getNdimG1();
    for (int i = 0; i < ndim; i++)
    {
        axesOut.push_back(axesIn[i]);
    }

    std::shared_ptr<hypercube> hyper2(new hypercube(axesOut));
    switch (typ)
    {
    case DATA_FLOAT:
        switch (ndim)
        {
        case 1:
        {
            std::shared_ptr<floatTensor1D> a(new floatTensor1D(hyper2));
            return a;
        }
        break;
        case 2:
        {
            std::shared_ptr<floatTensor2D> a(new floatTensor2D(hyper2));
            return a;
        }
        break;
        case 3:
        {
            std::shared_ptr<floatTensor3D> a(new floatTensor3D(hyper2));
            return a;
        }
        break;
        case 4:
        {
            std::shared_ptr<floatTensor4D> a(new floatTensor4D(hyper2));
            return a;
        }
        break;
        case 5:
        {
            std::shared_ptr<floatTensor5D> a(new floatTensor5D(hyper2));
            return a;
        }
        break;
        case 6:
        {
            std::shared_ptr<floatTensor6D> a(new floatTensor6D(hyper2));
            return a;
        }
        break;
        case 7:
        {
            std::shared_ptr<floatTensor7D> a(new floatTensor7D(hyper2));
            return a;
        }
        break;
        }
        break;
    case DATA_COMPLEXDOUBLE:
        switch (ndim)
        {
        case 1:
        {
            std::shared_ptr<complexDoubleTensor1D> a(new complexDoubleTensor1D(hyper2));
            return a;
        }
        break;
        case 2:
        {
            std::shared_ptr<complexDoubleTensor2D> a(new complexDoubleTensor2D(hyper2));
            return a;
        }
        break;
        case 3:
        {
            std::shared_ptr<complexDoubleTensor3D> a(new complexDoubleTensor3D(hyper2));
            return a;
        }
        break;
        case 4:
        {
            std::shared_ptr<complexDoubleTensor4D> a(new complexDoubleTensor4D(hyper2));
            return a;
        }
        break;
        case 5:
        {
            std::shared_ptr<complexDoubleTensor5D> a(new complexDoubleTensor5D(hyper2));
            return a;
        }
        break;
        case 6:
        {
            std::shared_ptr<complexDoubleTensor6D> a(new complexDoubleTensor6D(hyper2));
            return a;
        }
        break;
        case 7:
        {
            std::shared_ptr<complexDoubleTensor7D> a(new complexDoubleTensor7D(hyper2));
            return a;
        }
        break;
        }

    case DATA_COMPLEX:
        switch (ndim)
        {
        case 1:
        {
            std::shared_ptr<complexTensor1D> a(new complexTensor1D(hyper2));
            return a;
        }
        break;
        case 2:
        {
            std::shared_ptr<complexTensor2D> a(new complexTensor2D(hyper2));
            return a;
        }
        break;
        case 3:
        {
            std::shared_ptr<complexTensor3D> a(new complexTensor3D(hyper2));
            return a;
        }
        break;
        case 4:
        {
            std::shared_ptr<complexTensor4D> a(new complexTensor4D(hyper2));
            return a;
        }
        break;
        case 5:
        {
            std::shared_ptr<complexTensor5D> a(new complexTensor5D(hyper2));
            return a;
        }
        break;
        case 6:
        {
            std::shared_ptr<complexTensor6D> a(new complexTensor6D(hyper2));
            return a;
        }
        break;
        case 7:
        {
            std::shared_ptr<complexTensor7D> a(new complexTensor7D(hyper2));
            return a;
        }
        break;
        }

        break;
    case DATA_BYTE:
        switch (ndim)
        {
        case 1:
        {
            std::shared_ptr<byteTensor1D> a(new byteTensor1D(hyper2));
            return a;
        }
        break;
        case 2:
        {
            std::shared_ptr<byteTensor2D> a(new byteTensor2D(hyper2));
            return a;
        }
        break;
        case 3:
        {
            std::shared_ptr<byteTensor3D> a(new byteTensor3D(hyper2));
            return a;
        }
        break;
        case 4:
        {
            std::shared_ptr<byteTensor4D> a(new byteTensor4D(hyper2));
            return a;
        }
        break;
        case 5:
        {
            std::shared_ptr<byteTensor5D> a(new byteTensor5D(hyper2));
            return a;
        }
        break;
        case 6:
        {
            std::shared_ptr<byteTensor6D> a(new byteTensor6D(hyper2));
            return a;
        }
        break;
        case 7:
        {
            std::shared_ptr<byteTensor7D> a(new byteTensor7D(hyper2));
            return a;
        }
        break;
        }

        break;
    case DATA_SHORT:
        switch (ndim)
        {
        case 1:
        {
            std::shared_ptr<shortTensor1D> a(new shortTensor1D(hyper2));
            return a;
        }
        break;
        case 2:
        {
            std::shared_ptr<shortTensor2D> a(new shortTensor2D(hyper2));
            return a;
        }
        break;
        case 3:
        {
            std::shared_ptr<shortTensor3D> a(new shortTensor3D(hyper2));
            return a;
        }
        break;
        case 4:
        {
            std::shared_ptr<shortTensor4D> a(new shortTensor4D(hyper2));
            return a;
        }
        break;
        case 5:
        {
            std::shared_ptr<shortTensor5D> a(new shortTensor5D(hyper2));
            return a;
        }
        break;
        case 6:
        {
            std::shared_ptr<shortTensor6D> a(new shortTensor6D(hyper2));
            return a;
        }
        break;
        case 7:
        {
            std::shared_ptr<shortTensor7D> a(new shortTensor7D(hyper2));
            return a;
        }
        break;
        }

    case DATA_INT:
        switch (ndim)
        {
        case 1:
        {
            std::shared_ptr<intTensor1D> a(new intTensor1D(hyper2));
            return a;
        }
        break;
        case 2:
        {
            std::shared_ptr<intTensor2D> a(new intTensor2D(hyper2));
            return a;
        }
        break;
        case 3:
        {
            std::shared_ptr<intTensor3D> a(new intTensor3D(hyper2));
            return a;
        }
        break;
        case 4:
        {
            std::shared_ptr<intTensor4D> a(new intTensor4D(hyper2));
            return a;
        }
        break;
        case 5:
        {
            std::shared_ptr<intTensor5D> a(new intTensor5D(hyper2));
            return a;
        }
        break;
        case 6:
        {
            std::shared_ptr<intTensor6D> a(new intTensor6D(hyper2));
            return a;
        }
        break;
        case 7:
        {
            std::shared_ptr<intTensor7D> a(new intTensor7D(hyper2));
            return a;
        }
        break;
        }

        break;
    case DATA_DOUBLE:
        switch (ndim)
        {
        case 1:
        {
            std::shared_ptr<doubleTensor1D> a(new doubleTensor1D(hyper2));
            return a;
        }
        break;
        case 2:
        {
            std::shared_ptr<doubleTensor2D> a(new doubleTensor2D(hyper2));
            return a;
        }
        break;
        case 3:
        {
            std::shared_ptr<doubleTensor3D> a(new doubleTensor3D(hyper2));
            return a;
        }
        break;
        case 4:
        {
            std::shared_ptr<doubleTensor4D> a(new doubleTensor4D(hyper2));
            return a;
        }
        break;
        case 5:
        {
            std::shared_ptr<doubleTensor5D> a(new doubleTensor5D(hyper2));
            return a;
        }
        break;
        case 6:
        {
            std::shared_ptr<doubleTensor6D> a(new doubleTensor6D(hyper2));
            return a;
        }
        break;
        case 7:
        {
            std::shared_ptr<doubleTensor7D> a(new doubleTensor7D(hyper2));
            return a;
        }
        break;
        }

        break;
    default:
        throw(SEPException(std::string("Unhandled data type")));
    }
    return nullptr;
}

std::shared_ptr<regSpace> SEP::subCubeFromHyper(
    const std::shared_ptr<hypercube> hyper, const dataType typ,
    const int &ndim)
{
    std::vector<axis> axesIn = hyper->getAxes(), axesOut;

    for (int i = 0; i < ndim; i++)
    {
        axesOut.push_back(axesIn[i]);
    }
    std::shared_ptr<hypercube> hyper2(new hypercube(axesOut));
    return vecFromHyper(hyper2, typ);
    return nullptr;
}
/*
std::shared_ptr<regSpace> SEP::windowFromHyper(
    const std::shared_ptr<hypercube> hyper, const std::vector<int> &nw,
    const std::vector<int> &fw, const std::vector<int> &jw,
    const dataType typ) {
  size_t nbigest = 0;
  for (int i = 0; i < nw.size(); i++) {
    if (nw[i] > 1) nbigest = i;
  }
  if (hyper->getNdim() <= nbiggest)
    throw(SEPException(std::string("hyper ndim=") +
                       std::to_string(hyper->getNdim()) +
                       std::string(" nibiggest=") + std::to_string(nbiggest)));

  if (nbiggest > fw.size())
    throw(SEPException(std::string("nbiggest[") + std::to_string(nbiggest) +
                       std::string("] > fw.size()[") +
                       std::to_string(nbiggest) + std::to_string("]")));

  std::vector<axis> axes = hyper->getAxes(), axesOut;
  for (int i = 0; i < nbigest; i++) {
    checkWindow(axes[i].n, nw[i], fw[i], jw[i]);
    axis a(nw[i], axes[i].o + axes[i].d * fw[i], jw[i] * axes[i].d,
           axes[i].label);
    axesOut.push_back(a);
  }
  std::shared_ptr<hypercube> hyper2(new hypercube(axesOut));
  return vecFromHyper(hyper2, typ);
}
*/
std::shared_ptr<regSpace> SEP::cloneRegSpace(
    std::shared_ptr<regSpace> storage)
{
    std::shared_ptr<float1DReg> v1 =
        std::dynamic_pointer_cast<float1DReg>(storage);
    if (v1)
        return v1->clone();

    std::shared_ptr<float2DReg> v2 =
        std::dynamic_pointer_cast<float2DReg>(storage);
    if (v2)
        return v2->clone();

    std::shared_ptr<float3DReg> v3 =
        std::dynamic_pointer_cast<float3DReg>(storage);
    if (v3)
        return v3->clone();

    std::shared_ptr<float4DReg> v4 =
        std::dynamic_pointer_cast<float4DReg>(storage);
    if (v4)
        return v4->clone();

    std::shared_ptr<float5DReg> v5 =
        std::dynamic_pointer_cast<float5DReg>(storage);
    if (v5)
        return v5->clone();

    std::shared_ptr<float6DReg> v6 =
        std::dynamic_pointer_cast<float6DReg>(storage);
    if (v6)
        return v6->clone();
    std::shared_ptr<float7DReg> v7 =
        std::dynamic_pointer_cast<float7DReg>(storage);
    if (v7)
        return v7->clone();
    std::shared_ptr<int1DReg> va = std::dynamic_pointer_cast<int1DReg>(storage);
    if (va)
        return va->clone();

    std::shared_ptr<int2DReg> vb = std::dynamic_pointer_cast<int2DReg>(storage);
    if (vb)
        return vb->clone();

    std::shared_ptr<int3DReg> vc = std::dynamic_pointer_cast<int3DReg>(storage);
    if (vc)
        return vc->clone();

    std::shared_ptr<int4DReg> vd = std::dynamic_pointer_cast<int4DReg>(storage);
    if (vd)
        return vd->clone();

    std::shared_ptr<int5DReg> ve = std::dynamic_pointer_cast<int5DReg>(storage);
    if (ve)
        return ve->clone();

    std::shared_ptr<int6DReg> vf = std::dynamic_pointer_cast<int6DReg>(storage);
    if (vf)
        return vf->clone();

    std::shared_ptr<byte1DReg> vg = std::dynamic_pointer_cast<byte1DReg>(storage);
    if (vg)
        return vg->clone();

    std::shared_ptr<byte2DReg> vh = std::dynamic_pointer_cast<byte2DReg>(storage);
    if (vh)
        return vh->clone();

    std::shared_ptr<byte3DReg> vi = std::dynamic_pointer_cast<byte3DReg>(storage);
    if (vi)
        return vi->clone();

    std::shared_ptr<byte4DReg> vj = std::dynamic_pointer_cast<byte4DReg>(storage);
    if (vj)
        return vj->clone();

    std::shared_ptr<byte5DReg> vk = std::dynamic_pointer_cast<byte5DReg>(storage);
    if (vk)
        return vk->clone();

    std::shared_ptr<byte6DReg> vl = std::dynamic_pointer_cast<byte6DReg>(storage);
    if (vl)
        return vl->clone();

    std::shared_ptr<complex1DReg> vm =
        std::dynamic_pointer_cast<complex1DReg>(storage);
    if (vm)
        return vm->clone();

    std::shared_ptr<complex2DReg> vn =
        std::dynamic_pointer_cast<complex2DReg>(storage);
    if (vn)
        return vn->clone();

    std::shared_ptr<complex3DReg> vo =
        std::dynamic_pointer_cast<complex3DReg>(storage);
    if (vo)
        return vo->clone();

    std::shared_ptr<complex4DReg> vp =
        std::dynamic_pointer_cast<complex4DReg>(storage);
    if (vp)
        return vp->clone();

    std::shared_ptr<complex5DReg> vq =
        std::dynamic_pointer_cast<complex5DReg>(storage);
    if (vq)
        return vq->clone();

    std::shared_ptr<complex6DReg> vr =
        std::dynamic_pointer_cast<complex6DReg>(storage);
    if (vr)
        return vr->clone();
    std::shared_ptr<complex7DReg> vs =
        std::dynamic_pointer_cast<complex7DReg>(storage);
    if (vs)
        return vs->clone();
    {
        std::shared_ptr<complexDouble1DReg> vm =
            std::dynamic_pointer_cast<complexDouble1DReg>(storage);
        if (vm)
            return vm->clone();

        std::shared_ptr<complexDouble2DReg> vn =
            std::dynamic_pointer_cast<complexDouble2DReg>(storage);
        if (vn)
            return vn->clone();

        std::shared_ptr<complexDouble3DReg> vo =
            std::dynamic_pointer_cast<complexDouble3DReg>(storage);
        if (vo)
            return vo->clone();

        std::shared_ptr<complexDouble4DReg> vp =
            std::dynamic_pointer_cast<complexDouble4DReg>(storage);
        if (vp)
            return vp->clone();

        std::shared_ptr<complexDouble5DReg> vq =
            std::dynamic_pointer_cast<complexDouble5DReg>(storage);
        if (vq)
            return vq->clone();

        std::shared_ptr<complexDouble6DReg> vr =
            std::dynamic_pointer_cast<complexDouble6DReg>(storage);
        if (vr)
            return vr->clone();
        std::shared_ptr<complexDouble7DReg> vs =
            std::dynamic_pointer_cast<complexDouble7DReg>(storage);
        if (vs)
            return vs->clone();
    }
    {
        std::shared_ptr<double1DReg> vs =
            std::dynamic_pointer_cast<double1DReg>(storage);
        if (vs)
            return vs->clone();

        std::shared_ptr<double2DReg> vt =
            std::dynamic_pointer_cast<double2DReg>(storage);
        if (vt)
            return vt->clone();

        std::shared_ptr<double3DReg> vu =
            std::dynamic_pointer_cast<double3DReg>(storage);
        if (vu)
            return vu->clone();

        std::shared_ptr<double4DReg> vv =
            std::dynamic_pointer_cast<double4DReg>(storage);
        if (vv)
            return vv->clone();

        std::shared_ptr<double5DReg> vw =
            std::dynamic_pointer_cast<double5DReg>(storage);
        if (vw)
            return vw->clone();

        std::shared_ptr<double6DReg> vx =
            std::dynamic_pointer_cast<double6DReg>(storage);
        if (vx)
            return vx->clone();
        std::shared_ptr<double7DReg> vy =
            std::dynamic_pointer_cast<double7DReg>(storage);
        if (vy)
            return vy->clone();

        std::shared_ptr<byteTensor1D> aa1 =
            std::dynamic_pointer_cast<byteTensor1D>(storage);
        if (aa1)
            return aa1->clone();

        std::shared_ptr<byteTensor2D> aa2 =
            std::dynamic_pointer_cast<byteTensor2D>(storage);
        if (aa2)
            return aa2->clone();
        std::shared_ptr<byteTensor3D> aa3 =
            std::dynamic_pointer_cast<byteTensor3D>(storage);
        if (aa3)
            return aa3->clone();
        std::shared_ptr<byteTensor4D> aa4 =
            std::dynamic_pointer_cast<byteTensor4D>(storage);
        if (aa4)
            return aa4->clone();
        std::shared_ptr<byteTensor5D> aa5 =
            std::dynamic_pointer_cast<byteTensor5D>(storage);
        if (aa5)
            return aa5->clone();
        std::shared_ptr<byteTensor6D> aa6 =
            std::dynamic_pointer_cast<byteTensor6D>(storage);
        if (aa6)
            return aa6->clone();
        std::shared_ptr<byteTensor7D> aa7 =
            std::dynamic_pointer_cast<byteTensor7D>(storage);
        if (aa7)
            return aa7->clone();

        std::shared_ptr<complexTensor1D> ab1 =
            std::dynamic_pointer_cast<complexTensor1D>(storage);
        if (ab1)
            return ab1->clone();

        std::shared_ptr<complexTensor2D> ab2 =
            std::dynamic_pointer_cast<complexTensor2D>(storage);
        if (ab2)
            return ab2->clone();
        std::shared_ptr<complexTensor3D> ab3 =
            std::dynamic_pointer_cast<complexTensor3D>(storage);
        if (ab3)
            return ab3->clone();
        std::shared_ptr<complexTensor4D> ab4 =
            std::dynamic_pointer_cast<complexTensor4D>(storage);
        if (ab4)
            return ab4->clone();
        std::shared_ptr<complexTensor5D> ab5 =
            std::dynamic_pointer_cast<complexTensor5D>(storage);
        if (ab5)
            return ab5->clone();
        std::shared_ptr<complexTensor6D> ab6 =
            std::dynamic_pointer_cast<complexTensor6D>(storage);
        if (ab6)
            return ab6->clone();
        std::shared_ptr<complexTensor7D> ab7 =
            std::dynamic_pointer_cast<complexTensor7D>(storage);
        if (ab7)
            return ab7->clone();

        std::shared_ptr<complexDoubleTensor1D> ac1 =
            std::dynamic_pointer_cast<complexDoubleTensor1D>(storage);
        if (ac1)
            return ac1->clone();

        std::shared_ptr<complexDoubleTensor2D> ac2 =
            std::dynamic_pointer_cast<complexDoubleTensor2D>(storage);
        if (ac2)
            return ac2->clone();
        std::shared_ptr<complexDoubleTensor3D> ac3 =
            std::dynamic_pointer_cast<complexDoubleTensor3D>(storage);
        if (ac3)
            return ac3->clone();
        std::shared_ptr<complexDoubleTensor4D> ac4 =
            std::dynamic_pointer_cast<complexDoubleTensor4D>(storage);
        if (ac4)
            return ac4->clone();
        std::shared_ptr<complexDoubleTensor5D> ac5 =
            std::dynamic_pointer_cast<complexDoubleTensor5D>(storage);
        if (ac5)
            return ac5->clone();
        std::shared_ptr<complexDoubleTensor6D> ac6 =
            std::dynamic_pointer_cast<complexDoubleTensor6D>(storage);
        if (ac6)
            return ac6->clone();
        std::shared_ptr<complexDoubleTensor7D> ac7 =
            std::dynamic_pointer_cast<complexDoubleTensor7D>(storage);
        if (ac7)
            return ac7->clone();

        std::shared_ptr<doubleTensor1D> ad1 =
            std::dynamic_pointer_cast<doubleTensor1D>(storage);
        if (ad1)
            return ad1->clone();
        std::shared_ptr<doubleTensor2D> ad2 =
            std::dynamic_pointer_cast<doubleTensor2D>(storage);
        if (ad2)
            return ad2->clone();
        std::shared_ptr<doubleTensor3D> ad3 =
            std::dynamic_pointer_cast<doubleTensor3D>(storage);
        if (ad3)
            return ad3->clone();
        std::shared_ptr<doubleTensor4D> ad4 =
            std::dynamic_pointer_cast<doubleTensor4D>(storage);
        if (ad4)
            return ad4->clone();
        std::shared_ptr<doubleTensor5D> ad5 =
            std::dynamic_pointer_cast<doubleTensor5D>(storage);
        if (ad5)
            return ad5->clone();
        std::shared_ptr<doubleTensor6D> ad6 =
            std::dynamic_pointer_cast<doubleTensor6D>(storage);
        if (ad6)
            return ad6->clone();
        std::shared_ptr<doubleTensor7D> ad7 =
            std::dynamic_pointer_cast<doubleTensor7D>(storage);
        if (ad7)
            return ad7->clone();

        std::shared_ptr<floatTensor1D> ae1 =
            std::dynamic_pointer_cast<floatTensor1D>(storage);
        if (ae1)
            return ae1->clone();
        std::shared_ptr<floatTensor2D> ae2 =
            std::dynamic_pointer_cast<floatTensor2D>(storage);
        if (ae2)
            return ae2->clone();
        std::shared_ptr<floatTensor3D> ae3 =
            std::dynamic_pointer_cast<floatTensor3D>(storage);
        if (ae3)
            return ae3->clone();
        std::shared_ptr<floatTensor4D> ae4 =
            std::dynamic_pointer_cast<floatTensor4D>(storage);
        if (ae4)
            return ae4->clone();
        std::shared_ptr<floatTensor5D> ae5 =
            std::dynamic_pointer_cast<floatTensor5D>(storage);
        if (ae5)
            return ae5->clone();
        std::shared_ptr<floatTensor6D> ae6 =
            std::dynamic_pointer_cast<floatTensor6D>(storage);
        if (ae6)
            return ae6->clone();
        std::shared_ptr<floatTensor7D> ae7 =
            std::dynamic_pointer_cast<floatTensor7D>(storage);
        if (ae7)
            return ae7->clone();

        std::shared_ptr<intTensor1D> af1 =
            std::dynamic_pointer_cast<intTensor1D>(storage);
        if (af1)
            return af1->clone();
        std::shared_ptr<intTensor2D> af2 =
            std::dynamic_pointer_cast<intTensor2D>(storage);
        if (af2)
            return af2->clone();
        std::shared_ptr<intTensor3D> af3 =
            std::dynamic_pointer_cast<intTensor3D>(storage);
        if (af3)
            return af3->clone();
        std::shared_ptr<intTensor4D> af4 =
            std::dynamic_pointer_cast<intTensor4D>(storage);
        if (af4)
            return af4->clone();
        std::shared_ptr<intTensor5D> af5 =
            std::dynamic_pointer_cast<intTensor5D>(storage);
        if (af5)
            return af5->clone();
        std::shared_ptr<intTensor6D> af6 =
            std::dynamic_pointer_cast<intTensor6D>(storage);
        if (af6)
            return af6->clone();
        std::shared_ptr<intTensor7D> af7 =
            std::dynamic_pointer_cast<intTensor7D>(storage);
        if (af7)
            return af7->clone();

        std::shared_ptr<shortTensor1D> ag1 =
            std::dynamic_pointer_cast<shortTensor1D>(storage);
        if (ag1)
            return af1->clone();
        std::shared_ptr<shortTensor2D> ag2 =
            std::dynamic_pointer_cast<shortTensor2D>(storage);
        if (ag2)
            return af2->clone();
        std::shared_ptr<shortTensor3D> ag3 =
            std::dynamic_pointer_cast<shortTensor3D>(storage);
        if (ag3)
            return af3->clone();
        std::shared_ptr<shortTensor4D> ag4 =
            std::dynamic_pointer_cast<shortTensor4D>(storage);
        if (ag4)
            return af4->clone();
        std::shared_ptr<shortTensor5D> ag5 =
            std::dynamic_pointer_cast<shortTensor5D>(storage);
        if (ag5)
            return af5->clone();
        std::shared_ptr<shortTensor6D> ag6 =
            std::dynamic_pointer_cast<shortTensor6D>(storage);
        if (ag6)
            return af6->clone();
        std::shared_ptr<shortTensor7D> ag7 =
            std::dynamic_pointer_cast<shortTensor7D>(storage);
        if (ag7)
            return af7->clone();
    }

    return nullptr;
}
