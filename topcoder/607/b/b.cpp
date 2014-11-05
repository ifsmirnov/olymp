#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define fore(i, b, e) for (int i = (int)(b); i <= (int)(e); ++i)

const int maxn = 2510;

int n;
int d[maxn][maxn][10];
int pr[maxn][10]; // last occurence of d before (inclusive) i
int a[maxn];

inline int mabs(int x, int y) {
	x = (x+10) % 10;
	y = (y+10) % 10;
	if (x < y) swap(x, y); // x >= y
	return min(x-y, y+10-x);
}

int solve() {
	forn(i, 10) {
		forn(j, 10) pr[i][j] = i == 0 ? -1 : pr[i-1][j];
		pr[i][a[i]] = i;
	}
	forn(i, n) cout << a[i] << " "; cout << endl;
	fore(len, 1, n) {
		forn(i, n-len+1) {
			int j = i+len-1;
			forn(s, 10) {
				if (len == 1) {
					d[i][j][s] = mabs(a[i] - s, 0);
				} else {
					d[i][j][s] = 30000;
					{ // j
					int move = (a[j] - s + 10) % 10;
					int cost = min(move, 10-move);
					d[i][j][s] = min(d[i][j-1][s], d[i][j-1][(s+move)%10]) + cost;
					}
					{ // i
					int move = (a[i] - s + 10) % 10;
					int cost = min(move, 10-move);
					d[i][j][s] = min(d[i][j][s], min(d[i+1][j][s], d[i+1][j][(s+move)%10]) + cost);
					}
				}
				cout << i << " " << j << " " << s << ": " << d[i][j][s] << endl;
			}
		}
	}
	return d[0][n-1][0];
	return 0;
}

class CombinationLockDiv1 {
public: int minimumMoves(vector<string> A, vector<string> B) {
	string S, T;
    cin >> S >> T;
// 	forn(i, A.size()) S += A[i];
// 	forn(i, B.size()) T += B[i];
	n = S.length();
	forn(i, n) a[i] = (S[i]-T[i]+10)%10;
	return solve();
}
};

int main() {
    freopen("input.txt", "r", stdin);
    CombinationLockDiv1 lock;
    cout << lock.minimumMoves(vector<string>(), vector<string>()) << endl;
}
