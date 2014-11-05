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

const int N = 1 << 16;
    
int r[N][2];

int shr[N];
int shl[N];
int sht[N];
int shb[N];

int mT[16];
int mB[16];
int mL[16];
int mR[16];

inline void rotate(int A, int B, int C, int D, int & aa, int & bb, int & cc, int & dd, int dir) {
    if (dir == 0) {
        bb = r[A][dir];
        dd = r[B][dir];
        cc = r[D][dir];
        aa = r[C][dir];
    } else {
        aa = r[B][dir];
        bb = r[D][dir];
        cc = r[A][dir];
        dd = r[C][dir];
    }
}

inline void shiftRight(int A, int B, int C, int D, int & aa, int &bb, int &cc, int &dd, int msk) {
    aa = shr[A] ^ mL[msk & 15];
    cc = shr[C] ^ mL[msk >> 4];
    bb = shr[B] ^ ((A & 0x1111) << 3);
    dd = shr[D] ^ ((C & 0x1111) << 3);
}

inline void shiftLeft(int A, int B, int C, int D, int & aa, int &bb, int &cc, int &dd, int msk) {
    aa = shl[A] ^ ((B & 0x8888) >> 3);
    cc = shl[C] ^ ((D & 0x8888) >> 3);
    bb = shl[B] ^ mR[msk & 15];
    dd = shl[D] ^ mR[msk >> 4];
}

inline void shiftBot(int A, int B, int C, int D, int & aa, int &bb, int &cc, int &dd, int msk) {
    aa = shb[A] ^ mT[msk & 15];
    cc = shb[C] ^ ((A & 15) << 12);
    bb = shb[B] ^ mT[msk >> 4];
    dd = shb[D] ^ ((B & 15) << 12);
}

inline void shiftTop(int A, int B, int C, int D, int & aa, int &bb, int &cc, int &dd, int msk) {
    aa = sht[A] ^ (C >> 12);
    cc = sht[C] ^ mB[msk & 15];
    bb = sht[B] ^ (D >> 12);
    dd = sht[D] ^ mB[msk >> 4];
}

int A[2], B[2], C[2], D[2];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("board-blitz.in", "r", stdin);
    freopen("board-blitz.out", "w", stdout);
#endif
    long long n, a, c, s;
    cin >> n >> a >> c >> s;

    
    for (int i = 0; i < 16; ++i) {
        int arr[4];
        for (int j = 0; j < 4; ++j) {
            arr[j] = (i >> j) & 1;
        }
        for (int j = 0; j < 4; ++j) { 
            mL[i] ^= (arr[j] << (15 - 4 * j));
            mR[i] ^= (arr[j] << (15 - 4 * j - 3));
            mT[i] ^= (arr[j] << (15 - j));
            mB[i] ^= (arr[j] << (15 - 12 - j));
        }
    }
    
    for (int i = 0; i < N; ++i) {
        int z[4][4];
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                z[j][k] = (i >> (15 - j * 4 - k)) & 1;
            }
        }
        r[i][0] = 0;
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                r[i][0] ^= (z[j][k] << (15 - k * 4 - (3 - j)));
            }
        }
        
        r[i][1] = 0;
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                r[i][1] ^= (z[j][k] << (15 - (3 - k) * 4 - j));
            }
        }
        for (int j = 1; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                sht[i] ^= (z[j][k] << (15 - (j - 1) * 4 - k));
            }
        }
        
        for (int j = 1; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                shb[i] ^= (z[j - 1][k] << (15 - j * 4 - k));
            }
        }
        
        for (int j = 0; j < 4; ++j) {
            for (int k = 1; k < 4; ++k) {
                shl[i] ^= (z[j][k] << (15 - j * 4 - (k - 1)));
            }
        }
        
        for (int j = 0; j < 4; ++j) {
            for (int k = 1; k < 4; ++k) {
                shr[i] ^= (z[j][k - 1] << (15 - j * 4 - (k)));
            }
        }
    }
    int aa, bb, cc, dd;
    for (int i = 0; i < n; ++i) {
        s = s * a + c;
        long long p = s / (1ll << 53);
        int sign = s < 0;
        int step = i & 1;
        if (sign) {
            rotate(A[step], B[step], C[step], D[step], aa, bb, cc, dd, step);
        } else {
            int mask = p & 255;
            int dir = (p >> 8) & 3;
            
            switch (dir) {
                case 0 : shiftTop(A[step], B[step], C[step], D[step], aa, bb, cc, dd, mask); break;
                case 1 : shiftLeft(A[step], B[step], C[step], D[step], aa, bb, cc, dd, mask); break;
                case 2 : shiftBot(A[step], B[step], C[step], D[step], aa, bb, cc, dd, mask); break;
                case 3 : shiftRight(A[step], B[step], C[step], D[step], aa, bb, cc, dd, mask); break;
            }
        }
        A[step ^ 1] &= ~aa;
        B[step ^ 1] &= ~bb;
        C[step ^ 1] &= ~cc;
        D[step ^ 1] &= ~dd;
        A[step] = aa;
        B[step] = bb;
        C[step] = cc;
        D[step] = dd;
    }
    char ans[8][9];
    memset(ans, 0, sizeof(ans));
    
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            ans[i][j] = '.';
        }
    }
    
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int bit = (A[0] >> (15 - i * 4 - j)) & 1;
            if (bit) {
                ans[i][j] = 'W';
            }
            bit = (B[0] >> (15 - i * 4 - j)) & 1;
            if (bit) {
                ans[i][j + 4] = 'W';
            }
            bit = (C[0] >> (15 - i * 4 - j)) & 1;
            if (bit) {
                ans[i + 4][j] = 'W';
            }
            bit = (D[0] >> (15 - i * 4 - j)) & 1;
            if (bit) {
                ans[i + 4][j + 4] = 'W';
            }
        }
    }
    
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int bit = (A[1] >> (15 - i * 4 - j)) & 1;
            if (bit) {
                ans[i][j] = 'B';
            }
            bit = (B[1] >> (15 - i * 4 - j)) & 1;
            if (bit) {
                ans[i][j + 4] = 'B';
            }
            bit = (C[1] >> (15 - i * 4 - j)) & 1;
            if (bit) {
                ans[i + 4][j] = 'B';
            }
            bit = (D[1] >> (15 - i * 4 - j)) & 1;
            if (bit) {
                ans[i + 4][j + 4] = 'B';
            }
        }
    }
    
    for (int i = 0; i < 8; ++i) {
        puts(ans[i]);
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
 
