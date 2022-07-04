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


ll cache[101][101];
ll fun(ll left, ll before);
int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);

    int t; cin >> t;
    while (t--)
    {
        int n; cin >> n;
        memset(cache, -1, sizeof(cache));
        cout << fun(n, 0) << '\n';
    }
}

ll fun(ll left, ll before)
{
    if (left == 0)
        return 1;

    ll& ret = cache[left][before];
    if (ret != -1)
        return ret;

    ret = 0;
    if (before == 0) {
        for (int i = 1; i <= left; ++i)
            ret = (ret + fun(left - i, i) ) % MOD;
    }
    else {
        for (int i = 1; i <= left; ++i)
            ret = (ret + fun(left - i, i) * (before + i - 1)) % MOD;
    }



    return ret;
}
