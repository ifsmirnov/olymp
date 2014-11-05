#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <functional>
#include <numeric>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <cstdlib>
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
const int maxn = 1005000;

char s[maxn];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int N;
    scanf("%d", &N);
    forn(i, N) {
        scanf("%s", s);
        int b = 0, minb = 0, maxb = 0;
        for (int j = 0; s[j]; ++j) {
            if (s[j] == '1') {
                ++b;
                maxb = max(maxb, b);
            } else {
                --b;
                minb = min(minb, b);
            }
        }
        
        multiset<int> s0, s1;
        for (int j = 0; s[j]; ++j) {
            if (s[j] == '0') {
                if (minb < 0) {
                    s1.insert(0);
                    ++minb;
                }
                int x = *s1.begin();
                s0.insert(x + 1);
                s1.erase(s1.begin());
            } else {
                if (maxb > 0) {
                    s0.insert(0);
                    --maxb;
                }
                int x = *s0.begin();
                s1.insert(x + 1);
                s0.erase(s0.begin());
            }
        }
        printf("%d %d\n", (int)(s0.size() + s1.size()), (int)max(s0.empty() ? 0 : *s0.rbegin(), s1.empty() ? 0 : *s1.rbegin()));
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
