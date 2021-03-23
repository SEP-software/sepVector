#include <complexTensor.h>
#include <xtensor/xview.hpp>

using namespace SEP;

std::shared_ptr<complexTensor7D> complexTensor7D::clone() const
{
    if (getSpaceOnly())
    {
        std::shared_ptr<complexTensor7D> x(new complexTensor7D(getHyper()));

        return x;
    }
    else
    {
        std::shared_ptr<complexTensor7D> x(new complexTensor7D(getHyper(), getCVals()));

        return x;
    }
}

std::shared_ptr<complexTensor7D> complexTensor7D::cloneSpace() const
{
    std::shared_ptr<complexTensor7D> x(new complexTensor7D(getHyper()));
    x->mat = {{{{{{{0}}}}}}};

    x->setSpace();
    return x;
}

void complexTensor7D::initNoData(std::shared_ptr<SEP::hypercube> hyp)
{
    const std::vector<SEP::axis> axes = hyp->getAxes();
    setHyper(hyp);

    if (axes.size() != 7)
        throw(SEPException(std::string("Axes size must be 7 is ") +
                           std::to_string(axes.size())));
    xt::xtensor<std::complex<float>, 7>::shape_type shape = {(size_t)axes[6].n, (size_t)axes[5].n, (size_t)axes[4].n,
                                                             (size_t)axes[3].n, (size_t)axes[2].n, (size_t)axes[1].n, (size_t)axes[0].n};
    mat = xt::xtensor<std::complex<float>, 7>::from_shape(shape);
    setData(mat.data());
}

std::shared_ptr<complexTensor7D> complexTensor7D::window(
    const std::vector<int> &nw, const std::vector<int> &fw,
    const std::vector<int> &jw) const
{
    const std::vector<SEP::axis> axes = getHyper()->getAxes();
    if (nw.size() != axes.size())
        throw(SEPException("nw must of length 7"));
    if (fw.size() != axes.size())
        throw(SEPException("fw must of length 7"));
    if (jw.size() != axes.size())
        throw(SEPException("jw must of length 7"));
    std::vector<axis> aout;
    std::vector<int> beg(7), end(7), sk(7);
    for (int i = 0; i < axes.size(); i++)
    {
        checkWindow(axes[i].n, nw[i], fw[i], jw[i]);
        beg[i] = fw[i];
        sk[i] = jw[i];
        end[i] = beg[i] + sk[i] * nw[i];
        aout.push_back(
            axis(nw[i], axes[i].o + axes[i].d * fw[i], axes[i].d * jw[i]));
    }
    std::shared_ptr<hypercube> hypOut(new hypercube(aout));
    std::shared_ptr<complexTensor7D> out(new complexTensor7D(hypOut));
    auto vw = xt::view(mat, xt::range(beg[6], end[6], sk[6]),
                       xt::range(beg[5], end[5], sk[5]),
                       xt::range(beg[4], end[4], sk[4]),
                       xt::range(beg[3], end[3], sk[3]),
                       xt::range(beg[2], end[2], sk[2]),
                       xt::range(beg[1], end[1], sk[1]),
                       xt::range(beg[0], end[0], sk[0]));
    for (int i6 = 0; i6 < nw[6]; i6++)
        for (int i5 = 0; i5 < nw[5]; i5++)
            for (int i4 = 0; i4 < nw[4]; i4++)
                for (int i3 = 0; i3 < nw[3]; i3++)
                    for (int i2 = 0; i2 < nw[2]; i2++)
                        for (int i1 = 0; i1 < nw[1]; i1++)
                            for (int i0 = 0; i0 < nw[0]; i0++)
                                out->mat(i6, i5, i4, i3, i2, i1, i0) = mat(i6, i5, i4, i3, i2, i1, i0);

    return out;
}

//6-D
std::shared_ptr<complexTensor6D> complexTensor6D::clone() const
{
    if (getSpaceOnly())
    {
        std::shared_ptr<complexTensor6D> x(new complexTensor6D(getHyper()));

        return x;
    }
    else
    {
        std::shared_ptr<complexTensor6D> x(new complexTensor6D(getHyper(), getCVals()));

        return x;
    }
}

std::shared_ptr<complexTensor6D> complexTensor6D::cloneSpace() const
{
    std::shared_ptr<complexTensor6D> x(new complexTensor6D(getHyper()));
    x->mat = {{{{{{0}}}}}};

    x->setSpace();
    return x;
}

void complexTensor6D::initNoData(std::shared_ptr<SEP::hypercube> hyp)
{
    const std::vector<SEP::axis> axes = hyp->getAxes();
    setHyper(hyp);

    if (axes.size() != 6)
        throw(SEPException(std::string("Axes size must be 6 is ") +
                           std::to_string(axes.size())));
    xt::xtensor<std::complex<float>, 6>::shape_type shape = {(size_t)axes[5].n, (size_t)axes[4].n,
                                                             (size_t)axes[3].n, (size_t)axes[2].n, (size_t)axes[1].n, (size_t)axes[0].n};
    mat = xt::xtensor<std::complex<float>, 6>::from_shape(shape);
    setData(mat.data());
}

std::shared_ptr<complexTensor6D> complexTensor6D::window(
    const std::vector<int> &nw, const std::vector<int> &fw,
    const std::vector<int> &jw) const
{
    const std::vector<SEP::axis> axes = getHyper()->getAxes();
    if (nw.size() != axes.size())
        throw(SEPException("nw must of length 6"));
    if (fw.size() != axes.size())
        throw(SEPException("fw must of length 6"));
    if (jw.size() != axes.size())
        throw(SEPException("jw must of length 6"));
    std::vector<axis> aout;
    std::vector<int> beg(6), end(6), sk(6);
    for (int i = 0; i < axes.size(); i++)
    {
        checkWindow(axes[i].n, nw[i], fw[i], jw[i]);
        beg[i] = fw[i];
        sk[i] = jw[i];
        end[i] = beg[i] + sk[i] * nw[i];
        aout.push_back(
            axis(nw[i], axes[i].o + axes[i].d * fw[i], axes[i].d * jw[i]));
    }
    std::shared_ptr<hypercube> hypOut(new hypercube(aout));
    std::shared_ptr<complexTensor6D> out(new complexTensor6D(hypOut));
    auto vw = xt::view(mat,
                       xt::range(beg[5], end[5], sk[5]),
                       xt::range(beg[4], end[4], sk[4]),
                       xt::range(beg[3], end[3], sk[3]),
                       xt::range(beg[2], end[2], sk[2]),
                       xt::range(beg[1], end[1], sk[1]),
                       xt::range(beg[0], end[0], sk[0]));
    for (int i5 = 0; i5 < nw[5]; i5++)
        for (int i4 = 0; i4 < nw[4]; i4++)
            for (int i3 = 0; i3 < nw[3]; i3++)
                for (int i2 = 0; i2 < nw[2]; i2++)
                    for (int i1 = 0; i1 < nw[1]; i1++)
                        for (int i0 = 0; i0 < nw[0]; i0++)
                            out->mat(i5, i4, i3, i2, i1, i0) = mat(i5, i4, i3, i2, i1, i0);

    return out;
}

//5D version

std::shared_ptr<complexTensor5D> complexTensor5D::clone() const
{
    if (getSpaceOnly())
    {
        std::shared_ptr<complexTensor5D> x(new complexTensor5D(getHyper()));

        return x;
    }
    else
    {
        std::shared_ptr<complexTensor5D> x(new complexTensor5D(getHyper(), getCVals()));

        return x;
    }
}

std::shared_ptr<complexTensor5D> complexTensor5D::cloneSpace() const
{
    std::shared_ptr<complexTensor5D> x(new complexTensor5D(getHyper()));
    x->mat = {{{{{0}}}}};

    x->setSpace();
    return x;
}

void complexTensor5D::initNoData(std::shared_ptr<SEP::hypercube> hyp)
{
    const std::vector<SEP::axis> axes = hyp->getAxes();
    setHyper(hyp);

    if (axes.size() != 5)
        throw(SEPException(std::string("Axes size must be 5 is ") +
                           std::to_string(axes.size())));
    xt::xtensor<std::complex<float>, 5>::shape_type shape = {(size_t)axes[4].n,
                                                             (size_t)axes[3].n, (size_t)axes[2].n, (size_t)axes[1].n, (size_t)axes[0].n};
    mat = xt::xtensor<std::complex<float>, 5>::from_shape(shape);
    setData(mat.data());
}

std::shared_ptr<complexTensor5D> complexTensor5D::window(
    const std::vector<int> &nw, const std::vector<int> &fw,
    const std::vector<int> &jw) const
{
    const std::vector<SEP::axis> axes = getHyper()->getAxes();
    if (nw.size() != axes.size())
        throw(SEPException("nw must of length 5"));
    if (fw.size() != axes.size())
        throw(SEPException("fw must of length 5"));
    if (jw.size() != axes.size())
        throw(SEPException("jw must of length 5"));
    std::vector<axis> aout;
    std::vector<int> beg(5), end(5), sk(5);
    for (int i = 0; i < axes.size(); i++)
    {
        checkWindow(axes[i].n, nw[i], fw[i], jw[i]);
        beg[i] = fw[i];
        sk[i] = jw[i];
        end[i] = beg[i] + sk[i] * nw[i];
        aout.push_back(
            axis(nw[i], axes[i].o + axes[i].d * fw[i], axes[i].d * jw[i]));
    }
    std::shared_ptr<hypercube> hypOut(new hypercube(aout));
    std::shared_ptr<complexTensor5D> out(new complexTensor5D(hypOut));
    auto vw = xt::view(mat,

                       xt::range(beg[4], end[4], sk[4]),
                       xt::range(beg[3], end[3], sk[3]),
                       xt::range(beg[2], end[2], sk[2]),
                       xt::range(beg[1], end[1], sk[1]),
                       xt::range(beg[0], end[0], sk[0]));
    for (int i4 = 0; i4 < nw[4]; i4++)
        for (int i3 = 0; i3 < nw[3]; i3++)
            for (int i2 = 0; i2 < nw[2]; i2++)
                for (int i1 = 0; i1 < nw[1]; i1++)
                    for (int i0 = 0; i0 < nw[0]; i0++)
                        out->mat(i4, i3, i2, i1, i0) = mat(i4, i3, i2, i1, i0);

    return out;
}

//4D version

std::shared_ptr<complexTensor4D> complexTensor4D::clone() const
{
    if (getSpaceOnly())
    {
        std::shared_ptr<complexTensor4D> x(new complexTensor4D(getHyper()));

        return x;
    }
    else
    {
        std::shared_ptr<complexTensor4D> x(new complexTensor4D(getHyper(), getCVals()));

        return x;
    }
}

std::shared_ptr<complexTensor4D> complexTensor4D::cloneSpace() const
{
    std::shared_ptr<complexTensor4D> x(new complexTensor4D(getHyper()));
    x->mat = {{{{0}}}};

    x->setSpace();
    return x;
}

void complexTensor4D::initNoData(std::shared_ptr<SEP::hypercube> hyp)
{
    const std::vector<SEP::axis> axes = hyp->getAxes();
    setHyper(hyp);

    if (axes.size() != 4)
        throw(SEPException(std::string("Axes size must be 4 is ") +
                           std::to_string(axes.size())));
    xt::xtensor<std::complex<float>, 4>::shape_type shape = {
        (size_t)axes[3].n, (size_t)axes[2].n, (size_t)axes[1].n, (size_t)axes[0].n};
    mat = xt::xtensor<std::complex<float>, 4>::from_shape(shape);
    setData(mat.data());
}

std::shared_ptr<complexTensor4D> complexTensor4D::window(
    const std::vector<int> &nw, const std::vector<int> &fw,
    const std::vector<int> &jw) const
{
    const std::vector<SEP::axis> axes = getHyper()->getAxes();
    if (nw.size() != axes.size())
        throw(SEPException("nw must of length 4"));
    if (fw.size() != axes.size())
        throw(SEPException("fw must of length 4"));
    if (jw.size() != axes.size())
        throw(SEPException("jw must of length 4"));
    std::vector<axis> aout;
    std::vector<int> beg(4), end(4), sk(4);
    for (int i = 0; i < axes.size(); i++)
    {
        checkWindow(axes[i].n, nw[i], fw[i], jw[i]);
        beg[i] = fw[i];
        sk[i] = jw[i];
        end[i] = beg[i] + sk[i] * nw[i];
        aout.push_back(
            axis(nw[i], axes[i].o + axes[i].d * fw[i], axes[i].d * jw[i]));
    }
    std::shared_ptr<hypercube> hypOut(new hypercube(aout));
    std::shared_ptr<complexTensor4D> out(new complexTensor4D(hypOut));
    auto vw = xt::view(mat,

                       xt::range(beg[3], end[3], sk[3]),
                       xt::range(beg[2], end[2], sk[2]),
                       xt::range(beg[1], end[1], sk[1]),
                       xt::range(beg[0], end[0], sk[0]));
    for (int i3 = 0; i3 < nw[3]; i3++)
        for (int i2 = 0; i2 < nw[2]; i2++)
            for (int i1 = 0; i1 < nw[1]; i1++)
                for (int i0 = 0; i0 < nw[0]; i0++)
                    out->mat(i3, i2, i1, i0) = mat(i3, i2, i1, i0);

    return out;
}

//3D version

std::shared_ptr<complexTensor3D> complexTensor3D::clone() const
{
    if (getSpaceOnly())
    {
        std::shared_ptr<complexTensor3D> x(new complexTensor3D(getHyper()));

        return x;
    }
    else
    {
        std::shared_ptr<complexTensor3D> x(new complexTensor3D(getHyper(), getCVals()));

        return x;
    }
}

std::shared_ptr<complexTensor3D> complexTensor3D::cloneSpace() const
{
    std::shared_ptr<complexTensor3D> x(new complexTensor3D(getHyper()));
    x->mat = {{{0}}};

    x->setSpace();
    return x;
}

void complexTensor3D::initNoData(std::shared_ptr<SEP::hypercube> hyp)
{
    const std::vector<SEP::axis> axes = hyp->getAxes();
    setHyper(hyp);

    if (axes.size() != 3)
        throw(SEPException(std::string("Axes size must be 4 is ") +
                           std::to_string(axes.size())));
    xt::xtensor<std::complex<float>, 3>::shape_type shape = {
        (size_t)axes[2].n, (size_t)axes[1].n, (size_t)axes[0].n};
    mat = xt::xtensor<std::complex<float>, 3>::from_shape(shape);
    setData(mat.data());
}

std::shared_ptr<complexTensor3D> complexTensor3D::window(
    const std::vector<int> &nw, const std::vector<int> &fw,
    const std::vector<int> &jw) const
{
    const std::vector<SEP::axis> axes = getHyper()->getAxes();
    if (nw.size() != axes.size())
        throw(SEPException("nw must of length 3"));
    if (fw.size() != axes.size())
        throw(SEPException("fw must of length 3"));
    if (jw.size() != axes.size())
        throw(SEPException("jw must of length 3"));
    std::vector<axis> aout;
    std::vector<int> beg(3), end(3), sk(3);
    for (int i = 0; i < axes.size(); i++)
    {
        checkWindow(axes[i].n, nw[i], fw[i], jw[i]);
        beg[i] = fw[i];
        sk[i] = jw[i];
        end[i] = beg[i] + sk[i] * nw[i];
        aout.push_back(
            axis(nw[i], axes[i].o + axes[i].d * fw[i], axes[i].d * jw[i]));
    }
    std::shared_ptr<hypercube> hypOut(new hypercube(aout));
    std::shared_ptr<complexTensor3D> out(new complexTensor3D(hypOut));
    auto vw = xt::view(mat,
                       xt::range(beg[2], end[2], sk[2]),
                       xt::range(beg[1], end[1], sk[1]),
                       xt::range(beg[0], end[0], sk[0]));
    for (int i2 = 0; i2 < nw[2]; i2++)
        for (int i1 = 0; i1 < nw[1]; i1++)
            for (int i0 = 0; i0 < nw[0]; i0++)
                out->mat(i2, i1, i0) = mat(i2, i1, i0);

    return out;
}

//2D version

std::shared_ptr<complexTensor2D> complexTensor2D::clone() const
{
    if (getSpaceOnly())
    {
        std::shared_ptr<complexTensor2D> x(new complexTensor2D(getHyper()));

        return x;
    }
    else
    {
        std::shared_ptr<complexTensor2D> x(new complexTensor2D(getHyper(), getCVals()));

        return x;
    }
}

std::shared_ptr<complexTensor2D> complexTensor2D::cloneSpace() const
{
    std::shared_ptr<complexTensor2D> x(new complexTensor2D(getHyper()));
    x->mat = {{0}};

    x->setSpace();
    return x;
}

void complexTensor2D::initNoData(std::shared_ptr<SEP::hypercube> hyp)
{
    const std::vector<SEP::axis> axes = hyp->getAxes();
    setHyper(hyp);

    if (axes.size() != 2)
        throw(SEPException(std::string("Axes size must be 4 is ") +
                           std::to_string(axes.size())));
    xt::xtensor<std::complex<float>, 3>::shape_type shape = {
        (size_t)axes[1].n, (size_t)axes[0].n};
    mat = xt::xtensor<std::complex<float>, 2>::from_shape(shape);
    setData(mat.data());
}

std::shared_ptr<complexTensor2D> complexTensor2D::window(
    const std::vector<int> &nw, const std::vector<int> &fw,
    const std::vector<int> &jw) const
{
    const std::vector<SEP::axis> axes = getHyper()->getAxes();
    if (nw.size() != axes.size())
        throw(SEPException("nw must of length 2"));
    if (fw.size() != axes.size())
        throw(SEPException("fw must of length 2"));
    if (jw.size() != axes.size())
        throw(SEPException("jw must of length 2"));
    std::vector<axis> aout;
    std::vector<int> beg(2), end(2), sk(2);
    for (int i = 0; i < axes.size(); i++)
    {
        checkWindow(axes[i].n, nw[i], fw[i], jw[i]);
        beg[i] = fw[i];
        sk[i] = jw[i];
        end[i] = beg[i] + sk[i] * nw[i];
        aout.push_back(
            axis(nw[i], axes[i].o + axes[i].d * fw[i], axes[i].d * jw[i]));
    }
    std::shared_ptr<hypercube> hypOut(new hypercube(aout));
    std::shared_ptr<complexTensor2D> out(new complexTensor2D(hypOut));
    auto vw = xt::view(mat,
                       xt::range(beg[1], end[1], sk[1]),
                       xt::range(beg[0], end[0], sk[0]));
    for (int i1 = 0; i1 < nw[1]; i1++)
        for (int i0 = 0; i0 < nw[0]; i0++)
            out->mat(i1, i0) = mat(i1, i0);

    return out;
}

complexTensor2D::complexTensor2D(
    const std::shared_ptr<complexTensor7D> old, const int iax1,
    const bool rev1, const int iax2, const bool rev2,
    const std::vector<int> &ipos, const std::vector<int> &beg,
    const std::vector<int> &end)
{
    std::vector<int> n, f, j;
    std::shared_ptr<hypercube> hyperOut;
    std::tie(hyperOut, n, f, j) = sliceToWindow2D(iax1, iax2, beg, end, ipos);
    std::shared_ptr<complexTensor7D> tmp = old->window(n, f, j);
    initNoData(hyperOut);
    doTraverse2D(n, iax1, rev1, iax2, rev2, tmp->getCVals(), getVals(), sizeof(std::complex<std::complex<float> >));
}

complexTensor2D::complexTensor2D(
    const std::shared_ptr<complexTensor6D> old, const int iax1,
    const bool rev1, const int iax2, const bool rev2,
    const std::vector<int> &ipos, const std::vector<int> &beg,
    const std::vector<int> &end)
{
    std::vector<int> n, f, j;
    std::shared_ptr<hypercube> hyperOut;
    std::tie(hyperOut, n, f, j) = sliceToWindow2D(iax1, iax2, beg, end, ipos);
    std::shared_ptr<complexTensor6D> tmp = old->window(n, f, j);
    initNoData(hyperOut);
    doTraverse2D(n, iax1, rev1, iax2, rev2, tmp->getCVals(), getVals(), sizeof(std::complex<std::complex<float> >));
}
complexTensor2D::complexTensor2D(
    const std::shared_ptr<complexTensor5D> old, const int iax1,
    const bool rev1, const int iax2, const bool rev2,
    const std::vector<int> &ipos, const std::vector<int> &beg,
    const std::vector<int> &end)
{
    std::vector<int> n, f, j;
    std::shared_ptr<hypercube> hyperOut;
    std::tie(hyperOut, n, f, j) = sliceToWindow2D(iax1, iax2, beg, end, ipos);
    std::shared_ptr<complexTensor5D> tmp = old->window(n, f, j);
    initNoData(hyperOut);
    doTraverse2D(n, iax1, rev1, iax2, rev2, tmp->getCVals(), getVals(), sizeof(std::complex<std::complex<float> >));
}
complexTensor2D::complexTensor2D(
    const std::shared_ptr<complexTensor4D> old, const int iax1,
    const bool rev1, const int iax2, const bool rev2,
    const std::vector<int> &ipos, const std::vector<int> &beg,
    const std::vector<int> &end)
{
    std::vector<int> n, f, j;
    std::shared_ptr<hypercube> hyperOut;
    std::tie(hyperOut, n, f, j) = sliceToWindow2D(iax1, iax2, beg, end, ipos);
    std::shared_ptr<complexTensor4D> tmp = old->window(n, f, j);
    initNoData(hyperOut);
    doTraverse2D(n, iax1, rev1, iax2, rev2, tmp->getCVals(), getVals(), sizeof(std::complex<std::complex<float> >));
}
complexTensor2D::complexTensor2D(
    const std::shared_ptr<complexTensor3D> old, const int iax1,
    const bool rev1, const int iax2, const bool rev2,
    const std::vector<int> &ipos, const std::vector<int> &beg,
    const std::vector<int> &end)
{
    std::vector<int> n, f, j;
    std::shared_ptr<hypercube> hyperOut;
    std::tie(hyperOut, n, f, j) = sliceToWindow2D(iax1, iax2, beg, end, ipos);
    std::shared_ptr<complexTensor3D> tmp = old->window(n, f, j);
    initNoData(hyperOut);
    doTraverse2D(n, iax1, rev1, iax2, rev2, tmp->getCVals(), getVals(), sizeof(std::complex<std::complex<float> >));
}
complexTensor2D::complexTensor2D(
    const std::shared_ptr<complexTensor2D> old, const int iax1,
    const bool rev1, const int iax2, const bool rev2,
    const std::vector<int> &ipos, const std::vector<int> &beg,
    const std::vector<int> &end)
{
    std::vector<int> n, f, j;
    std::shared_ptr<hypercube> hyperOut;
    std::tie(hyperOut, n, f, j) = sliceToWindow2D(iax1, iax2, beg, end, ipos);
    std::shared_ptr<complexTensor2D> tmp = old->window(n, f, j);
    initNoData(hyperOut);
    doTraverse2D(n, iax1, rev1, iax2, rev2, tmp->getCVals(), getVals(), sizeof(std::complex<std::complex<float> >));
}

//1D version

std::shared_ptr<complexTensor1D> complexTensor1D::clone() const
{
    if (getSpaceOnly())
    {
        std::shared_ptr<complexTensor1D> x(new complexTensor1D(getHyper()));

        return x;
    }
    else
    {
        std::shared_ptr<complexTensor1D> x(new complexTensor1D(getHyper(), getCVals()));

        return x;
    }
}

std::shared_ptr<complexTensor1D> complexTensor1D::cloneSpace() const
{
    std::shared_ptr<complexTensor1D> x(new complexTensor1D(getHyper()));
    x->mat = {0};

    x->setSpace();
    return x;
}

void complexTensor1D::initNoData(std::shared_ptr<SEP::hypercube> hyp)
{
    const std::vector<SEP::axis> axes = hyp->getAxes();
    setHyper(hyp);

    if (axes.size() != 1)
        throw(SEPException(std::string("Axes size must be 4 is ") +
                           std::to_string(axes.size())));
    xt::xtensor<std::complex<float>, 1>::shape_type shape = {
        (size_t)axes[0].n};
    mat = xt::xtensor<std::complex<float>, 1>::from_shape(shape);
    setData(mat.data());
}

std::shared_ptr<complexTensor1D> complexTensor1D::window(
    const std::vector<int> &nw, const std::vector<int> &fw,
    const std::vector<int> &jw) const
{
    const std::vector<SEP::axis> axes = getHyper()->getAxes();
    if (nw.size() != axes.size())
        throw(SEPException("nw must of length 1"));
    if (fw.size() != axes.size())
        throw(SEPException("fw must of length 1"));
    if (jw.size() != axes.size())
        throw(SEPException("jw must of length 1"));
    std::vector<axis> aout;
    std::vector<int> beg(1), end(1), sk(1);
    for (int i = 0; i < axes.size(); i++)
    {
        checkWindow(axes[i].n, nw[i], fw[i], jw[i]);
        beg[i] = fw[i];
        sk[i] = jw[i];
        end[i] = beg[i] + sk[i] * nw[i];
        aout.push_back(
            axis(nw[i], axes[i].o + axes[i].d * fw[i], axes[i].d * jw[i]));
    }
    std::shared_ptr<hypercube> hypOut(new hypercube(aout));
    std::shared_ptr<complexTensor1D> out(new complexTensor1D(hypOut));
    auto vw = xt::view(mat,
                       xt::range(beg[0], end[0], sk[0]));
    for (int i0 = 0; i0 < nw[0]; i0++)
        out->mat(i0) = mat(i0);

    return out;
}

complexTensor1D::complexTensor1D(
    const std::shared_ptr<complexTensor7D> old, const int iax1,
    const bool rev1,
    const std::vector<int> &ipos, const std::vector<int> &beg,
    const std::vector<int> &end)
{
    std::vector<int> n, f, j;
    std::shared_ptr<hypercube> hyperOut;
    std::tie(hyperOut, n, f, j) = sliceToWindow1D(iax1, beg, end, ipos);
    std::shared_ptr<complexTensor7D> tmp = old->window(n, f, j);
    initNoData(hyperOut);
    doTraverse1D(n, iax1, rev1, tmp->getCVals(), getVals(), sizeof(std::complex<std::complex<float> >));
}

complexTensor1D::complexTensor1D(
    const std::shared_ptr<complexTensor6D> old, const int iax1,
    const bool rev1,
    const std::vector<int> &ipos, const std::vector<int> &beg,
    const std::vector<int> &end)
{
    std::vector<int> n, f, j;
    std::shared_ptr<hypercube> hyperOut;
    std::tie(hyperOut, n, f, j) = sliceToWindow1D(iax1, beg, end, ipos);
    std::shared_ptr<complexTensor6D> tmp = old->window(n, f, j);
    initNoData(hyperOut);
    doTraverse1D(n, iax1, rev1, tmp->getCVals(), getVals(), sizeof(std::complex<std::complex<float> >));
}
complexTensor1D::complexTensor1D(
    const std::shared_ptr<complexTensor5D> old, const int iax1,
    const bool rev1,
    const std::vector<int> &ipos, const std::vector<int> &beg,
    const std::vector<int> &end)
{
    std::vector<int> n, f, j;
    std::shared_ptr<hypercube> hyperOut;
    std::tie(hyperOut, n, f, j) = sliceToWindow1D(iax1, beg, end, ipos);
    std::shared_ptr<complexTensor5D> tmp = old->window(n, f, j);
    initNoData(hyperOut);
    doTraverse1D(n, iax1, rev1, tmp->getCVals(), getVals(), sizeof(std::complex<std::complex<float> >));
}
complexTensor1D::complexTensor1D(
    const std::shared_ptr<complexTensor4D> old, const int iax1,
    const bool rev1,
    const std::vector<int> &ipos, const std::vector<int> &beg,
    const std::vector<int> &end)
{
    std::vector<int> n, f, j;
    std::shared_ptr<hypercube> hyperOut;
    std::tie(hyperOut, n, f, j) = sliceToWindow1D(iax1, beg, end, ipos);
    std::shared_ptr<complexTensor4D> tmp = old->window(n, f, j);
    initNoData(hyperOut);
    doTraverse1D(n, iax1, rev1, tmp->getCVals(), getVals(), sizeof(std::complex<std::complex<float> >));
}
complexTensor1D::complexTensor1D(
    const std::shared_ptr<complexTensor3D> old, const int iax1,
    const bool rev1,
    const std::vector<int> &ipos, const std::vector<int> &beg,
    const std::vector<int> &end)
{
    std::vector<int> n, f, j;
    std::shared_ptr<hypercube> hyperOut;
    std::tie(hyperOut, n, f, j) = sliceToWindow1D(iax1, beg, end, ipos);
    std::shared_ptr<complexTensor3D> tmp = old->window(n, f, j);
    initNoData(hyperOut);
    doTraverse1D(n, iax1, rev1, tmp->getCVals(), getVals(), sizeof(std::complex<std::complex<float> >));
}
complexTensor1D::complexTensor1D(
    const std::shared_ptr<complexTensor2D> old, const int iax1,
    const bool rev1,
    const std::vector<int> &ipos, const std::vector<int> &beg,
    const std::vector<int> &end)
{
    std::vector<int> n, f, j;
    std::shared_ptr<hypercube> hyperOut;
    std::tie(hyperOut, n, f, j) = sliceToWindow1D(iax1, beg, end, ipos);
    std::shared_ptr<complexTensor2D> tmp = old->window(n, f, j);
    initNoData(hyperOut);
    doTraverse1D(n, iax1, rev1, tmp->getCVals(), getVals(), sizeof(std::complex<std::complex<float> >));
}
complexTensor1D::complexTensor1D(
    const std::shared_ptr<complexTensor1D> old, const int iax1,
    const bool rev1,
    const std::vector<int> &ipos, const std::vector<int> &beg,
    const std::vector<int> &end)
{
    std::vector<int> n, f, j;
    std::shared_ptr<hypercube> hyperOut;
    std::tie(hyperOut, n, f, j) = sliceToWindow1D(iax1, beg, end, ipos);
    std::shared_ptr<complexTensor1D> tmp = old->window(n, f, j);
    initNoData(hyperOut);
    doTraverse1D(n, iax1, rev1, tmp->getCVals(), getVals(), sizeof(std::complex<std::complex<float> >));
}