#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int n;
int m[2005][2005];
unsigned int dist[2005];
int from[2005];
bool done[2005];
int mprime[2005][2005];

vector<int> mst[2005];

void dfs(int at, int from, int mrow, int dist) {
  mprime[mrow][at] = dist;

  for (int i = 0; i < (int) mst[at].size(); i++) {
    int to = mst[at][i];
    if (to != from)
      dfs(to, at, mrow, dist + m[at][to]);
  }
}

void solve() {
  memset(dist, -1, sizeof(dist));
  memset(from, -1, sizeof(from));
  memset(done, 0, sizeof(done));

  for (int i = 0; i < n; i++)
    for (int k = 0; k < n; k++)
      scanf("%d", &m[i][k]);
  dist[0] = 0;
  from[0] = 0;

  for (int i = 0; i < n-1; i++) {
    int mi = -1;
    for (int k = 0; k < n; k++)
      if (!done[k] && (mi == -1 || dist[k] < dist[mi]))
        mi = k;
    done[mi] = true;

    for (int k = 0; k < n; k++) {
      if (!done[k] && dist[k] > m[mi][k]) {
        dist[k] = m[mi][k];
        from[k] = mi;
      }
    }
  }

  for (int i = 0; i < n; i++)
    mst[i].clear();
  for (int i = 1; i < n; i++) {
    mst[i].push_back(from[i]);
    mst[from[i]].push_back(i);
  }

  for (int i = 0; i < n; i++)
    dfs(i, -1, i, 0);

//  for (int i = 0; i < n; i++) {
//    for (int k = 0; k < n; k++)
//      printf("%d ", mprime[i][k]);
//    puts("");
//  }

  int a = -1, b = -1, c = 1 << 20;
  for (int i = 0; i < n; i++) {
    for (int k = 0; k < n; k++) {
      if (m[i][k] != mprime[i][k]) {
        if (m[i][k] < c) {
          a = i;
          b = k;
          c = m[i][k];
        }
      }
    }
  }

  for (int i = 1; i < n; i++)
    printf("%d %d %d\n", i+1, from[i]+1, m[i][from[i]]);
  if (a == -1)
    printf("%d %d %d\n", 2, 1, m[0][1]);
  else
    printf("%d %d %d\n", a+1, b+1, c);
  puts("");
}

int main() {
  while (scanf("%d", &n) == 1) {
    solve();
  }

  return 0;
}
