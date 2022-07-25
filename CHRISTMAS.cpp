#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <cstring>
#include <cmath>
#include <list>
#include <stack>
#include <assert.h>
#include <string>
#include <map>
#include <set>
#include <cstdlib>
#include <climits>
#define el '\n'
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
const int INF = 987654321;
const int MOD = 20091101;

int N, K; // 박스 수, 어린이의 수
int ps[100001];
int dp[100001];
int cnt[100000]; // init 0
int doll[100001]; 

void init();
void calPartialSum();
int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--)
    {
        init(); 
        // 1번 문제
        ll ret = 0;
        for (int i = 0; i < K; ++i) {
            ll temp = cnt[i];
            ret = (ret + (temp * (temp - 1)) / 2) % MOD;
        }
        cout << ret << " ";
        // 2번 문제
        vi Prev(K, -1);
        Prev[0] = 0;
        for (int i = 1; i <= N; ++i) {
            dp[i] = dp[i - 1];

            int loc = Prev[ps[i]];
            if (loc != -1)
                dp[i] = max(dp[i], dp[loc] + 1);

            Prev[ps[i]] = i;
        }
        cout << dp[N] << el;
    }
}

void calPartialSum() 
{
    ps[0] = 0;
    cnt[ps[0]] ++;
    for (int i = 1; i <= N; ++i) {
        ps[i] = (ps[i-1] + doll[i]) % K;
        cnt[ps[i]]++;
    }
}

void init()
{
    cin >> N >> K;
    for (int i = 1; i <= N; ++i) cin >> doll[i];
    memset(cnt, 0, sizeof(cnt));
    calPartialSum();
}
