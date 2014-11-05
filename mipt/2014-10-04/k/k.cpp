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

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    string s;
    getline(cin, s);
    bool active = false; int last = -1, ans = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (!active)
        {
            if (s[i] == '(') last = i, active = true;
            else if (s[i] == ')') last = -1, ans++;
        }
        else
        {
            if (s[i] == '(') last = i, ans++;
            else if (s[i] == ')') last = -1, active = false;
            else if (('a' <= s[i] && s[i] <= 'z') || ('A' <= s[i] && s[i] <= 'Z') || s[i] == ' ') ;
            else last = -1, active = false, ans++;
        }
    }
    if (active) ans++;
    cout << ans << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
