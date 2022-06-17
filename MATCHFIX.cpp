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

int START = 0;
int DEST;
int V;

int win[13];
int cap[115][115];
int flow[115][115]; // reset before each net_flow
int parent[115]; // reset before each bfs

void add_edge(int from, int to, int c) {
    cap[from][to] += c;
}
void init()
{
    memset(cap, 0, sizeof(cap));
    // flow initailzed at net_flow
    // parent initialized at bfs
}
void make_graph(int n, int m)
{
    DEST = m + n + 1;
    for (int i = 1; i <= n; ++i) {
        cin >> win[i];
    }
        
    for (int i = 1; i <= m; ++i) {
        int a, b; cin >> a >> b;
        add_edge(START, n + i, 1);
        add_edge(n + i, a+1, 1);
        add_edge(n + i, b+1, 1);
    }
}
int cal_amt() // this case, just one..but practice!
{
    int amt = INF;
    int here = DEST;
    while (parent[here] != here)
    {
        amt = min(amt, cap[parent[here]][here] - flow[parent[here]][here]);
        here = parent[here];
    }

    return amt;
}
bool bfs() // true: success to get DIST, or false
{
    memset(parent, -1, sizeof(parent));
    queue<int> q;
    q.push(START);
    parent[START] = START;

    int amt = INF;
    while (!q.empty())
    {
        int here = q.front(); q.pop();

        for (int next = 0; next < V; ++next) {
            if (parent[next] != -1 || ( cap[here][next] - flow[here][next] )<= 0)
                continue;

            q.push(next);
            parent[next] = here;
        }
       
    }

    // fail to get dest
    if (parent[DEST] == -1)
        return false;
    else
        return true;
}
void send(int amt) 
{
    int here = DEST;
    while (parent[here] != here)
    {
        flow[parent[here]][here] += amt;
        flow[here][parent[here]] -= amt;
        here = parent[here];
    }
}
int net_flow()
{
    memset(flow, 0, sizeof(flow));
    int ret = 0;
    while (bfs())
    {
        // cal max possible amount
        int max_amount = cal_amt();
        send(max_amount);
        ret += max_amount;
    }

    return ret;
}
void graph_set(int n, int limit)
{

    cap[1][DEST] = limit - win[1];
    for (int i = 2; i <= n; ++i) {
        int temp = (limit - win[i] - 1);
        if (temp >= 0)
            cap[i][DEST] = temp;
        else
            cap[i][DEST] = 0;
    }
}
int can_win(int n ,int m)
{
    int ret = 0;
    for (int i = 1; i <= m; ++i) {
        if (cap[n + i][1] > 0)
            ret++;
    }
    return ret;
}

int main()
{
    cin.tie(nullptr); cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    int t; cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        V = n + m + 2;
        init(); // cap -> 0
        make_graph(n, m);

        // 하나도 안이김 ~ 이길 수 있는거 다이김
        // mid 번승리하고, 나머지는 최대 mid-1번만 승리하게 할 수 있는가?
        int lo = win[1];
        int hi = win[1] + can_win(n, m);
        int ans = INF;
        while (lo <= hi) 
        {
            int mid = (lo + hi) / 2;
            if (*max_element(win + 2, win + n + 1) >= mid) {
                lo = mid + 1;
                continue;
            }

            graph_set(n,mid);
            bool possible = (net_flow() == m);
            if (possible) {
                ans = min(ans, mid);
                hi = mid - 1;
            }
            else {
                lo = mid + 1;
            }
        }

        if (ans == INF)
            cout << -1 << '\n';
        else
            cout << ans << '\n';
    }
    

  
}
