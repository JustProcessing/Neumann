#ifndef UTIL_H
#define UTIL_H

namespace internal {

template <typename T>
struct nested;

template <typename LhsScalar, typename RhsScalar>
struct scalar_sum_op {
  scalar_sum_op() {}
  
  const ReturnType operator()(const LhsScalar &lhs, const RhsScalar &rhs) const { return a + b; }
  
  // TODO: Packets
};

template <typename LhsScalar, typename RhsScalar>
struct scalar_sub_op {
  scalar_sub_op() {}
  
  const ReturnType operator()(const LhsScalar &lhs, const RhsScalar &rhs) const { return a - b; }
};

template <typename LhsScalar, typename RhsScalar>
struct scalar_mul_op {
  scalar_mul_op() {}
  
  const ReturnType operator()(const LhsScalar &lhs, const RhsScalar &rhs) const { return a * b; }
};

template <typename LhsScalar, typename RhsScalar>
struct scalar_div_op {
  scalar_div_op() {}
  
  const ReturnType operator()(const LhsScalar &lhs, const RhsScalar &rhs) const { return a / b; }
};

}

#endif
