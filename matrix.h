#ifndef MATRIX_H
#define MATRIX_H

template <typename Scalar>
class MatrixStorage {
protected:
  Scalar *m_data;
  
  Index m_rows;
  Index m_cols;
  Index m_size;
  
  void alloc(Index rows, Index cols) {
    m_rows = rows;
    m_cols = cols;
    m_size = rows * cols;
    m_data = new Scalar[m_size];
  }
  
public:
  MatrixStorage() {}
  
  MatrixStorage(Index rows, Index cols) {
    alloc(rows, cols);
  }
  
  Scalar *data() const { return m_data; }
  
  void resize(Index rows, Index cols) {
    alloc(rows, cols);
  }
  
  void free() {
    delete m_data;
  }
  
  Index rows() const { return m_rows; }
  Index cols() const { return m_cols; }
  Index size() const { return m_size; }
};

namespace internal {

template <typename _Scalar>
struct traits<Matrix<_Scalar>> {
  typedef _Scalar Scalar;
};

}

template <typename Derived>
class MatrixBase {
public:
  typedef typename internal::traits<Derived>::Scalar Scalar;
  
  MatrixStorage<Scalar> storage;
  Index m_outer_stride;
  
  Index outer_stride() const { return m_outer_stride; }
  
  const Scalar *data() const { return storage.data(); }
  
  Derived& derived()             { return *static_cast<Derived*>(this); }
  const Derived& derived() const { return *static_cast<const Derived*>(this); }
  
  Index rows() const { return storage.rows(); }
  Index cols() const { return storage.cols(); }
  Index size() const { return storage.size(); }
  
  MatrixBase() { }
  
  MatrixBase(Index rows, Index cols) {
    m_outer_stride = cols;
    resize(rows, cols);
  }
  
  MatrixBase& operator=(const MatrixBase& other) {
    internal::call_assignment(derived(), other.derived());
    return derived();
  }
  
  void resize(Index rows, Index cols) {
    storage.resize(rows, cols);
  }
  
  Scalar& operator()(Index row, Index col) {
    return const_cast<Scalar*>(data())[outer_stride() * row + col];
  }
  
  MatrixBase operator+(const MatrixBase& other) {
    
  }
};

template <typename _Scalar>
class Matrix : public MatrixBase<Matrix<_Scalar>> {
protected:
  typedef MatrixBase<Matrix> Base;
  
public:
  using Base::resize;
  
  Matrix();
  
  Matrix(Index rows, Index cols);
};

template <typename Scalar>
Matrix<Scalar>::Matrix() : Base() {}

template <typename Scalar>
Matrix<Scalar>::Matrix(Index rows, Index cols) : Base(rows, cols) {}

#endif
