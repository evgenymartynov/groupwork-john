#include <stdio.h>
#include <string.h>

#define MAX_K (7)
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

int rows, n;
int cols[MAX_K];
int depth[MAX_K][MAX_K];
int grid[MAX_K][MAX_K];
int finished;
int ans;

inline int min(int x, int y) {
  int up = (y == 0) ? 0 : grid[y-1][x];
  int left = (x == 0) ? up + 1 : grid[y][x-1];
  return MAX(left, up + 1);
}

inline int max(int x, int y) {
  int up = (y == 0) ? n : grid[y-1][x];
  int left = (x == 0) ? up + 1 : grid[y][x-1];
  return (n - depth[y][x]);
}

int increment(int y) {
  if (y < 0) 
    return 0;

  for (int x = cols[y] - 1; x >= 0; x--) {
    if (grid[y][x] < max(x, y)) {
      grid[y][x]++;
      for (int i = x + 1; i < cols[y]; i++) {
        grid[y][i] = min(i, y);
      }
      return 1;
    }
  }

  if (y == 0) 
    printf("finished!\n");
  return 0;
}

void debug_print() {
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols[y]; x++) {
      printf("%d ", grid[y][x]); 
    }
    printf("\n");
  }
  printf("--\n");
}

int main() {
  while (scanf("%d", &rows) == 1) {

    finished = 0;
    for (int y = 0; y < rows; y++) {
      scanf("%d", &cols[y]);
    }

    scanf("%d", &n);
    memset(depth, -1, sizeof(depth));
    for (int y = 0; y < rows; y++) {
      for (int x = 0; x < cols[y]; x++) {
        for (int i = y; i >= 0; i--) {
          depth[i][x]++;
        }
      }
    }

    for (int y = 0; y < rows; y++) {
      for (int x = 0; x < cols[y]; x++) {
        grid[y][x] = min(x, y);
      }
    }

    ans = 1;
    debug_print();
    for (int row = rows - 1; row >= 0; row--) {
      printf("doing row %d\n", row);
      while (increment(row)) {
        ans++;
        for (int y = row + 1; y < rows; y++) {
          for (int x = 0; x < cols[y]; x++) {
            grid[y][x] = min(x, y);
          }
        }
        debug_print();
        for (int current = rows - 1; current > row; current--) {
          while (increment(current)) {
            debug_print();
            ans++;
          }
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}

// 1: (1,2,3,4) * (2,3,4) = 12 ways
// 2: (2,3,4) * (3,4) = 6 ways
// 3: (3, 4) * (4) = 2 ways = 20 ways
