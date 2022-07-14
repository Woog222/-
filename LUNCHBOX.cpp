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

int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cout << fixed;
    
    int t; cin >> t;
    while (t--)
    {
        cin >> N;
        vector<pii> v(N); // (eat, heat)
        vi eat(N), heat(N);

        for (int i = 0; i < N; ++i) cin >> heat[i];
        for (int i = 0; i < N; ++i) cin >> eat[i];

        for (int i = 0; i < N; ++i)
            v[i] = pii(eat[i], heat[i]);

        sort(v.begin(), v.end(),
            [] (const pii& a, const pii& b) {
                if (a.first == b.first)
                    return a.second < b.second;
                else
                    return a.first > b.first;
            }
        );

        int ans = 0;
        int heatSum = 0;
        for (int i = 0; i < N; ++i) {
            heatSum += v[i].second;
            ans = max(ans, heatSum + v[i].first);
        }

        cout << ans << '\n';
    }
}
