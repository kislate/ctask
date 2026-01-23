#include "ancient2.h"

#include <string>
#include <vector>

namespace {

int variable_example = 1;

}  // namespace

std::string Solve(int N) {
  int m = 2;
  std::vector<int> a(m), b(m);
  a[0] = 0;
  a[1] = 1;
  b[0] = 0;
  b[1] = 1;
  variable_example = Query(m, a, b);
  std::string s(N, '0');
  s[0] = '1';
  return s;
}
