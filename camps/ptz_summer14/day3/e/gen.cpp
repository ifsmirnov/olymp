#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define fore(i, b, e) for (int i = (int)(b); i <= (int)(e); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
const int maxn = 1005;

int a[maxn][maxn];

int main(int argc, char* argv[]) {
    freopen("input.txt", "w", stdout);
    assert(argc > 2);
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);

    forn(i, n) forn(j, n) a[i][j] = (rand() % 10 < 3);
    printf("%d %d %d\n", n, n, k);
    forn(i, n) {
        forn(j, n) printf("%d", a[i][j]);
        printf("\n");
    }
    return 0;
}
