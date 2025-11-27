#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN = 100005;
const ll INF = 1e9 + 9;
// Edit node representation
typedef long long node;
const int MAXN = 1000006;
node seg[4 * MAXN];
int arr[MAXN];
node laz[4 * MAXN];
//-----------------------------------------------
// Edit the following
//-----------------------------------------------
const bool LAZY = true;
const node neutral = 0;
void initNode(int nodeID, int elemID) { seg[nodeID] = arr[elemID]; }
node join(node ch1, node ch2) { return (ch1 + ch2); }
void updateNode(int ID, int b, int e, node val) {
  seg[ID] += (e - b + 1) * val;
}
void updateChildrenLaz(int ID, node val) {
  if (!LAZY) return;
  laz[2 * ID] += val;
  laz[2 * ID + 1] += val;
}
void clearLaz(int ID) {
  if (!LAZY) return;
  laz[ID] = 0;
}
void unlazy(int ID, int b, int e) {
  if (!LAZY) return;
  updateChildrenLaz(ID, laz[ID]);
  updateNode(ID, b, e, laz[ID]);
  clearLaz(ID);
}
//-----------------------------------------------
void init(int ID, int b, int e) {
  if (b == e) {
    clearLaz(ID);
    initNode(ID, b);
    return;
  }
  int mid = (b + e) / 2;
  init(2 * ID, b, mid);
  init(2 * ID + 1, mid + 1, e);
  clearLaz(ID);
  seg[ID] = join(seg[2 * ID], seg[2 * ID + 1]);
}
void Update(int ID, int b, int e, int i, int j, node val) {
  if (i > e || j < b) {
    unlazy(ID, b, e);
    return;
  }
  if (b == e) {
    unlazy(ID, b, e);
    updateNode(ID, b, e, val);
    return;
  }
  if (LAZY && i <= b && e <= j) {
    unlazy(ID, b, e);
    updateChildrenLaz(ID, val);
    updateNode(ID, b, e, val);
    return;
  }
  int mid = (b + e) / 2;
  unlazy(ID, b, e);
  Update(2 * ID, b, mid, i, j, val);
  Update(2 * ID + 1, mid + 1, e, i, j, val);
  seg[ID] = join(seg[2 * ID], seg[2 * ID + 1]);
}
node Query(int ID, int b, int e, int i, int j) {
  if (i <= b && e <= j) {
    unlazy(ID, b, e);
    return seg[ID];
  }
  if (i > e || j < b) {
    return neutral;
  }
  unlazy(ID, b, e);
  int mid = (b + e) / 2;
  node r1 = Query(2 * ID, b, mid, i, j);
  node r2 = Query(2 * ID + 1, mid + 1, e, i, j);
  return join(r1, r2);
}
int main() {
  // ios_base::sync_with_stdio(0);
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, c;
    cin >> n >> c;
    memset(seg, 0, sizeof seg);
    memset(laz, 0, sizeof laz);
    int o, a, b;
    for (int i = 0; i < c; ++i) {
      scanf("%d %d %d", &o, &a, &b);
      a--;
      b--;
      if (o == 1) {
        printf("%lld\n", Query(1, 0, n - 1, a, b));
      } else {
        int x;
        scanf("%d", &x);
        Update(1, 0, n - 1, a, b, x);
      }
    }
  }
  return 0;
}