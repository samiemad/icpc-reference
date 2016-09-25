// source code copied from https://sites.google.com/site/indy256/ with minor modifications

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
#define mp(x,y) make_pair(x,y)
#define pb(x) push_back(x)

const ll maxnodes = 5005;

ll nodes = maxnodes, src, dest;
ll dist[maxnodes], q[maxnodes], work[maxnodes];

struct Edge {
  ll to, rev;
  ll f, cap;
};

vector<vector<Edge> > g(maxnodes);

// Adds bidirectional edge
// to construct a directed graph just put 0 as edge b's capacity
void addEdge(ll s, ll t, ll cap){
  Edge a = {t, g[t].size(), 0, cap};
  Edge b = {s, g[s].size(), 0, cap}; // use this for bidirectional graph
//  Edge b = {s, g[s].size(), 0, 0}; // use this for directed graph
  g[s].push_back(a);
  g[t].push_back(b);
}

bool dinic_bfs() {
  fill(dist, dist + nodes, -1);
  dist[src] = 0;
  ll qt = 0;
  q[qt++] = src;
  for (ll qh = 0; qh < qt; qh++) {
    ll u = q[qh];
    for (ll j = 0; j < (ll) g[u].size(); j++) {
      Edge &e = g[u][j];
      ll v = e.to;
      if (dist[v] < 0 && e.f < e.cap) {
        dist[v] = dist[u] + 1;
        q[qt++] = v;
      }
    }
  }
  return dist[dest] >= 0;
}

ll dinic_dfs(ll u, ll f) {
  if (u == dest)
    return f;
  for (ll &i = work[u]; i < (ll) g[u].size(); i++) {
    Edge &e = g[u][i];
    if (e.cap <= e.f) continue;
    ll v = e.to;
    if (dist[v] == dist[u] + 1) {
      ll df = dinic_dfs(v, min(f, e.cap - e.f));
      if (df > 0) {
        e.f += df;
        g[v][e.rev].f -= df;
        return df;
      }
    }
  }
  return 0;
}

ll maxFlow(ll _src, ll _dest) {
  src = _src;
  dest = _dest;
  ll result = 0;
  while (dinic_bfs()) {
    fill(work, work + nodes, 0);
    while (ll delta = dinic_dfs(src, INT_MAX))
      result += delta;
  }
  return result;
}

int main() {
	int x,y,c;
	int n,m;
	cin>>n>>m;
	g.assign(n+1, vector<Edge>());
	// for multiple test cases just re assign this vector and you're good to go :)
	
	for(int i=1; i<=m; ++i){
		cin>>x>>y>>c;
		addEdge(x,y,c);
	}
	cout<<maxFlow(1,n)<<"\n";
	return 0;
}
