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

const int maxn = 3000000;

char data[maxn + 1];
int n, t;
vector<int> vals, ops;

void pop_op()
{
    if (ops.back() == 0)
        vals.back() = vals.back() ^ 255;
    if (ops.back() == 1)
    {
        int x = vals.back();
        vals.pop_back();
        vals.back() &= x;
    }
    if (ops.back() == 2)
    {
        int x = vals.back();
        vals.pop_back();
        vals.back() |= x;
    }
    ops.pop_back();
}

int main() {
    ios_base::sync_with_stdio(false);
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("set-operations.in", "r", stdin);
    freopen("set-operations.out", "w", stdout);
#endif
    scanf("%s\n", data);
    n = strlen(data);

    int a = 170, b = 204, c = 240;
    for (int i = 0; i < n; ++i)
    {
        switch (data[i])
        {
            case 'A':
                vals.pb(a);
            break;
            case 'B':
                vals.pb(b);
            break;
            case 'C':
                vals.pb(c);
            break;
            case '~':
//                 while (ops.size() > 0 && ops.back() <= 0) pop_op();
                ops.pb(0);
            break;
            case '&':
                while (ops.size() > 0 && ops.back() <= 1) pop_op();
                ops.pb(1);
            break;
            case '|':
                while (ops.size() > 0 && ops.back() <= 2) pop_op();
                ops.pb(2);
            break;
            case '(':
                ops.pb(3);
            break;
            case ')':
                while (ops.back() != 3) pop_op();
                ops.pop_back();
            break;
        }
    }
    while (ops.size() > 0) pop_op();
    assert(vals.size() == 1);
    int expr = vals.back();

    scanf("%d%d", &n, &t);
    for (int tt = 0; tt < t; ++tt)
    {
        int vals[3] = {0, 0, 0};
        for (int it = 0; it < 3; ++it)
            for (;;)
            {
                int cur;
                scanf("%d", &cur);
                if (cur == 0) break;
                vals[it] |= 1 << (--cur);
            }
        for (int i = 0; i < n; ++i)
        {
            int bit = 0;
            for (int j = 2; j >= 0; --j)
                bit = (bit << 1) | ((vals[j] >> i) & 1);
            if ((expr >> bit) & 1)
                cout << i + 1 << " ";
        }
        cout << "0\n";
    }
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
