#include <cstdio>
#include <cstring>
#include <algorithm>

const long long INF = 1e14;

int n;
char s[1005];

long long min[1005][1005];
long long max[1005][1005];

bool known[1005][1005];
bool cache[1005][1005];

bool solve(int a, int b) {
  if (a >= b)
    return false;

  if (known[a][b])
    return cache[a][b];

  bool works = false;

  if (s[a] == '+') {
    // Binary +
    for (int i = a + 2; i < b; i++) {
      if (solve(a + 1, i) && solve(i, b)) {
        works = true;
        min[a][b] = std::min(min[a][b], min[a+1][i] + min[i][b]);
        max[a][b] = std::max(max[a][b], max[a+1][i] + max[i][b]);
      }
    }
  } else if (s[a] == '-') {
    // Binary -
    for (int i = a + 2; i < b; i++) {
      if (solve(a + 1, i) && solve(i, b)) {
        works = true;
        min[a][b] = std::min(min[a][b], min[a+1][i] - max[i][b]);
        max[a][b] = std::max(max[a][b], max[a+1][i] - min[i][b]);
      }
    }

    // Unary -
    if (solve(a+1, b)) {
      works = true;
      min[a][b] = std::min(min[a][b], -max[a+1][b]);
      max[a][b] = std::max(max[a][b], -min[a+1][b]);
    }
  } else {
    if (b - a <= 9 && (a+1 == b || s[a] != '0')) {
      long long x = 0;
      works = true;

      for (int i = a; i < b; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
          x = 10*x + s[i] - '0';
        } else {
          works = false;
          break;
        }
      }

      if (works)
        min[a][b] = max[a][b] = x;
    }
  }

  known[a][b] = true;
  cache[a][b] = works;
  return works;
}

void solve() {
  char *p = strchr(s, '\n');
  if (p) *p = 0;
  n = strlen(s);

  for (int i = 0; i <= n; i++)
    for (int k = 0; k <= n; k++)
      min[i][k] = INF, max[i][k] = -INF, known[i][k] = cache[i][k] = false;

  solve(0, n);
  printf("%lld %lld\n", min[0][n], max[0][n]);
}

int main() {
  while (fgets(s, sizeof(s), stdin))
    solve();
  return 0;
}
