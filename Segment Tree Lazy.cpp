#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN = 100005;
const ll INF = 1e9 + 9;
ll tree[MAXN * 4];
ll lazy[MAXN * 4];
void unlazy(int node, int st, int en) {
  if (lazy[node] == 0) return;
  tree[node] = max(tree[node], lazy[node]);  // Apply update
  if (st != en) {  // If not leaf, push lazy update to children
    lazy[node * 2] = max(lazy[node * 2], lazy[node]);
    lazy[node * 2 + 1] = max(lazy[node * 2 + 1], lazy[node]);
  }
  lazy[node] = 0;  // Clear lazy flag
}
void updateLazy(int node, int st, int en, int p, int q, ll val) {
  if (en < st || q < st || en < p)
    return;  // range [p,q] completely outside current node
  unlazy(node, st, en);
  if (p <= st && en <= q) {  // node fully inside range [p,q]
    tree[node] = max(tree[node], val);
    if (st != en) {  // Not a leaf node
      lazy[2 * node] = max(lazy[2 * node], val);
      lazy[2 * node + 1] = max(lazy[2 * node + 1], val);
    }
    return;
  }
  int mid = (st + en) / 2;
  updateLazy(node * 2, st, mid, p, q, val);          // Update left child
  updateLazy(node * 2 + 1, mid + 1, en, p, q, val);  // Update right child
  tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
  return;
}
ll query(int node, int st, int en, int p, int q) {
  if (en < st || q < st || en < p)
    return -INF;  // range [p,q] completely outside current node
  unlazy(node, st, en);
  if (p <= st && en <= q) {  // node fully inside range [p,q]
    return tree[node];
  }
  int mid = (st + en) / 2;
  ll q1 = query(node * 2, st, mid, p, q);
  ll q2 = query(node * 2 + 1, mid + 1, en, p, q);
  return max(q1, q2);
}
int main() {
  updateLazy(1, 0, MAXN - 1, 0, 5, 5);
  updateLazy(1, 0, MAXN - 1, 0, 10, 1);
  cout << query(1, 0, MAXN - 1, 0, 10) << "\n";
  return 0;
}
