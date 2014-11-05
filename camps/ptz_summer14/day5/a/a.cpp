#include <bits/stdc++.h>

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

const int N = 100000;

int t[N];

int get(int r) {
    int res = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) {
        res += t[r];
    }
    return res;
}

void add(int r, int val) {
    for (; r < N; r |= r + 1) {
        t[r] += val;
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    int n;
    int k;
    scanf("%d%d", &n, &k);
    
    int a[n];
    
    int b[n];
    
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        b[i] = a[i];
    }
    sort(b, b + n);
    int sz = unique(b, b + n) - b;
    
    long long iv = 0;
    
    for (int i = 0; i < n; ++i) {
        int pos = lower_bound(b, b + sz, a[i]) - b;
        int cnt = get(n - 1) - get(pos);
        iv += cnt;
        add(pos, 1);
    }
    
    iv = max(0ll, iv - k);
    
    cout << iv << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
