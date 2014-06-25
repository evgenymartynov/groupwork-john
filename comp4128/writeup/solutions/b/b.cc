#include <stdio.h>
#include <string.h>
#define MAX_N (455)
#define MAX_M (905)
int n, m;

int silver[MAX_N];
char adj[MAX_N][MAX_N];
struct edge {
  int u, v;
} e[MAX_M];

int main() {
  while (scanf("%d%d", &n, &m) == 2) {
    
    // silver carries by each ship
    int s;
    for (int i = 1; i <= n; i++) {
      scanf("%d", &s);
      silver[i] = s; 
    }
    
    // existing chains
    int u, v;
    memset(adj, 0, sizeof(adj));
    for (int i = 0; i < m; i++) {
      scanf("%d%d", &u, &v); 
      adj[u][v] = 1;
      adj[v][u] = 1;
      e[i].u = u;
      e[i].v = v;
    }
    
    // check n=2 and n=3 cliques
    int max_silver = 0;
    for (int i = 0; i < m; i++) {
      int u = e[i].u;
      int v = e[i].v;

      // consider adding all vertices to 2-vertex clique
      int extra = 0;
      for (int k = 1; k <= n; k++) {
        if (adj[k][u] && adj[k][v]) {
          if (silver[k] > extra)
            extra = silver[k];
        }
      }
      
      // update max silver clique, if required
      int total = silver[u] + silver[v] + extra;
      if (total > max_silver) {
        max_silver = total;
      }
    }

    // consider all pairs of edges for n=4 cliques
    for (int i = 0; i < m; i++) {
      int a = e[i].u;
      int b = e[i].v;
      for (int j = 0; j < m; j++) {
        int c = e[j].u;
        int d = e[j].v;
        if (adj[a][b] && adj[a][c] && adj[a][d] &&
            adj[b][c] && adj[b][d] && adj[c][d]) {
          int total = silver[a] + silver[b] + silver[c] + silver[d];
          if (total > max_silver) {
            max_silver = total;
          }
        }
      }
    }

    printf("%d\n", max_silver);
  }
  return 0;
}

