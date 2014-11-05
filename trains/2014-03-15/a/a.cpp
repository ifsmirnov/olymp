#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <sstream>
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

typedef map<string, string> Entry;
typedef pair<string, string> Item;

string s;
size_t pos;

void skipws() {
    while (pos < s.length() && s[pos] == ' ') ++pos;
}

Item readItem() {
    skipws();
    if (s[pos] == '}') return Item();
    string name;
    while (isalpha(s[pos])) name += s[pos++];
    skipws();
    assert(s[pos++] == '=');
    skipws();
    assert(s[pos++] == '"');
    string val;
    while (s[pos] != '"') val += s[pos++];
    assert(s[pos++] == '"');
    skipws();
    if (s[pos] == ',') ++pos;
    return Item(name, val);
}

Entry readEntry() {
    skipws();

    if (pos == s.length()) return Entry();

    assert(s[pos] == '@');
    ++pos;
    string type = "";
    while (isalpha(s[pos])) type += s[pos++];

    Entry entry;

    skipws();
    assert(s[pos++] == '{');
    Item item;
    while (1) {
        item = readItem();
        if (item.fi.empty()) {
            assert(s[pos++] == '}');
            break;
        } else {
//             cerr << "Read item [" << item.fi << "] [" << item.se << "]" << endl;
            entry.insert(item);
        }
    }
    entry["type"] = type;
    return entry;
}

void readString() {
    string t;
    while (getline(cin, t)) {
        s += t;
    }
    forn(i, s.length()) if (s[i] == '\n') s[i] = ' ';
}

vector<vector<string> > parseAuthors(const string& s) {
    stringstream ss(s + " and -");
    vector<vector<string> > res;
    vector<string> cur;
    string t;
    while (1) {
        ss >> t;
        if (t == "and") {
            cur.insert(cur.begin(), cur.back());
            cur.pop_back();
            res.pb(cur);
            cur.clear();
        } else if (t == "-") {
            sort(all(res));
            return res;
        } else {
            cur.pb(t);
        }
    }
}

bool cmpn(const string& s, const string& t) {
    if (s.length() == t.length()) return s < t;
    return s.length() < t.length();
}

struct Book {
    static int cnt;
    Book(){}
    Book(const Entry& e) {
        title = e.at("title");
        assert(!title.empty());
        authors = parseAuthors(e.at("author"));
//         for (auto author: authors) {
//             for (auto name: author) {
//                 cout << name << " ";
//             }
//             cout << endl;
//         }
//         cout << endl;

//         cerr << "type = " << e.at("type") << endl;

        vals = e;
    }
    void print() const {
        cout << "[" << cnt++ << "] ";
        forn(i, authors.size()) {
            forn(j, authors[i].size()) {
                if (j == 0) {
                    cout << authors[i][0];
                } else {
                    cout << authors[i][j][0] << ".";
                }
                if (j+1 != (int)authors[i].size()) {
                    cout << " ";
                }
            }
            if (i + 1 != (int)authors.size()) {
                cout << ", ";
            } else {
                cout << " ";
            }
        }

        cout << title;

        if (vals.at("type") == "book") {
            if (vals.count("volume")) {
                cout << ", Vol. " << vals.at("volume");
            }
            cout << " -- " << vals.at("publisher") << ", " << vals.at("year");
        } else {
            cout << " // " << vals.at("journal");
            if (vals.count("volume")) {
                cout << ", " << vals.at("volume");
            }
            if (vals.count("number")) {
                cout << " (" << vals.at("number") << ")";
            }
            cout << " -- " << vals.at("year");
            if (vals.count("pages")) {
                string pages = vals.at("pages");
                if (count(all(pages), '-')) {
                    cout << " -- pp. " << pages;
                } else {
                    cout << " -- p. " << pages;
                }
            }
        }
        cout << endl;
    }
    bool operator<(const Book& o) const {
        if (authors != o.authors) return authors < o.authors;
        else if (title != o.title) return title < o.title;
        else return cmpn(vals.at("volume"), o.vals.at("volume"));
    }
    vector<vector<string> > authors;
    string title;
    map<string, string> vals;
};
int Book::cnt = 1;

vector<Book> es;


int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("bibtex.in", "r", stdin);
    freopen("bibtex.out", "w", stdout);

    readString();
    while (true) {
        Entry entry = readEntry();
        if (entry.empty()) {
            break;
        } else {
            es.pb(Book(entry));
        }
    }
    sort(all(es));
    forn(i, es.size()) {
        es[i].print();
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
