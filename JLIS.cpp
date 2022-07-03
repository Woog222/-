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
#include <ctime>
#include <climits>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
const ll INF = 1LL << 60;

int N, M;
ll A[101];
ll B[101];
int cache[101][101];
int fun(int , int );

int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);
    A[0] = B[0] = -INF;

    int t; cin >> t;
    while (t--)
    {
        cin >> N >> M;
        for (int i = 1; i <= N; ++i)
            cin >> A[i];
        for (int i = 1; i <= M; ++i)
            cin >> B[i];
        memset(cache, -1, sizeof(cache));
        cout << fun(0, 0) - 1 << '\n';
    }
    
 
}


// 최근에 합쳐진것이 a b중하나.
int fun(int a, int b)
{
    if (a == N && b == M)
        return 1;

    int& ret = cache[a][b];
    if (ret != -1)
        return ret;

    ll last = max(A[a], B[b]);
    ret = 0;
    for (int i = a + 1; i <= N; ++i) {
        if (last < A[i])
            ret = max(ret, fun(i, b));
    }
    for (int i = b + 1; i <= M; ++i) {
        if (last < B[i])
            ret = max(ret, fun(a, i));
    }

    return ret = ret+1;

}
