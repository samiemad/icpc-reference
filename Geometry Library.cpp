// DESCLAIMER: most of this file contents are taken from coach fegla reference, so thanks a lot coach :D
// TODO: split into seperate files?
#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-9;
typedef long double ldouble;

typedef complex<double> point;
const double pi = acos(-1);

#define sz(x) ((int)(x).size())
#define dot(a,b) ((conj(a)*(b)).real())
#define cross(a,b) ((conj(a)*(b)).imag())
#define X real()
#define Y imag()
#define angle(a) atan2((a).imag(),(a).real())
#define length(a) hypot((a).X,(a).Y)
#define length2(a) dot(a,a)
#define normalize(a) ((a)/length(a))
#define polar(r,theta) 	((r)*exp(point(0,theta)))
#define vect(p1,p2) ((p2)-(p1))
#define mid(p1,p2)  (((p1)+(p2))/point(2,0))
#define perp(a) (point(-(a).Y,(a).X))
#define same(a,b) (length2(vect(a,b))<EPS)
#define rotate(v,t) (polar(v,t))
#define rotateabout(v,t,a) 	(rotate(vect(a,v),t)+(a))
#define reflect(p,m) ((conj((p)/(m)))*(m))

int compare(double a, double b) {
	if (fabs(a - b) < EPS)
		return 0;
	else if (a > b)
		return 1;
	else
		return -1;
}

//Points & Lines:
bool segmentIntersect(point a, point b, point p, point q) {
	double d1 = cross(p - a, b - a);
	double d2 = cross(q - a, b - a);
	double d3 = cross(a - p, q - p);
	double d4 = cross(b - p, q - p);
	if (d1 * d2 < 0 && d3 * d4 < 0)
		return true;
	else
		return false;
}

bool lineIntersect(point a, point b, point p, point q, point& r) {
	double d1 = cross(p - a, b - a);
	double d2 = cross(q - a, b - a);
	if (fabs(d2 - d1) < 1e-9)
		return false;
	r = (d1 * q - d2 * p) / (d1 - d2);
	return true;
}

// btgeb eza kan el p 3la el line elle 3lehel 2 points a,b
bool isPointOnLine(point a, point b, point p) {
	return fabs(cross(vect(a,b), vect(a,p))) < EPS;
}

bool isPointOnRay(point a, point b, point p) {
	return dot(vect(a,b),vect(a,p)) > -EPS && isPointOnLine(a, b, p);
}

bool isPointOnSegment(point a, point b, point p) {
	return dot(vect(a,b), vect(a,p)) > -EPS && isPointOnLine(a, b, p)
			&& dot(vect(b,a), vect(b,p)) > -EPS;
}

point projectOnLine(point p, point a, point b) {
	return a + vect(a,b) * dot(vect(a,c), vect(a,b)) / length2(vect(a,b));
}

point rotate_by(const point &p, const point &o, double th) {
	return (p - o) * exp(point(0, th)) + o;
}

point reflect1(const point &p, const point &l1, const point &l2) {
	point z = p - l1;
	point w = l2 - l1;
	return conj(z / w) * w + l1;
}

double pointLineDistance(const point& a, const point& b, const point& p) {
// ab is the line and p is the point
	return fabs(cross(b - a, p - a)) / length(b - a);
}

double pointSegmentDistance(const point& a, const point& b, const point& p) {
	if (dot(p-a,b-a) <= 0)
		return length(p - a);
	if (dot(p-b,a-b) <= 0)
		return length(p - b);
	return pointLineDistance(a, b, p);
}

bool testColinearPoints(const point& a, const point& b, const point& c) {
	return fabs(cross(b - a, c - b)) < EPS;
}

//Triangles:
long double triangleAreaBH(long double b, long double h) {
	return b * h / 2;
}

long double triangleArea2sidesAngle(long double a, long double b,
		long double t) {
	return fabs(a * b * sin(t) / 2);
}

long double triangleArea2anglesSide(long double t1, long double t2,
		long double s) {
	return fabs(s * s * sin(t1) * sin(t2) / (2 * sin(t1 + t2)));
}

long double triangleArea3sides(double a, double b, double c) {
	long double s((a + b + c) / 2);
	return sqrt(s * (s - a) * (s - b) * (s - c));
}

double triangArea3points(const point& a, const point& b, const point& c) {
	return fabs(cross(a,b) + cross(b, c) + cross(c, a)) / 2;
}

ldouble cosineRule(ldouble a, ldouble b, ldouble c) {
	ldouble x = (b * b + c * c - a * a) / (2 * b * c);
	if (x > 1)
		x = 1;
	if (x < -1)
		x = -1;
	return acos(x);
}

// if we have 2 angels A & B and a side length b this function returns the side length a
double sinRuleGetSide(double A, double B, double b) {
	return (sin(A) * b) / sin(B);
}

// if we have 2 sides lengths a & b and an angle B this function returns the angle A
double sinRuleGetAngel(double a, double b, double B) {
	double A = (a * sin(B)) / b;
	if (A > 1)
		A = 1;
	if (A < -1)
		A = -1;
	return asin(A);
}

// Circles:
// checking two circles intersection
int isIntersecting(point c1, point c2, double r1, double r2) {
// 0 if no intersection
// 1 if normally intersecting
// 2 if outside tangent
// 3 if inside tangent
// 4 if C1 contain C2
// 5 if same circule
	if (compare(r1 + r2, length(c1 - c2)) < 0)
		return 0; // no intersection
	if (compare(length(c1 - c2), fabs(r1 - r2)) < 0)
		return 4; // no intersection
	if (length(c1-c2) < 1e-9 && compare(r1, r2) == 0)
		return 5; // same circule
	if (compare(r1 + r2, length(c1 - c2)) == 0)
		return 2;
	if (compare(fabs(r1 - r2), length(c1 - c2)) == 0)
		return 3;
	if (compare(r1 + r2, length(c1 - c2)) > 0)
		return 1;
}

bool lineCirculeIntersection(point p0, point p1, point C, double r, point& r1,
		point& r2) {
	// p0,p1 -> line
	// C,r ->circle
	double a = dot(p1 - p0, p1 - p0);
	double b = 2 * dot(p1 - p0, p0 - C);
	double c = dot(p0-C,p0-C) - r * r;
	double x = b * b - (4 * a * c);
	if (x < -1 * 1e-9)
		return false;    //for sqrt(-x)
	if (fabs(x) < 1e-9)
		x = 0;
	double t1 = (-1 * b + sqrt(x)) / (2 * a);
	double t2 = (-1 * b - sqrt(x)) / (2 * a);
	r1 = p0 + t1 * (p1 - p0);
	r2 = p0 + t2 * (p1 - p0);
	return true;
}

void circuleIntersection(point c1, point c2, double r1, double r2, point& p1,
		point& p2) {
	if (r1 < r2) {
		swap(r1, r2);
		swap(c1, c2);
	}
	double theta1 = angle(c2 - c1);
	long double theta2 = cosineRule(r2, r1, length(c2 - c1));
	p1 = polar(r1, theta1+theta2) + c1;
	p2 = polar(r1, theta1-theta2) + c1;
}

pair<point, double> getCircle2(point a, point b) // el double el awalane el center we el tane el  raduis
		{
	// a, b are diameter(kotr)
	return make_pair((a + b) / point(2, 0), length(b-a) / 2);
}

pair<point, double> getCircle3(point a, point b, point c) // el double el awalane el center we el tane el  raduis
		{

	point v1 = vect(a, b);
	point mid1 = (b + a) / point(2, 0);
	point p1(-1 * v1.Y, v1.X);
	p1 += mid1;
	point v2 = vect(b, c);
	point mid2 = (c + b) / point(2, 0);
	point p2(-1 * v2.Y, v2.X);
	p2 += mid2;
	point C;
	lineIntersect(mid1, p1, mid2, p2, C);
	return make_pair(C, length(C - a));
}

// minimum enclosing circle
// random_shuffle(pnts.begin(),pnts.end());
// needed to enshure O(n)
#define MAXSIZE 100
int ps = 0, rs = 0;
point pts[MAXSIZE], rem[3];
pair<point, double> cir;
void mec() {
	if (rs == 3) {
		cir = getCircle3(rem[0], rem[1], rem[2]);
		return;
	}
	if (ps == 0) {
		if (rs == 2)
			cir = getCircle2(rem[0], rem[1]);
		else
			cir = make_pair(rem[0], 0);
		return;
	}
	ps--;
	mec();
	if (length2(vect(pts[ps],cir.first)) > cir.second * cir.second) {
		rem[rs++] = pts[ps];
		mec();
		rs--;
	}
	ps++;
}

// Polygons:
bool isSimple(vector<point> poly) {
	for (int i = 0; i < poly.size(); ++i) {
		for (int k = i + 1; k < poly.size(); ++k) {
			int j = (i + 1) % poly.size();
			int l = (k + 1) % poly.size();
			if (i == l || j == k)
				continue;
			if (segmentIntersect(poly[i], poly[j], poly[k], poly[l]))
				return false;
		}
	}
	return true;
}

// For convex HULL
struct cmp {
	point about;
	cmp(point c) {
		about = c;
	}
	bool operator()(const point& p, const point& q) const {
		double cr = cross(vect(about,p), vect(about,q));
		if (fabs(cr) < EPS)
			return make_pair(p.Y, p.X) < make_pair(q.Y, q.X);
		return cr > 0;
	}
};

vector<point> pnts, convex;
void convexHull() {
	point mn(1 / 0.0, 1 / 0.0);
	for (int i = 0; i < sz(pnts); i++) {
		if (make_pair(pnts[i].Y, pnts[i].X) < make_pair(mn.Y, mn.X))
			mn = pnts[i];
	}
	sort(pnts.begin(), pnts.end(), cmp(mn));
	convex.clear();
	convex.push_back(pnts[0]);
	if (sz(pnts) == 1)
		return;
	convex.push_back(pnts[1]);
	for (int i = 2; i <= sz(pnts); i++) {
		point c = pnts[i % sz(pnts)];
		while (sz(convex) > 1) {
			point b = convex.back();
			point a = convex[sz(convex) - 2];
			if (cross(vect(b,a),vect(b,c)) < -EPS)
				break;
			convex.pop_back();
		}
		if (i < sz(pnts))
			convex.push_back(pnts[i]);
	}
}

enum states {
	EXTERIOR, INTERIOR, BOUNDARY
};
int insidePolygon(vector<point> pol, point p) {
	int counter = 0, i, N = pol.size();
	double xinters;
	point p1, p2;
	p1 = pol[0];
	for (i = 1; i <= N; i++) {
		p2 = pol[i % N];
		if (p.Y > min(p1.Y, p2.Y)) {
			if (p.Y <= max(p1.Y, p2.Y)) {
				if (p.X <= max(p1.X, p2.X)) {
					if (p1.Y != p2.Y) {
						xinters = (p.Y - p1.Y) * (p2.X - p1.X)
								/ (p2.Y - p1.Y)+ p1.X;
						if (p1.X == p2.X || p.X <= xinters)
							counter++;
					}
				}
			}
		}
		if (pointSegmentDistance(p1, p2, p) == 0)
			return 2; //point on segment
		p1 = p2;
	}
	if (counter % 2)
		return 1;
	else
		return 0;
}

double polygonArea(vector<point> pol) {
	double res = 0;
	pol.push_back(pol[0]);
	for (int i = 0; i < (int) pol.size() - 1; i++) {
		res += cross(pol[i], pol[i + 1]);
	}
	return res / 2;
}

// if points are given in anti clockwise -> res will be positive else negative
// TAKE CARE this function fails if polygon intersects with itself
// return the centroid point of the polygon
// The centroid is also known as the "centre of gravity" or the "center of
// mass". The position of the centroid assuming the polygon to be made of
// a material of uniform density.
point polygin_centroid(vector<point> &poly) {
	point res(0, 0);
	double a = 0;
	for (int i = 0; i < sz(poly); i++) {
		int j = (i + 1) % sz(poly);
		res.X += (poly[i].X + poly[j].X)
				* (poly[i].X * poly[j].Y - poly[j].X * poly[i].Y);
		res.Y += (poly[i].Y + poly[j].Y)
				* (poly[i].X * poly[j].Y - poly[j].X * poly[i].Y);
		a += poly[i].X * poly[j].Y - poly[i].Y * poly[j].X;
	}
	a *= 0.5;
	res.X /= 6 * a;
	res.Y /= 6 * a;
	return res;
}
