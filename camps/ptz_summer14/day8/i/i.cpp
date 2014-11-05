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

const int N = 1000000;

int pos[N + 1];

int id[N + 1];


void move(int from, int to) {
    cout << "M " << from << " " << to << endl;
    int I = id[from];
    id[from] = 0;
    pos[I] = to;
    id[to] = I;
}

int counter = 0;

void alloc(int x) {
    cout << "A " << x << endl;
    int I = counter;
    pos[I] = x;
    id[x] = I;
}

void fr(int x) {
    int I = id[x];
    pos[I] = 0;
    id[x] = 0;
}

int main() {
#ifdef HOME
    //freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    
    int r3 = 0;
    
    int l2 = n + 1;
    
    int l1 = 0, r1 = -1;
    
    int query;
    
    while (cin >> query) {
        if (!query) {
            return 0;
        }
        ++counter;
        if (query == 3) {
            int it = 2;
            while (it > 0 && l1 <= r1 && r1 + 1 < l2) {
                move(l1, r1 + 1);
                ++l1, ++r1, --it;
            }
            alloc(r3 + 1);
            r3 += 3;
        }
        if (query == 2) {
            int it = 2;
            while (l1 <= r1 && l2 - r1 - 1 < 2) {
                move(r1, l1 - 1);
                --l1, --r1, --it;
            }
            assert(it >= 0);
            alloc(l2 - 2);
            l2 -= 2;
        }
        if (query == 1) {
            if (l1 <= r1) {
                if (l2 - r1 - 1 > 0) {
                    alloc(r1 + 1);
                    ++r1;
                } else {
                    alloc(l1 - 1);
                    --l1;
                }
            } else {
                alloc(l2 - 1);
                l1 = r1 = l2 - 1;
            }
        }
        if (query < 0) {
            int I = -query;
            int p = pos[I];
            
            if (p <= r3) {
                //3
                fr(p);
                if (p != r3 - 2) {
                    move(r3 - 2, p);
                }
                r3 -= 3;
            } else {
                if (p >= l2) {
                    fr(p);
                    if (p != l2) {
                        move(l2, p);
                    }
                    if (l1 <= r1) {
                        move(l1, r1 + 1);
                        ++l1, ++r1;
                    }
                    l2 += 2;
                } else {
                    fr(p);
                    if (p != l1) {
                        move(l1, p);
                    }
                    ++l1;
                }
            }
            cout << "D" << endl;
            
        }
        
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
