#ifndef MATRIX_EXPR_H
#define MATRIX_EXPR_H

namespace internal {

template <typename LhsType, typename RhsType, typename Functor>
struct nested<MatrixCWiseBinaryOp> {
  typedef const MatrixCWiseBinaryOp<LhsType, RhsType, Functor> type;
};

}

template <typename LhsType, typename RhsType, typename Functor>
class MatrixCWiseBinaryOp : public MatrixBase<MatrixCWiseBinaryOp<LhsType, RhsType, Functor>> {
public:
  typedef typename internal::nested<MatrixCWiseBinaryOp>::type Nested;
  
  MatrixCWiseBinaryOp(const LhsType &lhs, const RhsType &rhs, const Functor &func) :
    m_lhs(lhs), m_rhs(rhs), m_functor(func)
  {}
  
  const Functor &functor() const { return m_functor; }
  
  const typename LhsType::Nested &lhs() const { return m_lhs; }
  const typename RhsType::Nested &rhs() const { return m_rhs; }
  
protected:
  typename LhsType::Nested m_lhs;
  typename RhsType::Nested m_rhs;
  const Functor m_functor;
};

#endif
