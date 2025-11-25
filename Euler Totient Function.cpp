#include <vector>
using namespace std;
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
