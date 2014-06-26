#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
  int AB, AC, BD;
  while (scanf("%d%d%d", &AB, &AC, &BD) == 3) {
    int om = AB * AC;
    int nom = BD - AC;
    int g = __gcd(om, nom);
    om /= g;
    nom /= g;
    printf("%d/%d\n", om, nom);
  }

  return 0;
}
