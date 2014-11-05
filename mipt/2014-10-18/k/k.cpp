#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <vector>
#include <ctime>
#include <queue>
#include <set>
#include <map>
#include <iomanip>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define fore(i, b, e) for (int i = (int)(b); i <= (int)(e); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long i64;
typedef unsigned long long u64;

#ifdef HOME
typedef double ftype;
#else
typedef long double ftype;
#endif
const double eps = 1e-10;

struct numSet
{
	vector<pair<ftype, ftype>> intervals;
	
	numSet leaveOnly(ftype x, bool more)
	{
		numSet result;
		for (auto i: intervals)
		{
			if (more)
			{
				if (i.second < x + eps) continue;
				i.first = max(i.first, x);
			}
			else
			{
				if (i.first > x - eps) continue;
				i.second = min(i.second, x);
			}
			
				
			result.intervals.push_back(i);
		}
		return result;
	}
	
	numSet leaveOnlyMore(ftype x)
	{
		return leaveOnly(x, true);
	}
	
	numSet leaveOnlyLess(ftype x)
	{
		return leaveOnly(x, false);
	}
	
	numSet intersect(const numSet& x)
	{
		numSet result;
		for (auto i: x.intervals)
		{
			numSet some = (*this).leaveOnlyMore(i.first).leaveOnlyLess(i.second);
			result = result.merge(some);
		}
		return result;
	}
	
	numSet merge(const numSet& x)
	{
		numSet result = *this;
		for (auto i: x.intervals)
			result.intervals.push_back(i);
		return result;
	}
	
	void print()
	{
		printf("{ ");
		for (auto it: intervals)
			printf("(%lg; %lg) ", it.first, it.second);
		printf("}\n");
	}
	
	bool contains(ftype x)
	{
		for (auto it: intervals)
			if (x > it.first + eps && x < it.second - eps)
				return true;
				
		return false;
	}
};

numSet makeInterval(ftype a, ftype b)
{
	//cout << a << " - " << b << endl;
	assert(a + eps < b);
	
	numSet result;
	result.intervals.push_back(make_pair(a, b));
	return result;
}

const ftype inf = 1e9;

struct quadratic
{
	// ax^2 + bx + c
	ftype a, b, c;
	
	quadratic(ftype a, ftype b, ftype c): a(a), b(b), c(c) {}
	
	quadratic(ftype x): a(0), b(0), c(x) {}
	
	quadratic(): a(0), b(0), c(0) {}
	
	void print()
	{
		if (fabsl(a) > eps)
			printf("%lg*x^2 + ", a);
		
		if (fabsl(b) > eps)
			printf("%lg*x + ", b);
			
		printf("%lg\n", c);
	}
	
	ftype eval(ftype x)
	{
		return a * x * x + b * x + c;
	}
	
	// get solutions of ... > 0
	numSet getSolutions()
	{
		vector<ftype> keyPoints;
		
		keyPoints.push_back(-inf);
		keyPoints.push_back(inf);
		
		assert(fabsl(a) > eps);
		
		ftype d = b * b - 4 * a * c;
		if (fabsl(d) < eps)
			keyPoints.push_back((-b) / (2 * a));
		else if (d > 0)
		{
			// order unknown, sort required
			keyPoints.push_back((-b - sqrtl(d)) / (2 * a));
			keyPoints.push_back((-b + sqrtl(d)) / (2 * a));
		}
		
		sort(keyPoints.begin(), keyPoints.end());
		
		numSet result;
		
		for (int i = 0; i < (int)keyPoints.size() - 1; i++)
			if (eval((keyPoints[i] + keyPoints[i + 1]) / 2) > 0)
				result.intervals.push_back(make_pair(keyPoints[i], keyPoints[i + 1]));
				
		return result;
	}
	
	quadratic operator+(quadratic q) const { return quadratic(a + q.a, b + q.b, c + q.c); }
	quadratic operator-(quadratic q) const { return (*this) + (q * (-1)); }
	
	ftype& getCoef(int id)
	{
		if (id == 0) return c;
		if (id == 1) return b;
		if (id == 2) return a;
		
		assert(!"impossible");
		return a;
	}
	
	quadratic operator/(quadratic q) const
	{
		quadratic result = *this;
		
		assert(fabsl(q.a) < eps);
		assert(fabsl(q.b) < eps);
		assert(fabsl(q.c) > eps);
		
		result.a /= q.c;
		result.b /= q.c;
		result.c /= q.c;
		
		return result;
	}
	
	quadratic operator*(quadratic q)
	{	
		//print();
		//printf(" x ");
		//q.print();
		//printf("\n");
		
		quadratic result;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (i + j < 3)
					result.getCoef(i + j) += getCoef(i) * q.getCoef(j);
				else
					assert(fabsl(getCoef(i) * q.getCoef(j)) < eps);
		return result;
	}
};

quadratic sqr(quadratic q)
{
	return q * q;
}

numSet valueBounded(quadratic q, ftype from, ftype to)
{
	// q > from
	// q < to  <=> to - q > 0
	
	quadratic one = (q - from);
	quadratic two = quadratic(to) - q;
	
	//one.getSolutions().print();
	//two.getSolutions().print();
	
	return one.getSolutions().intersect(two.getSolutions());
}

ftype middle(ftype a, ftype b)
{
	return (a + b) / 2;
}

void solve()
{
	quadratic x(0, 1, 0);
	
	/*
	
	quadratic one = (x - 2) * (x - 3);
	one.print(); printf("\n");
	one.getSolutions().print();
	printf("\n");
	
	quadratic two = (x + 2) * (x - 5) * (-1);
	one.getSolutions().intersect(two.getSolutions()).print();
	
	printf("\n");*/
	
	ftype L, h, l, d;
	cin >> L >> h >> l >> d;
	
	
	ftype vx, vy, ux, uy;
	cin >> vx >> vy >> ux >> uy;
	
	//cout << fixed << setprecision(6);
	//cout << L << " " << h << " " << l << " " << d << endl;
	//cout << vx << " " << vy << " " << ux << " " << uy << endl;
	
	ftype g = 10;
	
	quadratic y0 =
		(x - quadratic(ux * uy) / g) * vy / vx
		- quadratic(g) / (sqr(vx) * 2) * sqr(x - quadratic(ux * uy) / g)
		 + sqr(uy) / (quadratic(g) * 2);
		
	//y0.print();
		
	quadratic yl = y0 - (quadratic(g) / (sqr(ux) * 2)) * sqr(x - L);
	quadratic yr = y0 - (quadratic(g) / (sqr(ux) * 2)) * sqr(x - L - l);
	//printf("OK\n");
	
	//yl.getSolutions().print();
	//yr.getSolutions().print();
	
	numSet ylr = valueBounded(yl, h, h + d).intersect(valueBounded(yr, h, h + d));
	//cout << ux * uy / g << endl;
	
	numSet defArea = makeInterval(ux * uy / g, ux * uy / g + min(L, 2 * vx * vy / g));
	
	//defArea.print();
	
	ylr = ylr.intersect(defArea);
	
	//ylr.print();
	
	// find x that does not belong to (L; L+l)
	
	ftype xAnswer = -1;
	
	for (auto it: ylr.intervals)
	{
		vector<ftype> c;
		c.push_back(middle(it.first, L));
		c.push_back(middle(it.first, L));
		c.push_back(middle(it.second, L + l));
		c.push_back(middle(it.second, L + l));
		c.push_back(middle(it.first, it.second));
		
		for (auto xc: c)
			if (ylr.contains(xc) && !(xc > L + eps && xc < L + l - eps))
			{
				xAnswer = xc;
				goto breakAll;
			}
	}
	breakAll:
	
	// ...
	
	ylr = ylr.intersect(valueBounded(y0, h, h + d));
	
	if (!ylr.intervals.empty())
		xAnswer = ((ylr.intervals.back().first + ylr.intervals.back().second) / 2);
		
	if (xAnswer < 0)
	{
		printf("-1\n");
		return;
	}
		
	ftype answer = (xAnswer - ux * uy / g) / vx;
	cout << setprecision(12) << fixed << answer << endl;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
    
    for (int i = 0; i < 6; i++)
    {
#endif
	solve();

#ifdef HOME
	printf("\n\n");
	}
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
