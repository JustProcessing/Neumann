#ifndef MATRIX_BASE_H
#define MATRIX_BASE_H

template <typename Derived>
class MatrixBase {
public:
  Derived &derived() { return *static_cast<Derived*>(this); }
  const Derived &derived() const { return *static_cast<const Derived*>(this); }
  
  template <typename OtherDerived, typename Functor>
  const MatrixCWiseBinaryOp<const Derived, const OtherDerived, Functor>
  binary_op(const OtherDerived &other, const Functor &func) {
    typedef const MatrixCWiseBinaryOp<const Derived, const OtherDerived, Functor> Op;
    return Op(derived(), other, func);
  }
  
  template <typename OtherDerived>
  const MatrixCWiseBinaryOp<const Derived, const OtherDerived, internal::scalar_add_op>
  operator+(const OtherDerived &other) {
    return binary_op(other, internal::scalar_add_op());
  }
  
  template <typename OtherDerived>
  const MatrixCWiseBinaryOp<const Derived, const OtherDerived, internal::scalar_sub_op>
  operator-(const OtherDerived &other) {
    return binary_op(other, internal::scalar_sub_op());
  }
  
  template <typename OtherDerived>
  const MatrixCWiseBinaryOp<const Derived, const OtherDerived, internal::scalar_mul_op>
  operator*(const OtherDerived &other) {
    return binary_op(other, internal::scalar_mul_op());
  }
  
  template <typename OtherDerived>
  const MatrixCWiseBinaryOp<const Derived, const OtherDerived, internal::scalar_div_op>
  operator/(const OtherDerived &other) {
    return binary_op(other, internal::scalar_div_op());
  }
};

#endif
