#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAX_K = 7;

int k, N;
int cols[MAX_K];
int grid[MAX_K][MAX_K];
int dp[1024 * 1024];

int brute(int y, int x) {

  if (y >= k) 
    return 1;
  if (x >= cols[y])
    return brute(y + 1, 0);

  int hash = 0;
  if (x == 0 && (y == 2)) {
    for (int i = 0; i < cols[y-1]; i++) {
      hash *= N;
      hash += grid[y-1][i] - 1;
    }
  }
  if (dp[hash] != -1)
    return dp[hash];

  int s = 0;
  if (y > 0) 
    s = max(s, grid[y-1][x] + 1);
  if (x > 0) 
    s = max(s, grid[y][x-1]);

  int cnt = 0;
  for (int i = s; i <= N; i++) {
    grid[y][x] = i;
    cnt += brute(y, x + 1);
  }

  if (dp[hash] == -1 && hash != 0) 
    dp[hash] = cnt;

  return cnt;
}

int main() {
  while (scanf("%d", &k) == 1) {
    for (int i = 0; i < k; i++) {
      scanf("%d", &cols[i]);  
    }
    scanf("%d", &N);
    memset(dp, -1, sizeof(dp));

    int ans = 0;
    for (int i = 1; i <= N; i++) {
      grid[0][0] = i;
      ans += brute(0, 1);
    }
    printf("%d\n", ans);
  }
  return 0;
}
