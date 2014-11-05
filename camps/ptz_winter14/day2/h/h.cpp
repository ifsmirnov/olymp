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
const int maxn = 100500;

vi zfunction(const string &s) {
    vi z(s.size());
    z[0] = s.size();
    int l = 0, r = 0;
    for (int i = 1; i < s.size(); ++i) {
        if (i > r) {
            l = r = i;
        }
        z[i] = min(r - i, z[i - l]);
        while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) {
            ++z[i];
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

bool compare(const vi &z, const string &s, int st, int fin) {
    int l = min(z[st], fin - st);
    return l < fin - st && s[st + l] > s[l];
}

vi partite(const string &s, int K) {
    vi z = zfunction(s);
    vi ans;
    ans.pb(s.size());
    for (int i = s.size() - 1; i > 0; --i) {
        /*if (2 * i < ans.back()) {
            break;
        }*/
        if (!compare(z, s, i, ans.back())) {
            ans.pb(i);
        }
    }
    //cout << s << '\n';
    reverse(all(ans));
    //cout << s.substr(0, ans[0]) << ' ';
    /*forn(i, ans.size() - 1) {
        //cout << ans[i] << '\n';
        cout << s.substr(ans[i], ans[i + 1] - ans[i]) << ' ';
    }
    cout << '\n';*/
    if (ans.size() < K) {
        return vi();
    }
    if (ans.size() == K) {
        return ans;
    }
    for (int i = 0; i + 1 < ans.size() && i - K + 1 < -1; ++i) {
        if (z[ans[i]] < min(ans[i + 1] - ans[i], ans[0])) {
            ans.erase(ans.begin() + i + 1, ans.begin() + i + ans.size() - K + 1);
            return ans;
        }
    }
    return vi();
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    string s;
    int K;
    cin >> s;
    cin >> K;
    string bestPart = string(1, (char)('z' + 1));
    vi bestAns;
    int bestShift;
    forn(i, s.size()) {
        vi ans = partite(s, K);
        if (ans.size() == K) {
            string part = s.substr(0, ans[0]);
            if (part < bestPart) {
                bestPart = part;
                bestAns = ans;
                bestShift = i;
            }
        }
        s += s[0];
        s.erase(s.begin(), s.begin() + 1);
    }
    
    //assert(!bestAns.empty());
    forn(i, bestAns.size()) {
        bestAns[i] += bestShift;
        bestAns[i] %= s.size();
    }
    //cout << bestShift << '\n';
    sort(all(bestAns));
    forn(i, K) {
        cout << bestAns[i] + 1 << ' ';
    }
    cout << '\n';

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
