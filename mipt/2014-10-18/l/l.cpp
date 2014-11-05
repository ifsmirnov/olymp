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

const char * s1[] = {"Alice",
"Ariel", "Aurora", "Phil", "Peter", "Olaf",
"Phoebus", "Ralph", "Robin"};
const char * s2[] = {"Bambi", "Belle", "Bolt",
"Mulan", "Mowgli", "Mickey", "Silver", "Simba", "Stitch"};

int get(string s) {
    forn(i, 9) {
        if (s == s1[i]) return 1;
        if (s == s2[i]) return 2;
    }
    return 3;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif


    int n;
    int res = 0;
    int pos = 1;
    cin >> n;
    forn(i, n) {
        string s;
        cin >> s;
        int p = get(s);
        res += abs(p-pos);
        pos = p;
    }
    cout << res << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
