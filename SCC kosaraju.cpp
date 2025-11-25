#include <bits/stdc++.h>
using namespace std;
#define pb(x) push_back(x)
#define MAXN 100005

vector<vector<int> > adj, rdj;  // graph and its transpose:
vector<vector<int> > nodes;     // list of nodes that belong to scc x:
vector<set<int> > sccAdj;       // the adjList of the result SCC DAG:
int v[MAXN];                    // dfs visited:
int comp[MAXN];  // comp[x] is the number of SCC that node x belong to:
int ncmp;        // ncmp is the total number of scc
int n, m;
stack<int> s;

void dfs1(int x) {
  v[x] = 1;
  for (int i = 0; i < adj[x].size(); ++i) {
    int nx = adj[x][i];
    if (!v[nx]) dfs1(nx);
  }
  s.push(x);
}

void rdfs(int x, int cmp) {
  comp[x] = cmp;
  nodes[cmp].pb(x);

  v[x] = 1;
  for (int i = 0; i < rdj[x].size(); ++i) {
    int nx = rdj[x][i];
    if (!v[nx]) {
      rdfs(nx, cmp);
    } else if (comp[nx] != comp[x]) {
      sccAdj[comp[nx]].insert(comp[x]);
    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int tc = 1; tc <= T; ++tc) {
    scanf("%d%d", &n, &m);
    // clear the global variables:
    adj.assign(n + 1, vector<int>());
    rdj.assign(n + 1, vector<int>());
    sccAdj.clear();
    nodes.clear();
    memset(v, 0, sizeof v);
    ncmp = 0;

    // read the graph:
    for (int i = 1; i <= m; ++i) {
      int a, b;
      scanf("%d%d", &a, &b);
      adj[a].pb(b);
      rdj[b].pb(a);
    }

    // do the first dfs:
    for (int i = 1; i <= n; ++i) {
      if (!v[i]) {
        dfs1(i);
      }
    }

    // do the second dfs to find the SCCs:
    memset(v, 0, sizeof v);
    while (!s.empty()) {
      int x = s.top();
      s.pop();
      if (!v[x]) {
        sccAdj.push_back(set<int>());
        nodes.push_back(vector<int>());
        rdfs(x, ncmp++);
      }
    }
  }
  return 0;
}
