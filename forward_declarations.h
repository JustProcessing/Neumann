#ifndef FORWARD_DECLARATIONS_H
#define FORWARD_DECLARATIONS_H

namespace internal {

template <typename T>
struct traits;

template <typename T>
struct traits<const T> : traits<T> {};

template <typename Functor>
struct functor_traits;

template <typename T>
struct functor_traits<const T> : functor_traits<T> {};

template <typename T>
struct evaluator_base;

template <typename T>
struct evaluator;

template <typename T>
struct packet_traits;

}

template <typename Derived>
class MatrixBase;

template <typename Scalar>
class Matrix;

#endif
