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




int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);

    ll dp[101] = { 0, };
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= 100; ++i) {
        dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
    }
    
    int t; cin >> t;
    while (t--)
    {
        int n; cin >> n;
        ll ans = 0;
        if (n % 2)
        {
            ans = (dp[n] - dp[(n - 1) / 2]) % MOD;
        }
        else
        {
            ans = (dp[n] +MOD - (dp[n / 2] + dp[n / 2 - 1]) % MOD) % MOD;
        }

        cout << ans%MOD << endl;
    }
}
