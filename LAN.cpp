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

double adj[500][500];

// get input, make adj
void make_graph(int v, int now)
{
    vi x(v),  y(v);
    for (int i = 0; i < v; ++i)
        cin >> x[i];
    for (int i = 0; i < v; ++i)
        cin >> y[i];

    // initializing by real distance
    for (int i = 0; i < v; ++i) {
        for (int j = 0; j < v; ++j) {

            double xd = x[i] - x[j];
            double yd = y[i] - y[j];
            double dist = sqrt(xd * xd + yd * yd);
            adj[i][j] = adj[j][i] = dist;
        }
    }

    // set dist to zero when already connected
    while (now--) {
        int a, b; cin >> a >> b;
        adj[a][b] = adj[b][a] = 0;
    }
}

double prim(int v)
{
    vector<double> dist(v, INF);
    vector<bool> included(v, false);
    // {cost, to}
    priority_queue< pair<double, int>, vector<pair<double, int>>, 
        greater<pair<double, int>>> pq;
    dist[0] = 0;
    pq.emplace(0, 0);

    double ret = 0;
    while (!pq.empty()) 
    {
        int here;
        double cost;
        tie(cost, here) = pq.top(); pq.pop();

        if (dist[here] < cost) continue;

        // valid, install!
        included[here] = true;
        ret += cost;

        for (int next = 0; next < v; ++next) 
        {
            if (included[next]) continue;

            if (dist[next] > adj[here][next]) {
                dist[next] = adj[here][next];
                pq.emplace(adj[here][next], next);
            }
        }
    }
    
    return ret;
}


int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    int t; cin >> t;
    while (t--) {
        int v, now;
        cin >> v >> now;
        make_graph(v, now);
        cout << fixed;
        cout.precision(10);
        cout << prim(v) << '\n';
    }

}
