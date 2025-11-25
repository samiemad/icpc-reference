#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
#define mp(x, y) make_pair(x, y)
#define pb(x) push_back(x)

#define SZ 802

int flow[SZ][SZ], cap[SZ][SZ], prv[SZ], f;
// initialize cap with 0 for each test case!

vector<vector<int> > L;
// L is the adj List of the graph

bool augmenting(int& N, int s, int t) {
  fill(prv, prv + N, -1);
  queue<int> Q;
  Q.push(s);
  prv[s] = -2;

  int aux;

  while (!Q.empty()) {
    aux = Q.front();
    Q.pop();

    for (int i = 0; i < L[aux].size(); ++i)
      if (flow[aux][L[aux][i]] < cap[aux][L[aux][i]] && prv[L[aux][i]] == -1) {
        prv[L[aux][i]] = aux;
        if (L[aux][i] == t) goto found;
        Q.push(L[aux][i]);
      }
  }

  return false;

found:

  int x = INT_MAX, cur = t, next;

  while (cur != s) {
    next = prv[cur];
    x = min(x, cap[next][cur] - flow[next][cur]);
    cur = next;
  }

  f += x;
  cur = t;

  while (cur != s) {
    next = prv[cur];
    flow[next][cur] += x;
    flow[cur][next] -= x;
    cur = next;
  }

  return true;
}

int main() {
  int m, c, n, x, y;
  cin >> n >> m;
  L.assign(n + 1, vi());
  for (int i = 0; i < m; ++i) {
    cin >> x >> y >> c;
    L[x].pb(y);
    L[y].pb(x);
    cap[x][y] += c;
    cap[y][x] += c;
  }
  int SRC = 1, SINK = N;
  while (augmenting(n, SRC, SINK)) {
    //		cerr<<"f = "<<f<<"\n";
  }
  cout << f << "\n";
  return 0;
}
