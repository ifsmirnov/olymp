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
#include <cmath>
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
const int inf = 1e9+100500;
#define op operator

typedef long double ld;

struct pt {
    ld x, y;
    pt(){}
    pt(ld x, ld y) : x(x), y(y) {}
    pt op+(const pt& p) const { return pt(x+p.x, y+p.y); }
    pt op-(const pt& p) const { return pt(x-p.x, y-p.y); }
    pt op*(const ld t ) const { return pt(x*t, y*t); }
    bool isok() const { return isfinite(x) && isfinite(y); }
    
    ld vprod(const pt& p) const { return x * p.y - y * p.x; }
    ld length() const { return sqrt(x * x + y * y); }
};

const ld eps = 1e-9;

pt getInter(pt a, pt va, pt b, pt vb)
{
	// a + va * t = b + vb * k
	// a * vb + va * vb * t = b * vb
	// (b - a) * vb = va * vb * t
	
	ld d = va.vprod(vb);
	if (abs(d) < eps) return pt(NAN, NAN);
	
	ld t = (b - a).vprod(vb) / d;
	
	if (t < -eps || t > 1 + eps) return pt(NAN, NAN);
	
	return a + va * t;
}

bool contains(vector<pt>& v, pt p)
{
	for (auto it: v)
		if (abs(it.x - p.x) < 1e-6 && abs(it.y - p.y) < 1e-6)
			return true;
	
	return false;
}

int sign(ld x)
{
	if (abs(x) < eps)
		return 0;
		
	if (x > 0)
		return 1;
	else
		return -1;
}

//pt a, b, c;
vector<pt> verts;
ld area, perimeter;

vector<pt> cutPts;

pair<ld, ld> getDareaDp(ld phi, ld d)
{
	pt vLine(cos(phi), sin(phi));
	pt vNorm(-vLine.y, vLine.x);
	
	pt base = vNorm * d;
	
	// line: base + vLine * t
	
	vector<pt> pts;
	for (int i = 0; i < 3; i++)
	{
		pt x = getInter(verts[i], verts[(i + 1) % 3] - verts[i], base, vLine);
		if (!x.isok()) continue;
		if (contains(pts, x)) continue;
		
		pts.push_back(x);
	}
	
	vector<int> vertSigns(3);
	for (int i = 0; i < 3; i++)
		vertSigns[i] = sign(vLine.vprod(verts[i] - base));
	
	int nonzeroSign = -2;
	for (int i = 0; i < 3; i++)
		if (vertSigns[i] != 0)
			nonzeroSign = vertSigns[i];
	assert(nonzeroSign == 1 || nonzeroSign == -1);
	
	ld dArea = 0, dP = 0;
	
	/*for (auto p: pts)
		printf("cutp %lf %lf\n", p.x, p.y);
	
	for (int i = 0; i < 3; i++)
		printf("%d ", vertSigns[i]);
	printf("\n");*/
	
	if ((int)pts.size() < 2)
	{
		for (int i = 0; i < 3; i++)
			if (vertSigns[i] != 0)
				assert(vertSigns[i] == nonzeroSign);
		
		dArea = area / 2 * nonzeroSign;
		dP = perimeter / 2 * nonzeroSign;
	}
	else
	{
		if (pts.size() != 2)
		{
			printf("\n");
			for (auto p: pts)
				printf("%Lf %Lf\n", p.x, p.y);
		}
		assert((int)pts.size() == 2);
		
		int uniqueSign = -2, uniqueV = -1;
		
		for (int i = 0; i < 3; i++)
		{
			if (vertSigns[i] == 0) continue;
			
			int count = 0;
			for (int j = 0; j < 3; j++)
				if (vertSigns[i] == vertSigns[j])
					count++;
					
			if (count != 1) continue;
			
			uniqueSign = vertSigns[i];
			uniqueV = i;
			break;
		}
		
		assert(uniqueSign == 1 || uniqueSign == -1);
		
		// partial
		ld pArea = (verts[uniqueV] - pts[0]).vprod(verts[uniqueV] - pts[1]);
		ld pP = (verts[uniqueV] - pts[0]).length() + (verts[uniqueV] - pts[1]).length();
		
		//printf("pArea %lf, pP %lf\n", pArea, pP);
		
		dArea = (abs(pArea) - area / 2) * uniqueSign;
		dP = (abs(pP) - perimeter / 2) * uniqueSign;
	}
	
	cutPts = pts;
	
	return make_pair(dArea, dP);
}

ld getDp(ld mPhi)
{
	ld minD = -3000, maxD = 3000;
	assert(sign(getDareaDp(mPhi, minD).first) * sign(getDareaDp(mPhi, maxD).first) == -1);
	
	for (int j = 0; j < 200; j++)
	{
		ld mD = (minD + maxD) / 2;
		
		pair<ld, ld> x = getDareaDp(mPhi, mD);
		if (sign(x.first) == 0)
		{
			minD = maxD = mD;
			break;
		}
		
		pair<ld, ld> y = getDareaDp(mPhi, minD);
		
		if (sign(y.first) * sign(x.first) == -1)
		{
			maxD = mD;
		}
		else
		{
			minD = mD;
		}
		
		//printf("%lf..%lf\n", minD, maxD);
	}
	
	ld ans = getDareaDp(mPhi, minD).second;
	//printf("phi %lf: dP %lf (dArea %lf)\n", mPhi, ans, getDareaDp(mPhi, minD).first);
	return ans;
}

void solve(ld la, ld lb, ld lc)
{
	verts.clear();
	verts.pb(pt(0, 0));
	verts.pb(pt(lc, 0));
	verts.pb(pt(la, lb));

	area = abs((verts[1] - verts[0]).vprod(verts[2] - verts[0]));
	perimeter = 0;
	for (int i = 0; i < 3; i++)
		perimeter += (verts[(i + 1) % 3] - verts[i]).length();

	//printf("2*area %lf perimeter %lf\n", area, perimeter);
	for (ld phi = 0; phi < M_PI; phi += M_PI / 10)
	{
		pair<ld, ld> x = getDareaDp(phi, 0);
		//printf("angle %lf, dArea %lf, dP %lf\n", phi, x.first, x.second);
	}
	
	ld answer = 0;
	
	ld minPhi = 0, maxPhi = M_PI;
	
	if (sign(getDp(minPhi)) == 0)
		answer = minPhi;
	else if (sign(getDp(maxPhi)) == 0)
		answer = maxPhi;
	else
	{
		assert(sign(getDp(minPhi)) != sign(getDp(maxPhi)));
		
		for (int i = 0; i < 200; i++)
		{
			ld mPhi = (minPhi + maxPhi) / 2;
			
			ld dP = getDp(mPhi);
			if (sign(dP) == 0)
			{
				minPhi = maxPhi = mPhi;
				break;
			}
			
			int t = sign(getDp(minPhi));
			if (sign(dP) * t == -1)
				maxPhi = mPhi;
			else
				minPhi = mPhi;
		}
		
		answer = minPhi;
	}
	
	//printf("found angle %Lf\n", answer);
	
	assert((int)cutPts.size() == 2);
	cout.precision(8);
	cout << fixed << cutPts[0].x << " " << cutPts[0].y << endl;
	cout << cutPts[1].x << " " << cutPts[1].y << endl;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	/*while (true)
	{
		solve(rand() % 2000 - 1000, rand() % 1000 + 1, rand() % 1000 + 1);
	}*/

	ld la, lb, lc;
	cin >> la >> lb >> lc;
	solve(la, lb, lc);
	
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
