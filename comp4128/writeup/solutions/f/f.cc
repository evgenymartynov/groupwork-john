#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

void print_date(double JD) {
  double Z = (int)(JD + 0.5);
  double F = Z - (int)Z;

  double W = (int)((Z - 1867216.25) / 36524.25);
  double X = (int)(W / 4);
  double A = Z + 1 + W - X;

  double B = A + 1524;
  double C = (int)((B - 122.1) / 365.25);
  double D = (int)(365.25 * C);
  double E = (int)((B - D) / 30.6001);

  double DAY = B - D - (int)(30.6001 * E) + F;
  double MONTH = (E > 13) ? E - 13 : E - 1;
  double YEAR = (MONTH < 3) ? C - 4715 : C - 4716;
  printf("%04d-%02d-%02d\n", (int)YEAR, (int)MONTH, (int)DAY);
}

int main() {
 
  int d, m, y;
  while (scanf("%04d-%02d-%02d", &y, &m, &d) == 3) {

    if (m < 3) {
      y--;
      m += 12;
    }

    double C = 0;
    double E = (int)(365.25 * (y + 4716));
    double F = (int)(30.6001 * (m + 1));
    double JD = C + (double)d + E + F - 1524.5;

    print_date(JD+1);
  }

  return 0;
}
