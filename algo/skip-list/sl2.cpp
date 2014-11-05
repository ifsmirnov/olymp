#include <iostream>
#include <cstdlib>
using namespace std;
const int maxn = 10000000;

int l[maxn], r[maxn], val[maxn], nxt[maxn], lvl[maxn];
int sz = 1, nsz = 0;

int nom = 1;
int den = 128;

int randomLevel() {
    while (level < MAX_LEVEL - 1) {
        if ((rand() & (den - 1)) < nom) ++level;
        else break;
    }
}

int newNode(int value, int level = -1) {
    if (l
    val[sz] = value;
    lvl[sz] = level;
    return sz++;
}
