#include <vector>
#include <math.h>
using namespace std;
typedef long long ll;
vector<int> factor(int n) {
  vector<int> f;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      f.push_back(i);
      while (n % i == 0) {
        n /= i;
      }
    }
  }
  if (n != 1) f.push_back(n);
  return f;
}

int phi(int n) {
  vector<int> p = factor(n);
  for (int i = 0; i < (int)p.size(); i++) {
    if (i && p[i] == p[i - 1]) continue;
    n /= p[i];
    n *= p[i] - 1;
  }
  return n;
}
ll sumDiv(ll N) {
  ll PF_idx = 0, PF = primes[PF_idx], ans = 1;  // start from ans = 1
  while (N != 1 && (PF * PF <= N)) {
    ll power = 0;
    while (N % PF == 0) {
      N /= PF;
      power++;
    }
    ans *= ((ll)pow((double)PF, power + 1.0) - 1) / (PF - 1);  // formula
    PF = primes[++PF_idx];
  }
  if (N != 1) ans *= ((ll)pow((double)N, 2.0) - 1) / (N - 1);  // last one
  return ans;
}