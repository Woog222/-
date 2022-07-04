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
const int MOD = 10000000;

int N, D, P;

int adj[100][100];
int connected[100];
double dp[101][100]; // 1~d일차 n번마을에 있을 확률

void init();
void makeGraph();

int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);

    int t; cin >> t;
    while (t--)
    {
        init();
        makeGraph();
        //[d][n] : d번째 날에 n번째 마을에 있을 확률
        dp[0][P] = 1.0;
        for (int i = 0; i < D; ++i) {
            for (int from = 0; from < N; ++from) {
                for (int to = 0; to < N; ++to) {
                    if (dp[i][from] > 0.0 &&  adj[from][to]) {
                        dp[i + 1][to] += dp[i][from] / (double)connected[from];
                    }
                }
            }
        }

        int q; cin >> q;
        while (q--) {
            int n; cin >> n;
            cout << fixed;
            cout.precision(8);
            cout << dp[D][n] << " ";
        }
        cout << '\n';
    }
}

void makeGraph()
{
    cin >> N >> D >> P;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> adj[i][j];
            if (adj[i][j]) connected[i]++;
        }

    }
}

void init()
{
    for (int i = 0; i <= 100; ++i)
        for (int j = 0; j < 100; ++j)
            dp[i][j] = 0.0;
    memset(connected, 0, sizeof(connected));
}
