typedef unsigned int Index;

#include "forward_declarations.h"
#include "packets.h"
#include "core_evaluators.h"
#include "assign.h"
#include "matrix.h"

int main(void) {
  Matrix<double> a(3, 3);
  Matrix<double> b;
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 1) = 6;
  a(2, 2) = 3;
  b = a;
}
