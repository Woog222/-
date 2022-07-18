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
#include <climits>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
const int INF = 987654321;

int N, K;
int L[5000], M[5000], G[5000];

int howmany(int loc);
int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    cout.tie(nullptr);

   
    int t; cin >> t;
    while (t--)
    {
        cin >> N >> K;
        for (int i = 0; i < N; ++i)
            cin >> L[i] >> M[i] >> G[i];

        int ans = -1;
        int lo = 0, hi = INT_MAX;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (howmany(mid) >= K) {
                ans = mid;
                hi = mid - 1;
            }
            else
                lo = mid + 1;
        }

        cout << ans << '\n';
    }
    
}

int howmany(int loc) 
{
    int ret = 0;
    for (int i = 0; i < N; ++i) {
        int dist = min(loc, L[i]) - (L[i] - M[i]);
        if (dist < 0)
            continue;
        // (loc - 표지판 시작위치) / 표지판간격 + 1;
        ret += dist / G[i] + 1;
    }
    return ret;
}
