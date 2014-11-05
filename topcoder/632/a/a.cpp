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
inline int f(int x) { int cnt = 0; while (x%2==0) ++cnt, x /= 2; return cnt; }
bool ok(vector<int> a) {
    int mpos = max_element(a.begin(),a.end())-a.begin();
    int x = 1<<a[mpos];
    if (x <= mpos) return false;
    for (int i= 0; i < (int)a.size(); ++i) {
        if (f(x-mpos+i) != a[i]) return false;
    }
    return true;
}
class PotentialArithmeticSequence {
public: int numberOfSubsequences(vector<int> a) {
    int res = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        vector<int> b;
        for (int j = i; j < (int)a.size(); ++j) {
            b.push_back(a[j]);
            res += ok(b);
        }
    }
    return res;
}
};

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    PotentialArithmeticSequence a;
    cout << a.numberOfSubsequences({0,1,0,2,0,1,0}) << endl;


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
