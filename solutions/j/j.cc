#include <cstdio>
#include <cstring>

const int INF = 1e6;

int n;
char buf[10000];

int balls[2005];
int tree[2005][2];

int build(char* &s) {
  if (s[1] != '(') {
    int i = n++;
    balls[i] = s[1] == 'B';
    tree[i][0] = tree[i][1] = 0;

    s += 2 + balls[i];  // "()" or "(B)"
    return i;
  } else {
    s++;
    int i = n++;
    tree[i][0] = build(s);
    tree[i][1] = build(s);
    balls[i] = balls[tree[i][0]] + balls[tree[i][1]];
    s++;
    return i;
  }
}


int solve(int at, int bal) {
  // TODO: cache

  if (tree[at][0] == 0) {  // leaf
    if (bal == 0 || bal == 1)
      return bal != balls[at];
    else
      return INF;
  }

  int best = INF;

  if (bal % 2 == 0) {
    int a = solve(tree[at][0], bal / 2);
    int b = solve(tree[at][1], bal / 2);

    if (best > a + b)
      best = a + b;
  } else {
    int small = bal / 2;
    int large = bal / 2 + 1;

    int a = solve(tree[at][0], small);
    int b = solve(tree[at][1], large);

    if (best > a + b)
      best = a + b;

    a = solve(tree[at][0], large);
    b = solve(tree[at][1], small);

    if (best > a + b)
      best = a + b;
  }

  return best;
}


void solve() {
  char *p = strchr(buf, '\n');
  if (p) *p = 0;

  int len = strlen(buf);
  if (!len)
    return;

  n = 0;
  memset(balls, 0, sizeof(balls));
  memset(tree, 0, sizeof(tree));

  build(p = buf);

  int res = solve(0, balls[0]);
  if (res == INF)
    printf("impossible\n");
  else
    printf("%d\n", res / 2);
}

int main() {
  while (fgets(buf, sizeof(buf), stdin))
    solve();
  return 0;
}
