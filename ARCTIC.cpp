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

int N;
vector<pair<double, double>> loc; // input injected
double adj[100][100]; // reset at makeGraph

void makeGraph();
double fun();
int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    cout.tie(nullptr);

    cout << fixed;
    cout.precision(2);
    int t; cin >> t;
    while (t--)
    {
        cin >> N;
        
        loc.resize(N);
        for (int i = 0; i < N; ++i)
            cin >> loc[i].first >> loc[i].second;
        makeGraph();
        cout << fun() << '\n';
    }
}

void makeGraph()
{
    memset(adj, 0, sizeof(adj));
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            double xdiff = loc[i].first - loc[j].first;
            double ydiff = loc[i].second - loc[j].second;
            adj[i][j] = adj[j][i] = sqrt(xdiff * xdiff + ydiff * ydiff);
        }
    }
}

bool possible(double least)
{
    vector<bool> visited(N, false);
    queue<int>q;

    visited[0] = true;
    q.push(0);
    int cnt = 0;

    while (!q.empty()) {
        int here = q.front(); q.pop();
        cnt++;

        for (int next = 0; next < N; ++next) {
            if (visited[next] || adj[here][next] > least)
                continue;

            q.push(next);
            visited[next] = true;
        }
    }

    return cnt == N;
}
double fun()
{
    double ret = -1.0;
    double lo = 0.0, hi = sqrt(1000.0 * 1000.0 * 2.0);
    while ((hi - lo) >= 0.000000001)
    {
        double mid = (lo + hi) / 2;
        if (possible(mid)) {
            ret = mid;
            hi = mid;
        }
        else
            lo = mid;
    }

    return ret;
}

