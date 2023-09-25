
#include <efanna2e/index.h>
using namespace efanna2e;

Index::Index(const size_t dimension, const size_t n, Metric metric = L2)
  : dimension_ (dimension), nd_(n), has_built(false) {
    if(metric == L2){
      distance_ = new DistanceL2();
    }else if(metric == INNER_PRODUCT){
      distance_ = new DistanceInnerProduct();
    }else if(metric == FAST_L2){
      distance_ = new DistanceL2();
    }
}

Index::~Index() {}

