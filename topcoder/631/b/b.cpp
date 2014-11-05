#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define fore(i, b, e) for (int i = (int)(b); i <= (int)(e); ++i)
const int inf = 1e9+100500;
const int maxn = 1010;
typedef long long i64;

int n, k;
int mtime;
int pos[maxn], cnt[maxn];
int d[maxn][maxn];

void relax(int &x, int y) {
	if (x > y) x = y;
}

int solve() {
	forn(i, maxn) forn(j, maxn) d[i][j] = inf;
	d[0][0] = -inf;
	forn(i, n) fore(k, 0, i) if (d[i][k] < inf) {
		cout << i << " " << k << ": " << d[i][k] << endl;
		{
			int l = d[i][k] + 1;
			l = max(l, pos[i] - mtime);
			int r = l + cnt[i] - 1;
			if (pos[i] - l <= mtime && r - pos[i] <= mtime) {
				relax(d[i+1][k], r);
			}
		}
		{
			for (int b = i; b < n; ++b) {
				int l = max(d[i][k] + 1, pos[b] - mtime);
				if (pos[b] - l > mtime || l - pos[i] > mtime) break;
				relax(d[b+1][k+1], l);
			}
		}
	}
	for (int k = 0; k <= n; ++k) if (d[n][k] < inf) return k;
	return -1;
}

class CatsOnTheLineDiv1 {
public: static int getNumber(vector<int> position, vector<int> count, int time) {
	n = position.size();
	mtime = time;
	vector<pair<int, int> > t(n);
	forn(i, n) t[i] = make_pair(position[i], count[i]);
	sort(t.begin(), t.end());
	forn(i, n) pos[i] = t[i].first, cnt[i] = t[i].second;
	return solve();
}
};

int main() {
    cout << CatsOnTheLineDiv1::getNumber({0, 2, 3}, {5, 3, 3}, 1) << endl;
}
