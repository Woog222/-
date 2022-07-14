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
        vi enemy(N);
        vi kor(N);
        for (int i = 0; i < N; ++i)
            cin >> enemy[i];
        for (int i = 0; i < N; ++i)
            cin >> kor[i];

        sort(enemy.begin(), enemy.end());
        sort(kor.begin(), kor.end());

        int ans = 0;
        int cur = 0;
        for (int i = 0; i < N; ++i) {
            if (enemy[cur] <= kor[i]) {
                ans++;
                cur++;
            }
        }

        cout << ans << '\n';
    }
}
