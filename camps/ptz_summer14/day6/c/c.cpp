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

struct node {
    int sum;
    int val;
    int cnt;
    int prior;
    node * l, *r;
    
    node(int v) {
        val = v;
        sum = v;
        cnt = 1;
        prior = rand() * RAND_MAX + rand();
        l = r = 0;
    }
};

int getCnt(node * v) {
    return v ? v->cnt : 0;
}

int getSum(node * v) {
    return v ? v->sum : 0;
}

void update(node * v) {
    if (v) {
        v->cnt = 1 + getCnt(v->l) + getCnt(v->r);
        v->sum = v->val + getSum(v->l) + getSum(v->r);
    }
}

void split(node * v, node * &l, node * &r, int count) {
    if (!v) {
        return void(l = r = 0);
    }
    
    int cnt = getCnt(v->l);
    
    if (cnt >= count) {
        split(v->l, l, v->l, count);
        r = v;
    } else {
        split(v->r, v->r, r, count - cnt - 1);
        l = v;
    }
    update(l), update(r);
    
}

void merge(node * &v, node * l, node * r) {
    if (!l || !r) {
        v = l ? l : r;
        return;
    }
    if (l->prior > r->prior) {
        v = l;
        merge(l->r, l->r, r);
    } else {
        v = r;
        merge(r->l, l, r->l);
    }
    update(l), update(r);
}

const int M = 5;

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    
    int n;
    scanf("%d", &n);
    
    node * roots[M];
    for (int i = 0; i < M; ++i) {
        roots[i] = 0;
    }
    
    node * newRoots[M];
    
    for (int i = 0; i < M * n; ++i) {
        int val;
        scanf("%d", &val);
        merge(roots[i % M], roots[i % M], new node(val));
    }
    
    int q;
    scanf("%d", &q);
    
    char s[2];
    
    while (q--) {
        scanf("%s", s);
        if (s[0] == '?') {
            int l, r;
            scanf("%d%d", &l, &r);
            --l, --r;
            int res = 0;
            for (int i = 0; i < M; ++i) {
                int L = (l - i + 4) / M;
                int R;
                if (i > r) {
                    R = -1;
                } else {
                    R = (r - i) / M;
                }
                node *a, *b, *c;
                split(roots[i], a, b, L);
                split(b, b, c, R - L + 1);
                res += getSum(b);
                merge(b, b, c);
                merge(roots[i], a, b);
            }
            printf("%d\n", res);
        }
        if (s[0] == '<') {
            int shift;
            scanf("%d", &shift);
            for (int i = 0; i < M; ++i) {
                int R;
                if (shift - 1 < i) {
                    R = -1;
                } else {
                    R = (shift - 1 - i) / M;
                }
                node *a, *b;
                split(roots[i], a, b, R + 1);
                merge(roots[i], b, a);
            }
            int delta = shift % M;
            for (int i = 0; i < M; ++i) {
                newRoots[i] = roots[(i + delta) % M];
            }
            for (int i = 0; i < M; ++i) {
                roots[i] = newRoots[i];
            }
        }
        if (s[0] == '#') {
            int p[M];
            for (int i = 0; i < M; ++i) {
                scanf("%d", p + i);
                --p[i];
            }
            for (int i = 0; i < M; ++i) {
                newRoots[i] = roots[p[i]];
            }
            for (int i = 0; i < M; ++i) {
                roots[i] = newRoots[i];
            }
        }
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
