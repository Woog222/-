#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <list>
#include <stack>
#include <assert.h>
#include <string>
#include <map>
#include <set>
#include <iterator>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
const int INF = 987654321;
const int MOD = 1000000007;

struct Edge {
    int to, weight;
};


int N;
int cache[32769][16];
vector<Edge> adj[16];
vector<string> words;

void init();
void makeGraph();
vi makeFail(const string& s);
int fun(int visited, int here);
string fun2(int visited, int here);
int main()
{
    int t; cin >> t;
    while (t--)
    {
        cin >> N;
        init();
        for (int i = 0; i < N; ++i)
            cin >> words[i];

        makeGraph();
        cout << fun2(0, 15) << '\n';
    }
}
// 0, 15(모두와 0으로 연결된 가상의 정점)
int fun(int visited, int here)
{
    if (visited == (1 << N) - 1)
        return 0;

    int& ret = cache[visited][here];
    if (ret != -1)
        return ret;

    ret = INF;
    for (Edge e : adj[here])
    {
        int next = e.to;
        if (visited & (1 << next))
            continue;

        ret = min(ret, fun(visited | (1 << next), next) + e.weight);

    }

    return ret;
}

string fun2(int visited, int here)
{
    if (visited == (1 << N) - 1)
        return "";

    // find next
    int nextVal = INF;
    int nextWord = 15;
    int cost = 100;
    for (Edge e : adj[here])
    {
        int next = e.to;
        if (visited & (1 << next))
            continue;

        if (fun(visited | (1 << next), next) + e.weight < nextVal) {
            nextVal = fun(visited | (1 << next), next) + e.weight;
            nextWord = next;
            cost = e.weight;
        }
    }

    assert(nextWord != 15);
    const string& temp = words[nextWord];

     return temp.substr(temp.size()-cost, cost) + fun2(visited | (1 << nextWord), nextWord);
}

vi makeFail(const string& s)
{
    int n = s.length();
    vi fail(n);

    int matched = 0;
    for (int i = 1; i < n; ++i) {
        while (matched > 0 && s[matched] != s[i]) matched = fail[matched-1];

        if (s[matched] == s[i])
            fail[i] = ++matched;
        else 
            fail[i] = 0;
    }


    return fail;
}

// a -> b
int cost(const string& a, const string& b)
{
    vi fail = makeFail(b);

    int n = a.size();
    int matched = 0;
    for (int i = 0; i < n; ++i) 
    {
        // matched: 숫자의이미로 이만큼 매칭됐따
        // 인덱스의 의미로 여기를 비교해야한다
        while (matched > 0 && a[i] != b[matched]) matched = fail[matched - 1];

        if (a[i] == b[matched]) {
            matched++;
            if (matched == b.size())
                return 0;
        }
    }

    return b.size() - matched;
}

void makeGraph()
{
    // 우선 중복제거
    while (true)
    {
        bool deleted = false;

        for (int i = 0; i < words.size(); ++i) {
            for (int j = 0; j < words.size(); ++j) {
                if (i == j) continue;
                if (cost(words[i], words[j]) == 0) {
                    words.erase(words.begin() + j);
                    deleted = true;
                    i = words.size();
                    break;
                }
            }
        }
        if (!deleted)
            break;
    }

    N = words.size();
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            adj[i].push_back(Edge{ j, cost(words[i], words[j]) });
            adj[j].push_back(Edge{ i, cost(words[j], words[i]) });
        }
    }

    // trick, 문자열 하나를 15번째 문자열에 추가해버리고 거기서시작
    for (int i = 0; i < N; ++i) {
        adj[15].push_back( Edge{ i, (int)words[i].length()} );
    }
}

void init()
{
    for (int i = 0; i <= 15; ++i)
        adj[i].clear();
    words.resize(N);
    memset(cache, -1, sizeof(cache));
}
