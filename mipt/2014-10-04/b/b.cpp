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
    
    int n;
    scanf("%d", &n);
    
    vi vx, vy0, vy1;
    vi hy, hx0, hx1;
    
    for (int i = 0; i < n; i++)
    {
        int x0, y0, x1, y1;
        scanf("%d %d %d %d", &x0, &y0, &x1, &y1);
        
        if (x0 == x1)
        {
            vx.push_back(x0);
            vy0.push_back(min(y0, y1));
            vy1.push_back(max(y0, y1));
        }
        else
        {
            hy.push_back(y0);
            hx0.push_back(min(x0, x1));
            hx1.push_back(max(x1, x0));
        }
    }
    
    int answer = 0;
    
    for (int i = 0; i < (int)hy.size(); i++)
        for (int j = i + 1; j < (int)hy.size(); j++)
        {
            int nCut = 0;
            
            int x0 = max(hx0[i], hx0[j]);
            int x1 = min(hx1[i], hx1[j]);
            
            if (x1 <= x0) continue;
            
            int y0 = min(hy[i], hy[j]);
            int y1 = max(hy[i], hy[j]);
            
            for (int k = 0; k < (int)vx.size(); k++)
            {
                if (vx[k] < x0 || vx[k] > x1) continue;
                if (vy0[k] > y0 || vy1[k] < y1) continue;
                
                nCut++;
            }
            
            answer += nCut * (nCut - 1) / 2;
        }

    printf("%d\n", answer);

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
