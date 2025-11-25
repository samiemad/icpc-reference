#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
#define mp(x, y) make_pair(x, y)
#define pb(x) push_back(x)

int n, m, ans, timer;
vvi adj;
vvi tr;
vi num, low, comp;
vector<ii> bridges;
stack<int> st;
int ncmp;
void biCon(int x, int p) {
  st.push(x);
  low[x] = num[x] = ++timer;
  for (int i = 0; i < adj[x].size(); ++i) {
    int nx = adj[x][i];
    if (nx == p) continue;
    if (num[nx] == -1) {
      biCon(nx, x);
      if (low[nx] > num[x]) {
        cerr << "bridge at " << x << ", " << nx << "\n";
        bridges.push_back(make_pair(x, nx));
      }
      if (p != -1 && low[nx] >= num[x]) cp = 1;
      if (p == -1 && rch > 1) cp = 1;
      low[x] = min(low[x], low[nx]);
    } else {
      low[x] = min(low[x], num[nx]);
    }
  }
  if (cp) {
    cerr << "cut point at " << x << "\n";
    cutPoints.pb(x);
  }
  if (low[x] == num[x]) {
    ++ncmp;
    while (!st.empty()) {
      int y = st.top();
      st.pop();
      comp[y] = ncmp;
      if (y == x) break;
    }
  }
}

int main() {
  int T, tc = 0;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    // initialize the global variables
    adj.assign(n + 1, vi());
    num.assign(n + 1, -1);
    low.assign(n + 1, -1);
    comp.assign(n + 1, -1);
    bridges.clear();
    ncmp = 0;
    timer = 0;
    while (!st.empty()) st.pop();

    // read the graph:
    for (int i = 0; i < m; ++i) {
      int x, y;
      scanf("%d%d", &x, &y);
      adj[x].pb(y);
      adj[y].pb(x);
    }
    // find the bi-connected components in the graph.
    biCon(0, -1);

    // create a tree whose nodes are the bi-connected-components and edges are
    // the bridges in the original graph.
    tr.assign(ncmp + 1, vi());
    for (int i = 0; i < bridges.size(); ++i) {
      ii& b = bridges[i];
      tr[comp[b.first]].pb(comp[b.second]);
      tr[comp[b.second]].pb(comp[b.first]);
    }
  }
  return 0;
}
