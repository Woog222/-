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
int cache[51][51];
int fun(const deque<int>& arr, int from, int to);

int main()
{
    int t; cin >> t;
    while (t--)
    {
        cin >> N;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                cache[i][j] = -INF;
        deque<int> arr(N);
        for (int i = 0; i < N; ++i)
            cin >> arr[i];
        
        cout << fun(arr, 0, N-1) << '\n';
    }
  
}
// 0 ~ N-1
int fun(const deque<int>& arr, int from, int to)
{
    int len = to - from + 1;
    if (len == 0) {
        return 0;
    }
    int& ret = cache[from][to];
    if (ret != -INF)
        return ret;

    // 왼 1
    int temp = arr[from];
    ret = max(ret, temp - fun(arr, from+1, to));
    // 오 1
    temp = arr[to];
    ret = max(ret, temp - fun(arr, from, to-1));

    if (len < 2)
        return ret;

    // 왼2
    ret = max(ret, -fun(arr, from+2, to));

    // 오2
    ret = max(ret, -fun(arr, from, to-2));


    return ret;
}
