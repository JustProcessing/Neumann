#ifndef MATRIX_EVAL_H
#define MATRIX_EVAL_H

namespace internal {

template <typename Derived>
struct evaluator {
  typedef typename Derived::Scalar Scalar;
  
  evaluator(const Derived &m) :
    m_data(const_cast<typename traits<Derived>::template MakePointer<Scalar>::type>(m.data()))
  {}
  
protected:
  typename traits<Derived>::template MakePointer<Scalar>::type m_data;
};

template <typename LeftArgType, typename RightArgType, typename Functor>
struct evaluator<> {
  typedef MatrixCWiseBinaryOp<LeftArgType, RightArgType, Functor> XprType;
  
  evaluator(const XprType &xpr) :
    m_lhs_impl(xpr.lhs()), m_rhs_impl(xpr.rhs()), m_functor(xpr.functor())
  {}
  
  bool eval_sub_exprs_if_needed() {
    m_lhs_impl.eval_sub_exprs_if_needed();
    m_rhs_impl.eval_sub_exprs_if_needed();
    return true;
  }
  
  CoeffReturnType coeff(Index index) {
    return m_functor(m_lhs_impl.coeff(index), m_rhs_impl.coeff(index));
  }
  
protected:
  const Functor m_functor;
  evaluator<LeftArgType> m_lhs_impl;
  evaluator<RightArgType> m_rhs_impl;
};

}

#endif
