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


int dist[201][201];


void init(int v)
{
    for (int i = 0; i < v; ++i) {
        for (int j = 0; j < v; ++j) {
            if (i == j) dist[i][i] = 0;
            else dist[i][j] = INF;
        }
    }
}
// get input, make graph
void make_graph(int now)
{
    //modeling
    for (int i = 1; i <= now; ++i) {
        int a, b, d;
        cin >> a >> b >> d;

        // 역겹다 진짜 이거 안넣으면 틀림
        // 아니 미리 말해준것도 아니고 똑같은 도시 연결하는 고속도로가 두번들어오는걸
        // 푸는 사람 입장에서 가정해서 풀어야 되는거야?
        //if (d >= dist[a][b]) continue;

        dist[a][b] = d;
        dist[b][a] = d;
    }
}
int fw(int v, int soon) 
{
    // cal now..
    for (int k = 0; k < v; ++k) {
        for (int i = 0; i < v; ++i) {
            for (int j = 0; j < v; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // add
    int ret = 0;
    while (soon--) {
        int a, b, d; cin >> a >> b >> d;
        // no need
        if (dist[a][b] <= d) {
            ret++; 
            continue;
        }
        // add and update
        for (int i = 0; i < v; ++i) {
            for (int j = 0; j < v; ++j) {
                int nd = min(dist[i][a] + d + dist[b][j],
                    dist[i][b] + d + dist[a][j]);

                if (nd < dist[i][j])
                    dist[i][j] = nd;
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
        int v, now, soon;
        cin >> v >> now >> soon;
        init(v);
        make_graph(now);
        cout << fw(v, soon) << '\n';
    }

}
