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

int N, S;
vi a;
int cache[101][11];
int psum[101];
int psqsum[101];

void makePsum();
int fun(int idx, int used);
int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);
    
    //freopen("input.txt", "r", stdin);

    int t; cin >> t;
    while (t--)
    {
        cin >> N >> S;
        vi(N+1,0).swap(a);
        for (int i = 1; i <= N; ++i)
            cin >> a[i];

        sort(a.begin(), a.end());
        makePsum();
        memset(cache, -1, sizeof(cache));
        cout << fun(1, S) << '\n';
    }
    
 
}
inline int sqr(int num) {
    return num * num;
}
void makePsum()
{
    psum[0] = 0;
    psqsum[0] = 0;
    for (int i = 1; i <= N; ++i) {
        psum[i] = psum[i - 1] + a[i];
        psqsum[i] = psqsum[i - 1] + sqr(a[i]);
    }
}

int minError(int from, int to)
{
    int sqsum = psqsum[to] - psqsum[from - 1];
    int sum = psum[to] - psum[from - 1];
    int m = (int)( 0.5 + (double)sum / (to - from + 1));
    return sqsum - 2 * m * sum + sqr(m) * (to- from + 1);
}

int fun(int idx, int left)
{
    if (idx == N+1)
        return 0;

    if (left == 0)
        return INF;

    int& ret = cache[idx][left];
    if (ret != -1)
        return ret;

    ret = INF;

    for (int i = idx; i <= N; ++i) {
        ret = min(ret, minError(idx, i) + fun(i + 1, left - 1));
    }


    return ret;
}
