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

int N;
int grid[101][101]; // 1~N
int cache[101][101];
int fun2(int r, int c);
int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);
    
    int t; cin >> t;
    while (t--)
    {
        cin >> N;
        for (int i = 1; i <= N; ++i) 
            for (int j = 1; j <= i; ++j) 
                cin >> grid[i][j];
        memset(cache, -1, sizeof(cache));
        cout << fun2(1, 1) << '\n';
    }
}

int fun(int r, int c)
{
    if (r == N)
        return grid[r][c];

    int& ret = cache[r][c];
    if (ret != -1)
        return ret;

    ret = max(fun(r + 1, c), fun(r + 1, c + 1));
    return ret = ret + grid[r][c];
}

int fun2(int r, int c)
{
    if (r == N)
        return 1;

    if (fun(r + 1, c) > fun(r + 1, c + 1))
        return fun2(r + 1, c);
    else if (fun(r + 1, c + 1) > fun(r + 1, c))
        return fun2(r + 1, c + 1);
    else
        return fun2(r + 1, c + 1) + fun2(r + 1, c);
}
