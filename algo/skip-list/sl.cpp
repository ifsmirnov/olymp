#include <iostream>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <set>
#include <chrono>
using namespace std;

int nom = 1;
int den = 128;

struct Element {
    const static int MAX_LEVEL = 20;
    Element(int value, int level = -1) : value(value), level(level) {
        if (level == -1) {
            level = 0;
            while (level < MAX_LEVEL - 1) {
                if ((rand() & (den - 1)) < nom) ++level;
                else break;
            }
        }
        this->level = level;
        memset(next, 0, sizeof (Element*) * MAX_LEVEL);
    }

    static Element* firstElement() {
        return new Element(0x80000000, MAX_LEVEL - 1);
    }

    int value;
    int level;
    Element* next[MAX_LEVEL];
//     Element** next;
};

int cnt = 0;
int tms = 0;
Element* lower_bound(Element* t, int value, Element* lpos[] = NULL, Element* linker[] = NULL) {
    assert(t->level == Element::MAX_LEVEL - 1);
    int lvl = Element::MAX_LEVEL - 1;
    ++tms;
    while (1) {
        ++cnt;
        Element* cand = t->next[lvl];
        if (cand && cand->value < value) {
            t = cand;
        } else {
            if (lpos) {
                lpos[lvl] = cand;
                linker[lvl] = t;
            }
            if (lvl) {
                --lvl;
            } else {
                return t->next[0];
            }
        }
    }
    if (cnt > 20) cerr << "ewr" << endl;
    return t;
}

void insert(Element* begin, int value) {
    assert(begin->level == Element::MAX_LEVEL - 1);
    static Element* lpos[Element::MAX_LEVEL];
    static Element* linker[Element::MAX_LEVEL];
    Element* t = new Element(value);
    lower_bound(begin, value, lpos, linker);
    for (int i = 0; i <= t->level; ++i) {
        linker[i]->next[i] = t;
        t->next[i] = lpos[i];
    }
}

const int K = 1000000;
int r[K];
struct InitR { InitR() { for (int i = 0; i < K; ++i) r[i] = rand() % (K * 2); } } _;

void testSet() {
    set<int> a;
    a.insert(K);

    int s = 0;
    chrono::steady_clock::time_point timestamp = chrono::steady_clock::now();
    for (int i = 0; i < K; ++i) {
        int x = r[i];
        if (x&1) {
            a.insert(x>>1);
        } else {
            s += *a.lower_bound(x>>1);
        }
    }
    chrono::milliseconds delta = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - timestamp);
    cout << s << endl;
    cout << delta.count() << endl;
}

void testSkipList() {
    Element* a = Element::firstElement();
    insert(a, K);

    int s = 0;
    chrono::steady_clock::time_point timestamp = chrono::steady_clock::now();
    for (int i = 0; i < K; ++i) {
        int x = r[i];
        if (x&1) {
            insert(a, x>>1);
        } else {
            int p = lower_bound(a, x>>1)->value;
            s += p;
        }
    }
    chrono::milliseconds delta = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - timestamp);
//     cout << s << endl;
    cout << delta.count() << endl;
}

void test() {
    set<int> a;
    Element* t = Element::firstElement();
    a.insert(100000);
    insert(t, 100000);
    for (int i = 0; i < 100000; ++i) {
        int x = rand() % 100000;
        if (rand() % 2) {
            a.insert(x);
            insert(t, x);
        } else {
            if (lower_bound(t, x)->value != *a.lower_bound(x)) {
                cout << i << endl;
                return;
            }
        }
    }
    cout << "OK" << endl;
}

int main(int argc, char** argv) {
//     testSet();
    nom = atoi(argv[1]);
    testSkipList();
//     if (tms) {
//         cout << (double)cnt/tms << endl;
//     }

    return 0;
}
