#include <math.h>
typedef long long ll;
int gcd(int a, int b) { return (b == 0 ? a : gcd(b, a % b)); }
int lcm(int a, int b) { return (a * (b / gcd(a, b))); }
int eGCD(int a, int b, int& x, int& y) {  // ax+by=gcd(a,b)
  x = 1;
  y = 0;
  int nx = 0, ny = 1, t, r;
  while (b) {
    r = a / b;
    t = a - r * b;
    a = b;
    b = t;
    t = x - r * nx;
    x = nx;
    nx = t;
    t = y - r * ny;
    y = ny;
    ny = t;
  }
  return a;
}
bool solveLDE(int a, int b, int c, int& x, int& y, int& g) {  // ax+by=c
  g = eGCD(a, b, x, y);
  x *= c / g;
  y *= c / g;
  return (c % g) == 0;
}
int modInv(int a, int m) {  //(a*mi)%m=1
  int mi, r;
  eGCD(a, m, mi, r);
  return (mi + m) % m;
}
bool solve(ll a, ll b, ll c, ll& x) {  //(a*x)%b=c
  ll y, g;
  if (solveLDE(a, b, c, x, y, g) && a * x + b * y == c) {
    if (x < 0) {
      x += (abs(x) / b) * b;
      if (x < 0) x += b;
    }
    return 1;
  }
  return 0;
}