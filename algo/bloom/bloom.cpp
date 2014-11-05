#include <unordered_set>
#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <random>
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
typedef unsigned u32;

// random_device device;
mt19937 mt((random_device())());

u32 hash_values[100][100];
u32 hash_shifts[100] = {3, 4, 17};

void init_hash_values() {
    forn(k, 100) {
        forn(i, 100) {
            hash_values[k][i] = mt();
        }
    }
}

u32 mhash(u32 x, int k) {
    u32 res = hash_values[k][0];
    res ^= (x*hash_values[k][1]) << 3;
    res ^= (x*hash_values[k][2]) >> 4;
    res ^= (x*hash_values[k][3]) << 17;
    res ^= (x*hash_values[k][4]) << 17;
    return res;
}

double random_test(vector<u32> a) {
    auto onebit = [](u32 x, int i) -> int {
        return 0 != (x&(1u<<i));
    };
    auto twobits = [](u32 x, int i, int j) -> int {
        return 2 * (0 != (x&(1u<<i))) + (0 != (x&(1u<<j)));
    };
    auto sqr = [](double x) { return x * x; };

    int n = a.size();

    int cnt[4];
    double s = 0;
    forn(i, 32) {
        forn(k, 2) cnt[k] = 0;
        for (auto x : a) {
            ++cnt[onebit(x, i)];
        }
        forn(k, 2) {
            s += sqr((double)cnt[k] / n - 0.5);
        }
    }
    forn(i, 32) forn(j, i) {
        forn(k, 4) cnt[k] = 0;
        for (auto x : a) {
            ++cnt[twobits(x, i, j)];
        }
        forn(k, 4) {
            s += sqr((double)cnt[k] / n - 0.25);
        }
    }
    return s;
}

struct bloom_filter {
    int n, k;
    int *a;
    bloom_filter(int n, int k) : n(n), k(k), a(new int[n]) {}

    void add(u32 x) {
        forn(i, k) {
            u32 h = mhash(x, i);
            a[(h>>5)%n] |= 1u<<(h&31);
        }
    }

    bool get(u32 x) {
        forn(i, k) {
            u32 h = mhash(x, i);
            if (0 == (a[(h>>5)%n] & (1u<<(h&31)))) {
                return false;
            }
        }
        return true;
    }
};

double test_bloom_filter(int n_elements, int n_queries, int filter_size, int n_functions) {
    bloom_filter a(filter_size/32, n_functions);
    unordered_set<u32> b;

    forn(i, n_elements) {
        u32 x = mt();
//         cout << "add " << x << endl;
        a.add(x);
        b.insert(x);
    }
    int fp = 0;
    forn(i, n_queries) {
        u32 x = mt();
//         cout << "check " << x << endl;
        if (b.count(x)) {
            assert(a.get(x));
        } else {
            if (a.get(x)) {
                ++fp;
//                 cout << "fp" << endl;
            }
        }
    }
    cerr << "num = " << fp << endl;
    return (double)fp / n_queries;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    init_hash_values();

    while (1) {
        int n_elements, n_queries, filter_size, n_functions;
        if (!(cin >> n_elements >> n_queries >> filter_size >> n_functions)) {
            break;
        }
        cout << test_bloom_filter(n_elements, n_queries, filter_size, n_functions) << endl;
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
