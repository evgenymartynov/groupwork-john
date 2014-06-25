#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

/*
 ** find rational approximation to given real number
 ** David Eppstein / UC Irvine / 8 Aug 1993
 **
 ** With corrections from Arno Formella, May 2008
 **
 **   x is real number to approx
 **   maxden is the maximum denominator allowed
 **
 ** based on the theory of continued fractions
 ** if x = a1 + 1/(a2 + 1/(a3 + 1/(a4 + ...)))
 ** then best approximation is found by truncating this series
 ** (with some adjustments in the last term).
 **
 ** Note the fraction can be recovered as the first column of the matrix
 **  ( a1 1 ) ( a2 1 ) ( a3 1 ) ...
 **  ( 1  0 ) ( 1  0 ) ( 1  0 )
 ** Instead of keeping the sequence of continued fraction terms,
 ** we just keep the last partial product of these matrices.
 */

void to_frac(double x) {
  long m[2][2];
  long maxden;
  long ai;

  double startx = x;
  maxden = 1e9;

  /* initialize matrix */
  m[0][0] = m[1][1] = 1;
  m[0][1] = m[1][0] = 0;

  /* loop finding terms until denom gets too big */
  while (m[1][0] *  ( ai = (long)x ) + m[1][1] <= maxden) {
    long t;
    t = m[0][0] * ai + m[0][1];
    m[0][1] = m[0][0];
    m[0][0] = t;
    t = m[1][0] * ai + m[1][1];
    m[1][1] = m[1][0];
    m[1][0] = t;
    if(x==(double)ai) break;     // AF: division by zero
    x = 1/(x - (double) ai);
    if(x>(double)0x7FFFFFFF) break;  // AF: representation failure
  } 

  printf("%ld/%ld\n", m[0][0], m[1][0],
      startx - ((double) m[0][0] / (double) m[1][0]));
}

int main() {
  int AB, AC, BD;
  while (scanf("%d%d%d", &AB, &AC, &BD) == 3) {
    double m = -AB / (double)(BD - AC);
    double c = -m * BD; 
    to_frac(c - AB); 
  }

  return 0;
}
