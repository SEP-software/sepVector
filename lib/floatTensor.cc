#include<floatTensor.h>
using namespace SEP;

std::shared_ptr<floatTensor7D> floatTensor7D::clone() const {
    if (getSpaceOnly()) {
        std::shared_ptr<float7DReg> x(new floatTensor7D(getHyper()));

        return x;
    }
    else {
        std::shared_ptr<floatTensor7D> x(new floatTensor7D(getHyper(), getVals()));

        return x;
    }
}

std::shared_ptr<floatTensor7D> floatTensor7D::cloneSpace() const {
    std::shared_ptr<floatTensor7D> x(new floatTensor7D(getHyper()));
    x->mat = NULL;

    x->setSpace();
    return x;
}

void floatTensor7D::initNoData(std::shared_ptr<SEP::hypercube> hyp) {
    const std::vector<SEP::axis> axes = hyp->getAxes();
    setHyper(hyp);

    if (axes.size() != 7)
        throw(SEPException(std::string("Axes size must be 7 is ") +
            std::to_string(axes.size())));
    xt::xtensor<float,7>::shape_type  shape={axes[6].n,axes[5].n,axes[4].n,axes[3].n,axes[2].n,axes[1].n,axes[0].n};
     mat=xt::xtensor<float,7>::from_shape(shape);
     setData(mat);
}

std::shared_ptr<floatTensor7D> floatTensor7D::window(
    const std::vector<int> &nw, const std::vector<int> &fw,
    const std::vector<int> &jw) const {
    const std::vector<SEP::axis> axes = getHyper()->getAxes();
    if (nw.size() != axes.size()) throw(SEPException("nw must of length 7"));
    if (fw.size() != axes.size()) throw(SEPException("fw must of length 7"));
    if (jw.size() != axes.size()) throw(SEPException("jw must of length 7"));
    std::vector<axis> aout;
    std::vector<int> beg(7),end(7),sk(7);
    for (int i = 0; i < axes.size(); i++) {
        checkWindow(axes[i].n, nw[i], fw[i], jw[i]);
        beg[i]=fw[i];
        sk[i]=j[i];
        end[i]=beg[i]+sk[i]*n[i];
        aout.push_back(
            axis(nw[i], axes[i].o + axes[i].d * fw[i], axes[i].d * jw[i]));
    }
    std::shared_ptr<hypercube> hypOut(new hypercube(aout));
    std::shared_ptr<float7DReg> out(new floatHyper7D(hypOut));
    auto vw=xt::view(mat,xt::range(beg[6],end[6],sk[6]),
    xt::range(beg[5],end[5],sk[5]),
    xt::range(beg[4],end[4],sk[4]),
    xt::range(beg[3],end[3],sk[3]),
    xt::range(beg[2],end[2],sk[2]),
    xt::range(beg[1],end[1],sk[1]),
    xt::range(beg[0],end[0],sk[0]));
    for (int i6 = 0; i6 < nw[6]; i6++) 
        for (int i5 = 0; i5 < nw[5]; i5++) 
            for (int i4 = 0; i4 < nw[4]; i4++) 
                for (int i3 = 0; i3 < nw[3]; i3++) 
                    for (int i2 = 0; i2 < nw[2]; i2++) 
                        for (int i1 = 0; i1 < nw[1]; i1++) 
                            for (int i0 = 0; i0 < nw[0]; i0++) 
                              out->mat(i6,i5,i4,i3,i2,i1,i0)=mat(i6,i5,i4,i3,i2,i1,i0);

    return out;
}
