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

int v, e;
// to, dist
vector<pii> adj[2000];
bool visit[2000];


void init()
{
    for (int i = 0; i < v; ++i) 
        adj[i].clear();
    
}
// get input, make adj
void make_graph(vi &edges)
{
    for (int i = 0; i < e; ++i) {
        int a, b, speed;
        cin >> a >> b >> speed;
        adj[a].emplace_back(b, speed);
        adj[b].emplace_back(a, speed);
        edges[i] = speed;
    }

    sort(edges.begin(), edges.end());
    edges.erase( unique(edges.begin(), edges.end()), edges.end());
}
// 0 -> v-1 possible with this boundary?
bool reach_bfs(int goal, int lower, int upper)
{
    memset(visit, false, sizeof(visit));
    queue<int> q;
    visit[0] = true;
    q.push(0);

    while (!q.empty())
    {
        int here = q.front(); q.pop();
        if (here == goal)
            return true;

        for (auto next : adj[here]){
            int there = next.first;
            int speed = next.second;
            if (!visit[there] && speed >= lower && speed <= upper)
                q.push(there);
        }
    }

    return false;
}

// two pointer scanning
int scan(const vi& edges)
{
    int lo = 0, hi = 0, size = edges.size();

    int ret = INF;
    while (lo <= hi && lo < size && hi < size)
    {
        if ( reach_bfs(v-1, edges[lo], edges[hi]) ) {
            ret = min(ret, edges[hi] - edges[lo]);
            lo++;
        }
        else
            hi++;
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
        init();
        // 간선가중치만 크기순대로 중복없이 정렬 (가능한 속도 모음)
        vi edges(e);
        make_graph(edges);
        cout << scan(edges) << '\n';
    }

}
