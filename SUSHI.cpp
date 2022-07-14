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

int N;
int dp[201];
int p[20], joy[20];

int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    

    int t; cin >> t;
    while (t--)
    {
        int m;
        cin >> N >> m;
        m /= 100;
        for (int i = 0; i < N; ++i) 
            cin >> p[i] >> joy[i];
        for (int i = 0; i < N; ++i)
            p[i] /= 100;

        dp[0] = 0;
        for (int b = 1; b <= m; ++b) {
            int cur = dp[(b - 1) % 201];
            for (int i = 0; i < N; ++i) {
                if (b >= p[i]) {
                    cur = max(cur, dp[(b - p[i] + 201) % 201] + joy[i]);
                }
            }
            dp[b % 201] = cur;;

        }
        cout << dp[m%201] << '\n';
    }
}
