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

typedef double ftype;
ftype eps = 1e-8;

struct point
{
    ftype x;
    ftype v; // speed
    int add;
    
    bool operator<(const point&) const { return false; }
};

struct moving
{
    ftype from; // inclusive
    ftype to; // exclusive;
    
    int add;
};

bool haveCollisionTime(ftype& collisionTime, point& a, point& b)
{
    ftype dx = b.x - a.x;
    ftype dv = a.v - b.v;
    
    if (abs(dv) < eps) return false;
    
    ftype t = dx / dv;
    
    if (t < 0) return false;
    
    collisionTime = t;
    return true;
}

int xMax;

ftype getOffBoardTime(point p)
{
    if (p.v > 0)
        return (xMax - p.x) / p.v;
    else
        return p.x / -p.v;
}

bool solve()
{
    int n, height, modelTime;
    scanf("%d %d %d %d", &n, &xMax, &height, &modelTime);
    if (n == 0) return false;
    
    ftype tEffective = modelTime - sqrt(2 * height / 10000.0);
    //printf("t effective %lf\n", tEffective);
    
    vector<int> sourceX(n), sourceSpeed(n), sourceAdd(n), sourceStart(n), sourcePeriod(n);
    
    for (int i = 0; i < n; i++)
    {
        char sign;
        scanf("%d %d %d %d %d %c", &sourceX[i], &sourceSpeed[i], &sourceAdd[i], &sourcePeriod[i], &sourceStart[i], &sign);
        
        assert(sign == '+' || sign == '-');
        if (sign == '-')
            sourceSpeed[i] *= -1;
    }
    
    vector<pair<ftype, point>> newPoints;
    int newPointsNext = 0;
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; ; j++)
        {
            ftype t = sourceStart[i] + sourcePeriod[i] * j;
            if (t - eps > tEffective) break;
            
            //printf("add pt at %lf\n", t);
            
            newPoints.push_back(make_pair(t, point { (ftype)sourceX[i], (ftype)sourceSpeed[i], sourceAdd[i] }));
        }
    }
    
    sort(newPoints.begin(), newPoints.end());
    
    vector<point> currentPoints;
    
    ftype totalTimePassed = 0;
    
    // FIXME: край доски
    vector<moving> answer;
    
    int firstAdd = 0, lastAdd = 0;
    
    while (true)
    {
        /*#ifdef HOME
        printf("\n");
        printf("current time %lf of %lf\n", totalTimePassed, tEffective);
        for (auto it: currentPoints)
            printf("point %lf + %lf*t, add %d\n", it.x, it.v, it.add);
        #endif*/
        
        ftype nextEvent = tEffective - totalTimePassed;
        
        // find dt
        
        if (newPointsNext < (int)newPoints.size())
            nextEvent = min(nextEvent, newPoints[newPointsNext].first - totalTimePassed);
            
        for (int i = 0; i < (int)currentPoints.size() - 1; i++)
        {
            ftype collisionTime = 0;
            if (haveCollisionTime(collisionTime, currentPoints[i], currentPoints[i + 1]))
            {
                nextEvent = min(nextEvent, collisionTime);
            }
        }
        
        for (int i = 0; i < (int)currentPoints.size(); i++)
        {
            ftype t = getOffBoardTime(currentPoints[i]);
            nextEvent = min(nextEvent, t);
        }
        
        // process dt=nextEvent
        
        bool lastEvent = totalTimePassed + nextEvent > tEffective + eps;
        
        //printf("dt = %lf\n", nextEvent);
        
        vector<char> removePoint(currentPoints.size());
        
        vector<point> addPoints;
        
        while (newPointsNext < (int)newPoints.size() &&
                abs(newPoints[newPointsNext].first - totalTimePassed - nextEvent) < eps)
        {
            bool noAdd = false;
            
            for (int i = 0; i < (int)currentPoints.size(); i++)
                if (abs(currentPoints[i].x + currentPoints[i].v * nextEvent - newPoints[newPointsNext].second.x) < eps)
                {
                    noAdd = true;
                    removePoint[i] = true;
                }
                //else printf("delta %lf\n", abs(currentPoints[i].x + currentPoints[i].v * nextEvent - newPoints[newPointsNext].second.x));
                
            if (!noAdd && !lastEvent)
            {
                addPoints.push_back(newPoints[newPointsNext].second);
                newPointsNext++;
            }
            else
            {
                //printf("add & remove at same time\n");
                ftype x = newPoints[newPointsNext].second.x;
                answer.push_back(moving { x, x, newPoints[newPointsNext].second.add });
            }
        }
        
        for (int i = 0; i < (int)currentPoints.size() - 1; i++)
        {
            ftype collisionTime = 0;
            if (haveCollisionTime(collisionTime, currentPoints[i], currentPoints[i + 1]) &&
                abs(collisionTime - nextEvent) < eps)
            {
                removePoint[i] = true;
                removePoint[i + 1] = true;
                
                //printf("collsion event\n");
            }
        }
        
        for (int i = 0; i < (int)currentPoints.size(); i++)
        {
            if (abs(getOffBoardTime(currentPoints[i]) - nextEvent) < eps)
            {
                removePoint[i] = true;
                
                // FIXME: add to board end here
                
                if (currentPoints[i].v > 0)
                    lastAdd += currentPoints[i].add;
                else
                    firstAdd += currentPoints[i].add;
            }
        }
        
        for (int i = 0; i < (int)currentPoints.size(); i++)
        {
            ftype from = currentPoints[i].x;
            ftype to = from + currentPoints[i].v * nextEvent;
            answer.push_back(moving { from, to, currentPoints[i].add });
            currentPoints[i].x = to;
        }
        
        int addPtr = 0;
        
        vector<point> newPoints;
        for (int i = 0; i < (int)currentPoints.size(); i++)
        {
            if (removePoint[i]) continue;
            
            while (addPtr < (int)addPoints.size() && currentPoints[i].x >= addPoints[addPtr].x)
            {
                newPoints.push_back(addPoints[addPtr++]);
            }
            
            newPoints.push_back(currentPoints[i]);
        }
        
        while (addPtr < (int)addPoints.size())
            newPoints.push_back(addPoints[addPtr++]);
        
        currentPoints = newPoints;
        
        // break condition
        
        if (totalTimePassed > eps && abs(nextEvent) < eps) break;
        
        totalTimePassed += nextEvent;
    }
    
    assert(newPointsNext == (int)newPoints.size());
    
    /*printf("%d answer entries\n", (int)answer.size());
    for (auto it: answer)
        if (it.from < it.to)
            printf("[%lf %lf) += %d\n", it.from, it.to, it.add);
        else
            printf("(%lf %lf] += %d\n", it.to, it.from, it.add);
    */
    
    vector<ftype> answerNumbers;
    for (auto it: answer)
    {
        answerNumbers.push_back(it.to);
        answerNumbers.push_back(it.from);
    }
    answerNumbers.push_back(0);
    answerNumbers.push_back(xMax);
    
    vector<ftype> purgedNumbers;
    
    sort(answerNumbers.begin(), answerNumbers.end());
    
    for (int i = 0; i < (int)answerNumbers.size(); i++)
        if (i == 0 || answerNumbers[i] - answerNumbers[i - 1] > eps)
            purgedNumbers.push_back(answerNumbers[i]);
            
    answerNumbers = purgedNumbers;
    
    vector<int> sumAdd(2 * answerNumbers.size());
    
    for (auto it: answer)
    {
        int toNumber = lower_bound(answerNumbers.begin(), answerNumbers.end(), it.to - eps) - answerNumbers.begin();
        int fromNumber = lower_bound(answerNumbers.begin(), answerNumbers.end(), it.from - eps) - answerNumbers.begin();
        
        int toCell = toNumber * 2 + 1;
        int fromCell = fromNumber * 2 + 1;
        
        if (toCell > fromCell)
        {
            toCell--;
            fromCell--;
        }
        
        if (toCell == fromCell)
        {
            fromCell = fromNumber * 2;
        }
        
        {
            int x = min(toCell, fromCell);
            int y = max(toCell, fromCell);
            fromCell = x;
            toCell = y;
        }
        
        sumAdd[fromCell] += it.add;
        sumAdd[toCell] -= it.add;
    }
    
    sumAdd[0] += firstAdd;
    sumAdd[sumAdd.size() - 2] += lastAdd;
    
    static int testCase = 1;
    printf("Test case %d:\n", testCase);
    testCase++;
    
    int hlast = -1;
    ftype x0, x1;
    char c0, c1;
    
    int sum = 0;
    for (int i = 0; i < 2 * (int)answerNumbers.size() - 1; i++)
    {
        sum += sumAdd[i];
        
        ftype x0now = answerNumbers[i / 2];
        ftype x1now = answerNumbers[(i + 1) / 2];
        
        char c0now = i % 2 == 0 ? '[' : '(';
        char c1now = i % 2 == 0 ? ']' : ')';
        
        if (hlast == -1 || sum != hlast)
        {
            if (hlast != -1)
                printf("on %c%.12lf; %.12lf%c: height %d\n", c0, x0, x1, c1, hlast);
            
            hlast = sum;
            c0 = c0now;
            c1 = c1now;
            x0 = x0now;
            x1 = x1now;
        }
        else
        {
            c1 = c1now;
            x1 = x1now;
        }
    }
    
    if (hlast != -1)
        printf("on %c%.12lf; %.12lf%c: height %d\n", c0, x0, x1, c1, hlast);
    
    return true;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
    freopen("faucets.in", "r", stdin);
    freopen("faucets.out", "w", stdout);
#endif
    
    while (solve());

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
