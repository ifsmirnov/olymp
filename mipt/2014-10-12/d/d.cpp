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

vector<pair<int, int> > all;
string s;
int n;
bool indent[10100];
vector<int> ans, st;

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("indent.in", "r", stdin);
    freopen("indent.out", "w", stdout);
#endif

    int test = 0;
    while (true)
    {
        test++;
        cin >> n;
        if (n == 0) break;
        all.resize(n);
        for (int i = 0; i < n; i++)
        {
            cin >> s; int tabs = 0, spaces = 0;
            int cur = 0;
            while (cur < s.length() && (s[cur] == '*' || s[cur] == '.'))
            {
                if (s[cur] == '*') tabs++;
                else spaces++;
                cur++;
            }
            if (s[s.length() - 1] == ':') indent[i] = true;
            else indent[i] = false;
            all[i].first = tabs, all[i].second = spaces;
        }
        cout << "Testcase #" << test << ":" << endl;
        if (indent[n - 1])
        {
            cout << "none" << endl << endl << endl;
            continue;
        }
        st.resize(1); st[0] = 0; ans.resize(0);
        for (int wid = 1; wid <= 64; wid++)
        {
            bool f = true;
            for (int i = 0; i < n; i++)
            {
                int cwid = all[i].first * wid + all[i].second;
                if (i > 0 && indent[i - 1])
                {
                    if (cwid <= st.back())
                    {
                        f = false;
                        break;
                    }
                    st.push_back(cwid);
                }
                else
                {
                    while (st.back() > cwid) st.pop_back();
                    if (cwid > st.back())
                    {
                        f = false;
                        break;
                    } 
                }
            }
            if (f) ans.push_back(wid);
        }
        if (ans.size() == 0)
        {
            cout << "none" << endl << endl << endl;
        }
        else if (ans.size() == 1)
        {
            cout << "unique" << endl << ans[0] << endl << endl;
        }
        else
        {
            cout << "multiple" << endl;
            for (int i = 0; i < (int)ans.size(); i++)
                cout << ans[i] << ' ';
            cout << endl << endl;
        }
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
