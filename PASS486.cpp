#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
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
const int MAX = 10000000; // 백만

int minFactor[MAX + 1];
int cache[MAX + 1];
void preprocessing();
int divisorCnt(int n);
int main()
{
    
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    preprocessing();
    memset(cache, -1, sizeof(cache));
 
    int t; cin >> t;
    while (t--)
    {
        int n, lo, hi;
        cin >> n >> lo >> hi;

        int cnt = 0;
        for (int i = lo; i <= hi; ++i)
            if (divisorCnt(i) == n)
                cnt++;

        cout << cnt << '\n';
    }

}

void preprocessing()
{
    for (int i = 2; i <= MAX; ++i)
        minFactor[i] = i;
    minFactor[1] = -1;
    int last = sqrt(MAX);
    for (int i = 2; i <= last; ++i) {
        if (minFactor[i] == i) {
            for (ll temp = (ll)i * (ll)i; temp <= (ll)MAX; temp += i)
                if (minFactor[temp] = temp)
                    minFactor[temp] = i;
        }
    }
}   

int divisorCnt(int n) 
{
    if (n == 1)
        return 1;

    int& ret = cache[n];
    if (ret != -1)
        return ret;

    int m = minFactor[n];
    int a = 0, temp = n;
    while (temp % m == 0) {
        a++;
        temp /= m;
    }

    return ret = divisorCnt(n / m) * (a + 1) / a;
}
