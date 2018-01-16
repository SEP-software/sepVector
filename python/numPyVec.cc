
#include <numPyVec.h>

numPyVec::numPyVec(giee::floatHyper &hyp, const bool copy) {
  // Remember C stype
  int ndims = hyp.getHyper()->getNdim();
  long n[ndims];
  for (int i = 0; i < ndims; i++) n[i] = hyp.getHyper()->getAxis(ndims - i).n;
  float *buf = hyp.getVals();

  if (copy) {
    _vec.resize(hyp.getHyper()->getN123());
    for (auto i = 0; i < hyp.getHyper()->getN123(); i++) _vec[i] = buf[i];
    buf = _vec.data();
  }
  PyObject *y = PyArray_SimpleNewFromData(ndims, n, NPY_FLOAT32, buf);
  _ar.reset(y);
  _hyper = hyp.getHyper();
}
numPyVec::numPyVec(PyObject *numpy, const std::vector<int> &n,
                   const std::vector<float> &o, const std::vector<float> &d,
                   const std::vector<std::string> &label) {
  std::vector<SEP::axis> axes;
  for (int i = 0; i < (int)n.size(); i++) {
    axes.push_back(SEP::axis(n[i], o[i], d[i], label[i]));
  }
  _hyper.reset(new SEP::hypercube(axes));
  _ar.reset(numpy);
}
void numPyVec::windowInit(const giee::floatHyper &hyp,
                          const std::vector<int> &nw,
                          const std::vector<int> &fw,
                          const std::vector<int> &jw) {
  assert(nw.size() == fw.size() && nw.size() == jw.size() && nw.size() <= 7);
  std::vector<int> n = nw, f = fw, j = fw;
  n.resize(7, 1);
  f.resize(7, 0);
  j.resize(7, 1);
  std::shared_ptr<SEP::hypercube> hyper = hyp.getHyper();
  std::vector<int> nds = hyper->getNs(), nd = nds;
  nd.resize(7, 1);
  std::vector<long long> pin(7), pout(7);
  std::vector<long long> bin(7), bout(7);
  for (int i = 0; i < 7; i++) {
    if (j[i] <= 0) j[i] = 1;
    if (f[i] == -1) f[i] = 0;
    if (n[i] == -1) n[i] = (nd[i] - f[i]) / j[i] + 1;
    assert(nd[i] >= (1 + f[i] + j[i] * (n[i] - 1)));
    if (i == 0) {
      bin[i] = bout[i] = 1;
    } else {
      bout[i] = bout[i - 1] * n[i - 1];
      bin[i] = bin[i - 1] * nd[i];
    }
  }
  std::vector<SEP::axis> axes;
  for (int i = 0; i < nds.size(); i++) {
    SEP::axis a = hyper->getAxis(i + 1);
    a.o = a.o + f[i] * a.d;
    a.d = a.d * j[i];
    a.n = n[i];
    axes.push_back(a);
  }
  std::shared_ptr<SEP::hypercube> hyperOut(new SEP::hypercube(axes));
  _hyper = hyperOut;
  _vec.resize(_hyper->getN123());
  std::vector<long> ns;
  std::vector<int> n_s = _hyper->getNs();
  for (int i = 0; i < ns.size(); i++) ns[i] = n_s[i];
  float *out = _vec.data();
  const float *_vals = hyp.getCVals();
  PyObject *x =
      PyArray_SimpleNewFromData(_hyper->getNdim(), ns.data(), NPY_FLOAT32, out);
  _ar.reset(x);
  for (int i6 = 0; i6 < n[6]; i6++) {
    pout[6] = bout[6] * i6;
    pin[6] = bin[6] * (f[6] + j[6] * i6);
    for (int i5 = 0; i5 < n[5]; i5++) {
      pout[5] = bout[5] * i5 + pout[6];
      pin[5] = bin[5] * (f[5] + j[5] * i5) + pin[6];
      for (int i4 = 0; i4 < n[4]; i4++) {
        pout[4] = bout[4] * i4 + pout[5];
        pin[4] = bin[4] * (f[4] + j[4] * i4) + pin[5];
        for (int i3 = 0; i3 < n[3]; i3++) {
          pout[3] = bout[3] * i3 + pout[4];
          pin[3] = bin[3] * (f[3] + j[3] * i3) + pin[4];
          for (int i2 = 0; i2 < n[2]; i2++) {
            pout[2] = bout[2] * i2 + pout[3];
            pin[2] = bin[2] * (f[2] + j[2] * i2) + pin[3];
            for (int i1 = 0; i1 < n[1]; i1++) {
              pout[1] = bout[1] * i1 + pout[2];
              pin[1] = bin[1] * (f[1] + j[1] * i1) + pin[2];
              for (int i0 = 0, iout = pout[1], iin = pin[1] + f[0]; i0 < n[0];
                   i1++, iout++, iin += j[0]) {
                out[iout] = _vals[iin];
              }
            }
          }
        }
      }
    }
  }
}