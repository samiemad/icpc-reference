const int MAXN = 1e5 + 5;
int m = 0, n = 0, cost[MAXN], P[MAXN];
struct Edge {
  int u, v, cap, cost;
} edge[MAXN];
void addedge(int from, int to, int cap, int cost) {
  edge[++m].u = from, edge[m].v = to, edge[m].cap = cap, edge[m].cost = cost;
  edge[++m].u = to, edge[m].v = from, edge[m].cap = 0, edge[m].cost = -1 * cost;
}
bool get_path(int src, int snk) {
  for (int j = src; j <= snk; j++) cost[j] = (1 << 28);
  cost[src] = 0;
  bool upd = true;
  for (int it = 1; it <= n + 2 && upd; it++) {
    upd = 0;
    for (int j = 1; j <= m; j++) {
      if (edge[j].cap > 0 && cost[edge[j].u] != (1 << 28)

          && cost[edge[j].v] > cost[edge[j].u] + edge[j].cost) {
        upd = true;
        cost[edge[j].v] = cost[edge[j].u] + edge[j].cost;
        P[edge[j].v] = j;
      }
      // cout<<j<<endl;
    }
  }
  return (cost[snk] != (1 << 28));
}
int MIN_COST_MAX_FLOW(int src, int snk) {
  int ans = 0;
  while (get_path(src, snk)) {
    // cout<<cost[snk]<<endl;
    for (int node = snk; node != src; node = edge[P[node]].u) {
      --edge[P[node]].cap;
      if (P[node] % 2)
        edge[P[node] + 1].cap++;
      else
        edge[P[node] - 1].cap++;
      // cout<<node<<endl;
    }
    ans += cost[snk];
    // cout<<cost[snk]<<endl;
  }
  return ans;
}