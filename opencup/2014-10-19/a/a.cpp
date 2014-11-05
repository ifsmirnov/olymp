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
#include <cstring>
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

void solve(char* str)
{
	vector<string> words;
	
	int length = strlen(str);
	
	string word = "";
	
	for (int i = 0; i < length; i++)
	{
		if (!isalpha(str[i]))
		{
			if (!word.empty())
				words.push_back(word);
			word = "";
		}
		else
		{
			word += str[i];
		}
	}
	
	if (!word.empty())
		words.push_back(word);
		
	//for (auto it: words)
	//	printf("%s\n", it.c_str());
	
	set<string> colors = { "white", "blue", "red", "gray", "green" };
	set<string> names  = { "Barabashka", "book", "chair", "mouse", "bottle" };	
	
	set<string> notPresentColors = colors, notPresentNames = names;
	
	vector<string> pairFirst = { "white", "blue", "red", "gray", "green" };
	vector<string> pairSecond = { "Barabashka", "book", "chair", "mouse", "bottle" };
	
	string answer = "";
	
	for (int i = 0; i < (int)words.size() - 1; i++)
		if (colors.count(words[i]) && names.count(words[i + 1]))
		{
			if ((words[i] == "white" && words[i + 1] == "Barabashka") ||
				(words[i] == "blue" && words[i + 1] == "book") ||
				(words[i] == "red" && words[i + 1] == "chair") ||
				(words[i] == "gray" && words[i + 1] == "mouse") ||
				(words[i] == "green" && words[i + 1] == "bottle"))
			{
				assert(answer.empty());
				answer = string(words[i].c_str()) + " " + words[i + 1].c_str();
			}
			
			notPresentColors.erase(words[i]);
			notPresentNames.erase(words[i + 1]);
		}
		
	if (answer.empty())
	{
		for (int i = 0; i < 5; i++)
			if (notPresentColors.count(pairFirst[i]) && notPresentNames.count(pairSecond[i]))
			{
				assert(answer.empty());
				answer = pairFirst[i] + " " + pairSecond[i];
			}
	}
	
	assert(!answer.empty());
	printf("%s\n", answer.c_str());
}

int main() {
#ifdef HOME
    freopen("001", "r", stdin);
#else
	freopen("barabashka.in", "r", stdin);
	freopen("barabashka.out", "w", stdout);
#endif

	for (int i = 0; i < 5; i++)
	{
		char str[100];
		gets(str);
		solve(str);
	}

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
