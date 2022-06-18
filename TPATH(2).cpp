#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <cstring>
#include <cmath>
#include <iomanip>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 987654321;
// Union Find (no need to implement rank, fast enough)
struct UF
{
    vi parent;

    UF (int _v) 
    {
        parent.resize(_v);
        for (int i = 0; i < _v; ++i)
            parent[i] = i;
    }

    int FIND(int a) {
        if (parent[a] == a)
            return a;
        else
            return parent[a] = FIND(parent[a]);
    }

    void UNION(int a, int b) {
        int pa = FIND(a);
        int pb = FIND(b);
        parent[pb] = pa;
    }
};

int v, e;


// get input, make adj
void make_graph(vector<pair<int ,pii>> &edges)
{
    for (int i = 0; i < e; ++i) {
        int a, b, speed;
        cin >> a >> b >> speed;
        edges[i] = make_pair(speed, make_pair(a, b));
    }

    sort(edges.begin(), edges.end());
}
//using kruskal
int lower_upper(const vector<pair<int, pii>>& edges, int lower)
{
    UF uf(v);

    for (int i = 0; i < edges.size(); ++i)
    {
        if (edges[i].first < lower) continue;

        int a = edges[i].second.first;
        int b = edges[i].second.second;
        if (uf.FIND(a) != uf.FIND(b))
            uf.UNION(a, b);

        if (uf.FIND(0) == uf.FIND(v - 1))
            return edges[i].first;
    }
    // FAIL TO CONNECT;
    return INF;
}

// using kruskal
int scan( const vector<pair<int, pii>>& edges)
{
    int ret = INF;
    for (int i = 0; i < edges.size(); ++i) {
        int lower = edges[i].first;
        int upper = lower_upper(edges, lower);

        // 이 lower로는 도달이 불가능함
        if (upper == INF) break;

        ret = min(ret, upper - lower);
    }

    return ret;
}


int main()
{
    cin.tie(nullptr); cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    int t; cin >> t;
    while (t--) {
        cin >> v >> e;
        vector<pair<int ,pii>> edges(e);
        make_graph(edges);
        cout << scan(edges) << '\n';
    }

}
