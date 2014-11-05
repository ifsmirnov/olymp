
#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <fstream>
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
const int maxn = 100500;

int main(int argc, char *argv[]) {
    assert(argc > 2);
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    if (argc > 3) srand(atoi(argv[3]));
    forn(i, n) cout << (char)(rand()%26+'a'); cout << endl;
    cout << k << " " << n << endl;
    int l, r;
    forn(i, n) {
        l = rand()%n+1;
        r = rand()%n+1;
        if (l>r) swap(l,r);
        if (rand()%2) {
            cout << 1 << " " << l << " " << r << " " << (char)('a'+rand()%26) << endl;
        } else {
            cout << 2 << " " << l << " " << r << endl;
        }
    }
}
