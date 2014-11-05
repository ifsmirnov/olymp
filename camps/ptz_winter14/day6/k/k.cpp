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

typedef int real_int;
#define int i64

int n;
int fc, ft;
vector <pair <i64, int> > d;
vector <int> job[2];
vector <int> res;
int a[2][300000];

real_int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    ios::sync_with_stdio(false);

    cin >> n >> fc >> ft;
    for (int i = 0; i < n; ++i) {
        int x, y;
        i64 t;
        cin >> a[1][i] >> a[0][i] >> t;
        d.push_back(make_pair(t, i));
    }
    
    sort(d.begin(), d.end());
    i64 curtime = d[d.size() - 1].first;
    
    int curd = d.size() - 1;
    
    int type = 0;
    
    while (1) {
        //cout << curtime << endl;
        //cout << curd << endl;
        //cout << "!!\n";
        while (curd >= 0 && curtime <= d[curd].first) {
            job[0].push_back(d[curd].second);
            --curd;
        }
        if (job[type].size()) {
            if (type) {
                res.push_back(-job[type][0] - 1);
            }
            else {
                res.push_back(job[type][0] + 1);
            }
            curtime -= i64(a[type][job[type][0]]);
            if (!type) {
                job[1].push_back(job[0][0]);
            }
            swap(job[type][0], job[type][job[type].size() - 1]);
            job[type].pop_back();
        }
        else {
            if (curd == -1 && !job[1].size() && !job[0].size()) {
                break;
            }
            
            if (type) {
                type = 0;
                //curtime -= ft;
            }
            else {
                if (!job[1].size() && curd != -1) {
                    curtime = d[curd].first;
                    continue;
                }
                
                if (job[1].size() && curd == -1) {
                    curtime -= fc+ft;
                    type = 1;
                    continue;
                }
                
                if (job[1].size() && fc + ft < curtime - d[curd].first) {
                    type = 1;
                    curtime -= fc+ft;
                }
                else {
                    curtime = d[curd].first;
                }
                
            }
        }
    }
    
    //curtime -= ft;
    
    if (curtime >= 0) {
        cout << 0 << "\n";
    }
    else {
        cout << -curtime << "\n";
    }
    for (int i = res.size() - 1; i >= 0; --i) {
        cout << res[i] << " ";
    }
    cout << "\n";
    
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
