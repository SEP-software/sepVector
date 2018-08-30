#include "byte1DReg.h"
#include "byte2DReg.h"
#include "byte3DReg.h"
#include "byte4DReg.h"
#include "byte5DReg.h"
#include "byte6DReg.h"
#include "complex1DReg.h"
#include "complex2DReg.h"
#include "complex3DReg.h"
#include "complex4DReg.h"
#include "complex5DReg.h"
#include "complex6DReg.h"
#include "double1DReg.h"
#include "double2DReg.h"
#include "double3DReg.h"
#include "double4DReg.h"
#include "double5DReg.h"
#include "double6DReg.h"
#include "float1DReg.h"
#include "float2DReg.h"
#include "float3DReg.h"
#include "float4DReg.h"
#include "float5DReg.h"
#include "float6DReg.h"
#include "int1DReg.h"
#include "int2DReg.h"
#include "int3DReg.h"
#include "int4DReg.h"
#include "int5DReg.h"
#include "int6DReg.h"
namespace SEP {
enum dataType { DATA_BYTE, DATA_INT, DATA_FLOAT, DATA_COMPLEX, DATA_DOUBLE };

std::shared_ptr<regSpace> vecFromHyper(const std::shared_ptr<hypercube> hyper,
                                       const dataType typ,
                                       const bool g1 = true);
std::shared_ptr<regSpace> subCubeFromHyper(
    const std::shared_ptr<hypercube> hyper, const dataType typ,
    const int &ndim);
std::shared_ptr<regSpace> windowFromHyper(
    const std::shared_ptr<hypercube> hyper, const std::vector<int> &nw,
    const std::vector<int> &fw, const std::vector<int> &jw, const dataType typ);
std::shared_ptr<regSpace> cloneRegSpace(std::shared_ptr<regSpace> storage);
}  // namespace SEP