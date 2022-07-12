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
const ll MAX = 1LL << 32;

int N, K;
ll skip;
int arr[501];
int cache[501]; // idx부터 시작하는 증가부분수열 길이
ll cache2[501]; // idx부터 시작하는 증가부분수열 개수
int fun(int idx);
void fun2(int idx);
int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);
    
  
    int t; cin >> t;
    while (t--)
    {
        cin >> N >> K; 
        skip = (ll)K - 1;
        for (int i = 1; i <= N; ++i)
            cin >> arr[i];

        memset(cache, -1, sizeof(cache));
        memset(cache2, -1, sizeof(cache2));
        cout << fun(0) - 1 << '\n';
        fun2(0);
    }
}

int fun(int idx)
{
    int& ret = cache[idx];
    if (ret != -1)
        return ret;

    ret = 1;
    int cur = arr[idx];
    for (int i = idx + 1; i <= N; ++i) {
        if (arr[i] > cur)
            ret = max(ret, fun(i) + 1);
    }

    return ret;
}

ll count(int idx)
{
    int len = fun(idx);
    if (len == 1)
        return 1;

    ll& ret = cache2[idx];
    if (ret != -1LL)
        return ret;

    ret = 0;
    for (int i = idx + 1; i <= N; ++i) {
        if (fun(i) == len - 1 && arr[i] > arr[idx]) {
            ret += count(i);
            if (ret >= MAX)
                return MAX;
        }
    }

    return ret;
}

// 하나씩 타고가면서 순서대로 출력
void fun2(int idx) // from idx=0
{
    int len = fun(idx);
    if (idx > 0)
        cout << arr[idx] << " ";

    if (len == 1) {
        cout << '\n';
        return;
    }


    vector<pii> v;
    for (int i = idx + 1; i <= N; ++i) 
        if (fun(i) == len - 1 && arr[idx] < arr[i])
            v.emplace_back(arr[i], i);

    // v : {arr[idx], idx}, 값 순서대로 오름차순
    sort(v.begin(), v.end());

    for (int i = 0; i < v.size(); ++i) {
        ll cnt = count(v[i].second);

        if (cnt <= skip) {
            skip -= cnt;
        }
        else {
            fun2(v[i].second);
            return;
        }
    }
    
}
