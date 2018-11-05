#ifndef CORE_EVALUATORS_H
#define CORE_EVALUATORS_H

#include <stdlib.h>
#include <stdio.h>

namespace internal {

template <typename T>
struct evaluator<const T> : evaluator<T> {
  explicit evaluator(const T& x) : evaluator<T>(x) {}
};

template <typename ExpressionType>
struct evaluator_base {
  typedef traits<ExpressionType> ExpressionTraits;
  
  evaluator_base() {}
  ~evaluator_base() {}
};

template <typename Scalar>
struct matrixbase_evaluator {
  matrixbase_evaluator(const Scalar *ptr, Index os, Index sz) : data(ptr) {
    outer_stride = os;
    size = sz;
  }
  
  const Scalar *data;
  Index outer_stride;
  Index size;
};

template <typename Derived>
struct evaluator<MatrixBase<Derived>> : evaluator_base<Derived> {
  typedef MatrixBase<Derived> MatrixType;
  typedef typename MatrixType::Scalar Scalar;
  
  evaluator(const MatrixType &m) : m_d(m.data(), m.outer_stride(), m.size()) { }
  
  Index size() { return m_d.size; }
  
  Scalar coeff(Index i) {
    return m_d.data[i];
  }
  
  Scalar coeff(Index row, Index col) {
    return m_d.data[m_d.outer_stride * row + col];
  }
  
  Scalar& coeff_ref(Index i) {
    return const_cast<Scalar*>(m_d.data)[i];
  }
  
  Scalar& coeff_ref(Index row, Index col) {
    return const_cast<Scalar*>(m_d.data)[m_d.outer_stride * row + col];
  }
  
  // TODO: add packet methods
  
protected:
  matrixbase_evaluator<Scalar> m_d;
};

template <typename Scalar>
struct evaluator<Matrix<Scalar>> : evaluator<MatrixBase<Matrix<Scalar>>> {
  typedef Matrix<Scalar> XprType;
  
  explicit evaluator(const XprType &m) : evaluator<MatrixBase<XprType>>(m) { }
};

}

#endif
