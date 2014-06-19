#include <cstdio>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
using namespace std;

struct car_t {
  int t, v;
  int weight;

  bool operator<(const car_t& other) const {
    return t == other.t ? v < other.v : t < other.t;
  }
} c[35005];

struct frac_t {
  int a, b;

  frac_t() {}
  frac_t(int _a, int _b): a(_a), b(_b) {
    int g = __gcd(a, b);
    a /= g;
    b /= g;
  }

  bool operator<(const frac_t& other) const {
    return a * other.b < other.a * b;
  }
};

int n;

void solve() {
  for (int i = 0; i < n; i++) {
    scanf("%d %d", &c[i].t, &c[i].v);
    c[i].weight = 1;
  }

  sort(c, c+n);

  vector<car_t> temp;
  temp.push_back(c[0]);
  for (int i = 1; i < n; i++)
    if (c[i].t == temp.back().t && c[i].v == temp.back().v)
      temp.back().weight++;
    else
      temp.push_back(c[i]);
  copy(temp.begin(), temp.end(), c);
  n = temp.size();

  int best = 0;
  for (const auto& o : temp)
    best = max(best, o.weight);

  list<car_t> l;
  for (int i = 0; i < n; i++) {
    // Fuck it, lambda it
    l.remove_if([i](const car_t& o) {
      return o.v * (c[i].t - o.t) > 100;
    });

    map<frac_t, int> m;
    for (const auto& o : l) {
      if (o.v >= c[i].v)
        continue;

      int dt = c[i].t - o.t;
      frac_t t(o.v * dt, c[i].v - o.v);

      if (t.a * c[i].v <= 100 * t.b) {
        m[t] += o.weight;
      }
    }

    for (const auto& p : m) {
      best = max(best, p.second + c[i].weight);
    }

    l.push_back(c[i]);
  }

  printf("%d\n", best);
}

int main() {
  while (scanf("%d", &n) == 1)
    solve();
  return 0;
}
