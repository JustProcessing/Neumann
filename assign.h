#ifndef ASSIGN_H
#define ASSIGN_H

#include <stdio.h>
#include "packets.h"

namespace internal {

template <typename DstScalar, typename SrcScalar>
struct assign_op {
  inline void assign_coeff(DstScalar& a, const SrcScalar& b) const { a = b; }
};

template <typename DstScalar, typename SrcScalar>
struct functor_traits<assign_op<DstScalar, SrcScalar>> {
  enum {
    PacketAccess = packet_traits<DstScalar>::Vectorizable && packet_traits<SrcScalar>::Vectorizable
  };
};

template <typename Context,
          int Traversal = Context::Traversal>
struct assignment_loop;

template <typename Context>
struct assignment_loop<Context, 0> {
  static void run(Context &context) {
    for (Index i = 0; i < context.size(); ++i) {
      context.assign_linear_coeff(i, i);
    }
  }
};

template <typename DstEvaluatorType, typename SrcEvaluatorType, typename Functor>
struct generic_assignment_context {
  DstEvaluatorType m_dst;
  SrcEvaluatorType m_src;
  Functor m_functor;
  
  enum {
    Vectorize = functor_traits<Functor>::PacketAccess
  };
  
  enum {
    Traversal = Vectorize ? 1 : 0
  };
  
  generic_assignment_context(DstEvaluatorType &dst, const SrcEvaluatorType &src, const Functor &func) :
    m_dst (dst), m_src (src), m_functor (func)
  {}
  
  Index size() { return m_src.size(); }
  
  void assign_linear_coeff(Index i, Index j) {
    m_functor.assign_coeff(m_dst.coeff_ref(i), m_src.coeff(j));
  }
};

template <typename Dst, typename Src, typename Func>
void call_dense_assignment_loop(Dst &dst, Src &src, Func &func) {
  typedef evaluator<Dst> DstEvaluatorType;
  typedef evaluator<Src> SrcEvaluatorType;
  
  SrcEvaluatorType src_evaluator(src);
  DstEvaluatorType dst_evaluator(dst);
  
  typedef generic_assignment_context<DstEvaluatorType, SrcEvaluatorType, Func> Context;
  Context context(dst_evaluator, src_evaluator, func);
  
  assignment_loop<Context>::run(context);
}

template <typename Dst, typename Src, typename Func>
struct Assignment {
  static void run(Dst &dst, const Src &src, const Func &func) {
    dst.resize(src.rows(), src.cols());
    call_dense_assignment_loop(dst, src, func);
  }
};

template <typename Dst, typename Src>
void call_assignment(Dst &dst, const Src &src) {
  call_assignment(dst, src, assign_op<typename Dst::Scalar, typename Src::Scalar>());
}

template <typename Dst, typename Src, typename Func>
void call_assignment(Dst &dst, const Src &src, const Func &func) {
  call_assignment_no_alias(dst, src, func);
}

template <typename Dst, typename Src, typename Func>
void call_assignment_no_alias(Dst &dst, const Src &src, const Func &func) {
  Assignment<Dst, Src, Func>::run(dst, src, func);
}

}

#endif
