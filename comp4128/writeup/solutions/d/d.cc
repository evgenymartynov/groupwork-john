#include <stdio.h>
#include <string.h>

#define MAX_K (7)
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

int rows, n;
int cols[MAX_K];
int min[MAX_K][MAX_K];
int max[MAX_K][MAX_K];
int depth[MAX_K][MAX_K];
int grid[MAX_K][MAX_K];

void debug_print() {
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols[y]; x++) {
      printf("%d-%d ", min[y][x], max[y][x]); 
    }
    printf("\n");
  }
  printf("--\n");
}

int increment(int y) {
  int x = cols[y] - 1;
  int val = grid[y][x--];
  while (x >= 0) {
    if (grid[y][x] < val && grid[y][x] < max[y][x]) {
      grid[y][x]++;
      return 1;
    }
  }
  x = cols[y] - 1;
  if (val < max[y][x]) {
    grid[y][x]++;
  } else {
    return 0;
  }
}

int main() {
  while (scanf("%d", &rows) == 1) {
    for (int y = 0; y < rows; y++) {
      scanf("%d", &cols[y]);
    }

    scanf("%d", &n);
    printf("(%d)\n", n);
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
        int up = (y == 0) ? 0 : min[y-1][x];
        int left = (x == 0) ? up + 1 : min[y][x-1];
        min[y][x] = MIN(left, up + 1);   
        max[y][x] = n - depth[y][x];
      }
    }

    int ans = 0;
    memcpy(grid, min, sizeof(grid));
    debug_print();

    printf("ans %d\n", ans);
  }
  return 0;
}

// 1: (1,2,3,4) * (2,3,4) = 12 ways
// 2: (2,3,4) * (3,4) = 6 ways
// 3: (3, 4) * (4) = 2 ways = 20 ways
