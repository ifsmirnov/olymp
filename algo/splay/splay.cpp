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

struct Node {
    int val;
    Node *l, *r, *p;
    Node() {}
    Node(int val) : val(val), l(r=p=NULL) {}

    bool isRight() const { return c->p && c->p->r == c; }
    bool isLeft() const { return c->p && c->p->l == c; }
};

void rotateLeft(Node* c) {
    assert(c->isRight());
    Node *a = c->p;
    Node *d = c->l;

    c->p = a->p;
    a->p = c;
    d->p = a;
    c->l = a;
    a->r = d;
}
void rotateRight(Node* a) {
    assert(a->isLeft());
    Node *a = c->p;
    Node *d = c->r;

    c->p = a->p;
    a->p = c;
    d->p = a;
    c->r = a;
    a->l = d;
}
void expose(Node* t) {
    while (t->p) {
        if (t->isRight()) {
            rotateRight(t);
        } else {
            rotateLeft(t);
        }
    }
}

void print(Node* t) {
    if (t) {
        print(t->l);
        printf("%d ", t->val);
        print(t->r);
    }
}

void printCool(Node* t, int d = 0);

int main() {

void rotateLeft(Node* t) {
}
void rotateRight(Node* t) {
}
void expose(Node* t) {
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
