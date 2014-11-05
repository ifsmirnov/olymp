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

int d;
vector<int> answer;

void solve(int n, const vector<int>& add, const vector<int>& cut)
{
    for (int i = 0; i < d; i++)
    {
        //printf("%d %d\n", cut[i], n);
        assert(cut[i] >= 0 && cut[i] < (1 << n));
    }
    
    // side size 2^n
    
    // add central
    
    int halfSide = 1 << (n - 1);
    
    // minimal of whole cube
    for (int i = 0; i < d; i++)
        answer.push_back(add[i] + halfSide - 1);
    
    vector<int> cutVertex(d);
    // minimal of cut vertex
    for (int i = 0; i < d; i++)
    {
        int x = 0;
        if (cut[i] >= halfSide)
            x = halfSide;
        else
            x = halfSide - 1;
        
        cutVertex[i] = x;
        answer.push_back(add[i] + cutVertex[i]);
    }
    
    if (n == 1) return;
    
    // recursive calls
    for (int mask = 0; mask < (1 << d); mask++)
    {
        vector<int> realCut(d), nowCut(d), nowAdd(d);
        
        for (int i = 0; i < d; i++)
            if (mask & (1 << i))
            {
                realCut[i] = halfSide;
                
                nowCut[i] = 0;
                nowAdd[i] = add[i] + halfSide;
            }
            else
            {
                realCut[i] = halfSide - 1;
                
                nowCut[i] = halfSide - 1;
                nowAdd[i] = add[i];
            }
                
        if (realCut == cutVertex)
        {
            nowCut = cut;
            for (int i = 0; i < d; i++)
                nowCut[i] -= nowAdd[i] - add[i];
        }
        
        solve(n - 1, nowAdd, nowCut);
    }
    
    if (n == 1) return;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("packing.in", "r", stdin);
    freopen("packing.out", "w", stdout);
#endif

    #if 0
    for (int n = 2; n <= 24; n++)
        for (int td = 2; n * td < 24; td++)
        {
            d = td;
            vector<int> zero(d);
            printf("solving %dx%d\n", d, n);
            answer.clear();
            solve(n, zero, zero);
            printf("answer %d\n", (int)answer.size());
            assert(answer.size() % (2 * d) == 0);
    
        }
    #endif

    answer.clear();
    int n;
    scanf("%d %d", &d, &n);
        
    vector<int> zero(d);
    solve(n, zero, zero);

    assert(answer.size() % (2 * d) == 0);
    int nans = answer.size() / (2 * d);
    printf("%d\n", nans);
    if (1)
    {
        for (int i = 0; i < nans; i++)
        {
            for (int j = 0; j < 2 * d; j++)
                printf("%d ", answer[i * (2 * d) + j]);
            printf("\n");
        }
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
