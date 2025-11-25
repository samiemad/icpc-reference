#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
#define mp(x, y) make_pair(x, y)
#define pb(x) push_back(x)

#define MAXN 100005
int n, q, i, j, c;
int a[MAXN];
int t[MAXN * 4];

void build(int node, int st, int en) {
  if (st == en) {
    t[node] = a[st];
    return;
  }
  build(node * 2, st, (st + en) / 2);
  build(node * 2 + 1, (st + en) / 2 + 1, en);
  t[node] = max(t[node * 2], t[node * 2 + 1]);
}

int query(int node, int st, int en, int i, int j) {
  if (st > j || en < i) return -1e9;
  if (st >= i && en <= j) return t[node];
  int a = query(node * 2, st, (st + en) / 2, i, j);
  int b = query(node * 2 + 1, (st + en) / 2 + 1, en, i, j);
  return max(a, b);
}

void update(int node, int st, int en, int x, int v) {
  if (st > x || en < x) return;
  if (st == en) {
    t[node] = v;
    return;
  }
  update(node * 2, st, (st + en) / 2, x, v);
  update(node * 2 + 1, (st + en) / 2 + 1, en, x, v);
  t[node] = max(t[node * 2], t[node * 2 + 1]);
}

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i];
  build(1, 0, n - 1);
  cin >> q;
  while (q--) {
    cin >> c >> i >> j;
    if (c)
      cout << query(1, 0, n - 1, i, j) << "\n";
    else
      update(1, 0, n - 1, i, j);
  }
  return 0;
}
