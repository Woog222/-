#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <cstring>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 987654321;

int delay[501]; //1 ~ v
int dist[501][501];
int max_delay[501][501];


// get input, make graph
void make_graph(int v, int e)
{
    for (int i = 1; i <= v; ++i) {
        cin >> delay[i];
    }
    //init
    for (int i = 1; i <= v; ++i)
        for (int j = 1; j <= v; ++j)
            dist[i][j] = INF;
    for (int i = 1; i <= v; ++i)
        dist[i][i] = 0;
    //modeling
    for (int i = 1; i <= e; ++i) {
        int a, b, d;
        cin >> a >> b >> d;
        dist[a][b] = d;
        dist[b][a] = d;
    }
}
int cal_delay(int i, int k, int j) 
{
    int res = max(max_delay[i][k], delay[k]);
    res = max(res, max_delay[k][j]);
    return res;
}
void fw(int v) 
{
    for (int k = 1; k <= v; ++k) {
        for (int i = 1; i <= v; ++i) {
            for (int j = 1; j <= v; ++j) {
                if (dist[i][k] == INF || dist[k][j] == INF) continue;
                if (k == i || k == j || i==j) continue;

                int worst_delay = cal_delay(i, k, j);
                int temp = dist[i][k] + dist[k][j] + worst_delay
                    - max_delay[i][k] - max_delay[k][j];
                if (temp < dist[i][j]) {
                    dist[i][j] = temp;
                    max_delay[i][j] = worst_delay;
                }                   
            }
        }
    }
}


int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int v, e;
    cin >> v >> e;
    make_graph(v, e);
    fw(v);
    
    
    int t; cin >> t;
    while (t--) {
        int a, b; cin >> a >> b;
        cout << dist[a][b] << '\n';
    }


}
