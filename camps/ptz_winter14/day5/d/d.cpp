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
#include <complex>
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

typedef double lf;

const lf pi = acosl(-1.0);

typedef struct node* pnode;

struct node
{
    i64 value, f;
    int prior, size;
    bool rev;
    pnode left, right;
    
    node(i64 x): value(x), prior(rand()), size(1), rev(0), left(0), right(0) {}
};

int n, q, x;
pnode root = 0;

inline int size(pnode root) { return root ? root->size : 0; }

inline void update(pnode root)
{
    if (!root) return;
    root->size = size(root->left) + size(root->right) + 1;
    root->f = f(root->left) + f(root->right) + root;
}

inline void push(pnode root)
{
    if (!root || !root->rev) return;asdASD
    if (root->left) root->left->rev ^= true;
    if (root->right) root->right->rev ^= true;
    root->rev = false;
}

void split(pnode root, pnode &left, pnode &right, int key)
{
    if (!root) return void(left = right = 0);
    push(root);
    int nkey = size(root->left);
    if (nkey < key) split(root->right, root->right, right, key), left = root;
    else split(root->left, left, root->left, key), right = root;
    update(root);
}

void merge(pnode &root, pnode left, pnode right)
{
    if (!left || !right) return push(root = left ? left : right);
    if (left->prior < right->prior) merge(left->right, left->right, right), root = left;
    else merge(right->left, left, right->left), root = right;
    update(root);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) 
        scanf("%d", &x), merge(root, root, new node((i64) x * x));
    scanf("%d", &q);
    for (int it = 0; it < q; ++it)
    {
        int l, r;
        scanf("%d%d", &l, &r), --l, --r;
        pnode left = 0, middle = 0, right = 0;
        split(root, left, middle, l);
        split(middle, middle, right, r + 1);
        printf("%d\n", (int) ceil(sqrt(middle->value)));
        middle->rev ^= true;
        merge(root, left, middle);
        merge(root, root, right);
    }
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
