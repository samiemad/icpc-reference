while(st<end) {int mid=st+(end-st+1)/2;if(ok(mid)) st=mid; else end=mid-1;}
while(st<end) {int mid=st+(end-st) /2;if(ok(mid)) end=mid; else st=mid+1;}
int st = begin, size = (end - begin) / 2;
for (; size > EPS; size *= 0.5) {  if (ok(st + size)) st += size;}
// Ternary Search
double ternarySearch(double left, double right) {
  while (right - left > EPS) {
    double g = left + (right - left) / 3, h = left + 2 * (right - left) / 3;
    if (f(g) < f(h))  // finds the min value.
      right = h;
    else
      left = g;
  }  // change < to > to find the max value (the fn inc then dec)
  return f((left + right) / 2);
}