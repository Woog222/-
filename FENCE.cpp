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
const int INF = 987654321;


int N; 
int fun(const vi& height, int lo, int hi);

int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);

    int t; cin >> t;
    while (t--)
    {
        cin >> N;
        vi height(N);
        for (int i = 0; i < N; ++i)
            cin >> height[i];

        cout << fun(height, 0, N - 1) << '\n';

    }


}
int middle(const vi& height, int mid)
{
    int h = min(height[mid], height[mid + 1]);

    int l = mid, r = mid + 1;

    while (l >= 0 && height[l] >= h) l--;
    while (r < N && height[r] >= h) r++;

    return (r - l - 1) * h;
}

int fun(const vi& height, int lo, int hi)
{
    if (lo == hi)
        return height[lo];

    int mid = (lo + hi) / 2;
    int ret = max( fun(height, lo, mid), fun(height, mid + 1, hi));
    ret = max(ret, middle(height, mid));

    return ret;
}
