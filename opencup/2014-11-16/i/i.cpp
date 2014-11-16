#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <ctime>
#include <queue>
#include <set>
#include <map>
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

const int MAXN = 200000;

int n, m, perm[MAXN];
vector<vector<int> > cycle, times;
bool used[MAXN];
pair<int, int> pos[MAXN];

struct MinRight {
    MinRight() {}
    MinRight(int n) : n(n) {
        sz = n;
        while (sz&(sz-1)) ++sz;
        a = new int[sz * 2];
        forn(i, sz * 2) a[i] = inf;
    }

    void upd(int i, int x) {
        i += sz;
        if (x) {
            a[i] = i-sz;
        } else {
            a[i] = inf;
        }
        for (i /= 2; i; i /= 2) {
            a[i] = min(a[i*2], a[i*2+1]);
        }
    }
    int get(int l, int r) {
        l += sz;
        r += sz;
        int mn = inf;
        while (l < r) {
            if (l%2 == 1) mn = min(mn, a[l]);
            if (r%2 == 0) mn = min(mn, a[r]);
            l = (l+1)/2;
            r = (r-1)/2;
        }
        if (l == r) {
            mn = min(mn, a[l]);
        }
        return mn;
    }
    int get(int s) {
        int t = get(s, n-1);
        if (t == inf) {
            assert(a[1] != inf);
            return a[1];
        } else {
            return t;
        }
    }
    int getval(int i) {
        return a[i+sz] != inf;
    }

    int *a;
    int sz;
    int n;
};

struct node {
    int l, r;
    node *L, *R;
    int s;
    bool inv;
    node(int l, int r) : l(l), r(r) {
        s = 0;
        inv = false;
        if (l == r) { L = R = NULL; }
        else {
            int m = (l+r)/2;
            L = new node(l, m);
            R = new node(m+1, r);
        }
    }
    int get() {
        if (inv) return r-l+1-s;
        else return s;
    }
    void norm() {
        if (inv) {
            s = (r-l+1) - s;
            if (L) {
                L->inv ^= 1;
                R->inv ^= 1;
            }
            inv = false;
        }
    }
    void upd() {
        assert(!inv);
        if (L) s = L->get() + R->get();
    }
    void inverse_internal(int lq, int rq) {
        if (lq <= l && rq >= r) {
            inv ^= 1;
        } else if (l > rq || r < lq) {
            ;
        } else {
            norm();
            L->inverse_internal(lq, rq);
            R->inverse_internal(lq, rq);
            upd();
        }
    }
    void inverse(int lq, int rq) {
        int n = r - l + 1;
        if (lq <= rq) {
            inverse_internal(lq, rq);
        } else {
            inverse_internal(lq, n-1);
            inverse_internal(0, r);
        }
    }
    int getsum(int lq, int rq) {
        if (lq <= l && rq >= r) {
            return get();
        } else if (l > rq || r < lq) {
            return 0;
        } else {
            norm();
            return L->getsum(lq, rq) + R->getsum(lq, rq);
        }
    }
};

vector<MinRight> treeFB;
vector<node*> treeSum;
vector<set<pair<int, int> > > begins;

int getShot(int num, int pos)
{
	return (treeSum[num]->getsum(pos, pos));
}

int nextShot(int num, int pos)
{
	return (treeFB[num].getval(pos) == 1 || getShot(num, pos) == 0 ? 1 : 0);
}

int init(int num)
{
	int len = cycle[num].size();
	treeFB.push_back(MinRight(len));
	treeSum.push_back(new node(0, len - 1));
// 	treeSum[(int)treeSum.size() - 1] = new node(0, len - 1);
	
	int least = 0;
	for (int i = 0; i < len; i++)
	{
		int next = (i + 1) % len;
		if (times[num][i] < times[num][next])
			treeFB.back().upd(i, 0);
		else
			treeFB.back().upd(i, 1);
		if (times[num][i] < times[num][least])
			least = i;
	}
	int cur = least;
	treeSum.back()->inverse(least, least);
	for (int i = 1; i < len; i++)
	{
		int nval = nextShot(num, cur);
		cur = (cur + 1) % len;
		if (nval)
			treeSum.back()->inverse(cur, cur);
	}
	return treeSum.back()->getsum(0, len - 1);
}

void printout(int num)
{
	cerr << "cerr " << num << endl;
	cerr << "cerr ";
	for (size_t i = 0; i < cycle[num].size(); i++)
		cerr << treeFB[num].getval(i);
	cerr << endl << "cerr ";
	for (size_t i = 0; i < cycle[num].size(); i++)
		cerr << getShot(num, i);
	cerr << endl;
}

int modify(int num, int pos, int val)
{
	printout(num);
	int least = begins[num].begin()->second, len = cycle[num].size();
	begins[num].erase(make_pair(times[num][pos], pos));
	int old = treeSum[num]->getsum(0, len - 1);
	int prev = (pos + len - 1) % len,
			next = (pos + 1) % len;
	if (times[num][next] > val)
		treeFB[num].upd(pos, 0);
	else
		treeFB[num].upd(pos, 1);
	if (times[num][prev] < val)
		treeFB[num].upd(prev, 0);
	else
		treeFB[num].upd(prev, 1);
	if (val > times[num][least] && pos != least)
	{	
		int nval = nextShot(num, prev);
		if (nval != getShot(num, pos))
			treeSum[num]->inverse(pos, pos);
		nval = nextShot(num, pos);
		if (nval != getShot(num, next))
		{
			int nearest = treeFB[num].get(next);
			treeSum[num]->inverse(next, nearest);
		}
	}
	else if (pos != least)
	{
		int nval = getShot(num, pos);
		if (nval != 1)
		{
			int nearest = treeFB[num].get(pos);
			treeSum[num]->inverse(next, nearest);
		}
	}
	else if (val > begins[num].begin()->first)
	{
		int nval = nextShot(num, prev);
		cerr << "cerr nval " << nval << endl;
		if (nval != getShot(num, pos))
			treeSum[num]->inverse(pos, pos);
		nval = nextShot(num, pos);
		if (nval != getShot(num, next))
		{
			int nearest = treeFB[num].get(next);
			treeSum[num]->inverse(next, nearest);
		}
	}
	printout(num);
	times[num][pos] = val;
	begins[num].insert(make_pair(times[num][pos], pos));
	return treeSum[num]->getsum(0, len - 1) - old;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &perm[i]); perm[i]--;
		used[i] = false;
	}

	for (int i = 0; i < n; i++)
	{
		if (used[i]) continue;
		cycle.resize(cycle.size() + 1);
		int cur = i;
		while (!used[cur])
		{
			cycle.back().push_back(cur);
			pos[cur] = make_pair((int)cycle.size() - 1, (int)cycle.back().size() - 1);
			used[cur] = true;
			cur = perm[cur];
		}
	}

	times.resize(cycle.size());
	for (int i = 0; i < (int)times.size(); i++)
		times[i].resize(cycle[i].size());
	for (int i = 0; i < n; i++)
		scanf("%d", &times[pos[i].first][pos[i].second]);

	int ans = 0;
	for (int i = 0; i < cycle.size(); i++)
		ans += init(i);
	printf("%d\n", n - ans);
	
	begins.resize(cycle.size());
	for (int i = 0; i < cycle.size(); i++)
		for (int j = 0; j < cycle[i].size(); j++)
			begins[i].insert(make_pair(times[i][j], j));

	scanf("%d", &m);
	for (int i = 0; i < m; i++)
	{
		int k, v; scanf("%d%d", &k, &v); k--;
		ans += modify(pos[k].first, pos[k].second, v);
		printf("%d\n", n - ans);
	}

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
