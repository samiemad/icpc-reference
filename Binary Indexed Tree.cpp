const int MAXN = 100005;
int BIT[MAXN];
void update(int x, int v) {
  for (; x < MAXN; x += (x & -x)) BIT[x] += v;
}
int query(int x) {
  int r = 0;
  for (; x > 0; x -= (x & -x)) r += BIT[x];
  return r;
}
// BIT in 2D:
int tree[1025][1025], arr[1025][1025], n;
char s[4];
inline void update(int x, int y, int val) {
  for (; x <= n; x += (x & -x)) {
    for (int y1 = y; y1 <= n; y1 += (y1 & -y1)) {
      tree[x][y1] += val;
    }
  }
}
inline int read(int x, int y) {
  int sum = 0;
  for (; y > 0; y -= (y & -y)) {
    for (int x1 = x; x > 0; x1 -= (x1 & -x1)) {
      sum += tree[x1][y];
    }
  }
  return sum;
}