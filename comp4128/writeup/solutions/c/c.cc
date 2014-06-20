#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
using namespace std;

template<class T>
void splitstr(const string &s, vector<T> &out) {
  istringstream in(s);
  out.clear();
  copy(istream_iterator<T>(in), istream_iterator<T>(), back_inserter(out));
}


int n, first;
int cards[1115];
bool known[1115];
double cache[1115];

double solve(int at) {
  if (at >= n)
    return 0;
  if (known[at])
    return cache[at];

  double &res = cache[at];

  if (cards[at]) {
    res = solve(at + cards[at]);
  } else {
    for (int i = 2; i <= 11 && at + i < n; i++) {
      if (i == 10) {
        res += 4 * solve(at + i);
      } else {
        res += solve(at + i);
      }
    }

    res /= 13.0;
  }

  known[at] = true;
  return res;
}

void solve() {
  memset(cards, 0, sizeof(cards));
  memset(known, 0, sizeof(known));
  memset(cache, 0, sizeof(cache));

  char buf[1000];
  fgets(buf, sizeof(buf), stdin);

  int val[105];
  vector<string> temp;
  splitstr(buf, temp);
  for (int i = 0; i < n; i++) {
    if (isdigit(temp[i][0]))
      val[i] = atoi(temp[i].c_str());
    else
      val[i] = temp[i][0] == 'A' ? 11 : 10;
  }

  int at = first - 1;
  for (int i = 0; i < n; i++)
    at += cards[at] = val[i];

  known[at-val[n-1]] = true;
  cache[at-val[n-1]] = 1;

  n = at + 1;

  double p = 0;
  for (int i = 0; i < 10; i++)
    p += solve(i);
  printf("%.9f\n", p / 10);
}

int main() {
  while (scanf("%d %d ", &n, &first) == 2)
    solve();
  return 0;
}
