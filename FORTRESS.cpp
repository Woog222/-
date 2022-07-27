#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#define el '\n'
using namespace std;
typedef vector<int> vi;

struct fortress {
    int x, y, r;
    fortress(int _x=0, int _y=0, int _z = 0) :
        x(_x), y(_y), r(_z) {}
};

int N;
vector<fortress> a;
vi adj[100];
int dist[100];

bool include(int i, int j);
void makeTree();
void dfs(int here, int d);
void Init();
int diameter();
int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    int t;  cin >> t;
    while (t--) {
        Init();
        makeTree();
        cout << diameter() << el;;
    }

}

int diameter()
{
    memset(dist, -1, sizeof(dist));
    dfs(0, 0);

    int start = 0;
    for (int i = 0; i < N; ++i) {
        if (dist[i] > dist[start]) {
            start = i;
        }
    }
    memset(dist, -1, sizeof(dist));
    dfs(start, 0);
    return *max_element(dist, dist + N);
}

void Init()
{
    cin >> N;
    a.clear();
    for (int i = 0; i < N; ++i) adj[i].clear();

    for (int i = 0; i < N; ++i) {
        int x, y, r; cin >> x >> y >> r;
        a.emplace_back(x, y, r);
    }
}

void dfs(int here, int d) 
{
    dist[here] = d;
    for (int next : adj[here]) 
        if (dist[next] == -1)
            dfs(next, d + 1);
}

void makeTree()
{
    vector<bool> visit(N, false);
    queue<int> q;
    visit[0] = true;
    q.push(0);
    // bfs
    while (!q.empty())
    {
        int here = q.front(); q.pop();

        for (int i = 0; i < N; ++i) {
            if (visit[i] || !include(here, i)) continue;
            
            bool ok = true;
            for (int j = 0; j < N; ++j) {
                if (j == i || j == here) continue;
                if (include(here, j) && include(j, i)) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                q.push(i);
                visit[i] = true;
                adj[here].push_back(i);
                adj[i].push_back(here);
            }
        }
    }
}

inline int sqr(int n) {
    return n*n;
}

int sqrdist(int i, int j) {
    return sqr(a[i].x - a[j].x) + sqr(a[i].y - a[j].y);
}

bool include(int i, int j) {
    return  a[i].r > a[j].r && sqrdist(i,j) <= sqr(a[i].r - a[j].r);
}
