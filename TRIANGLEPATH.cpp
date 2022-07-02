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
int grid[100][100];
int cache[100][100];
int fun(int r, int c);

int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);

    int t; cin >> t;
    while (t--)
    {
        cin >> N;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j <= i; ++j)
                cin >> grid[i][j];
        }
        memset(cache, -1, sizeof(cache));
        cout << fun(0, 0) << '\n';
    }
    
 
}



int fun(int r, int c)
{
    if (r == N - 1)
        return grid[r][c];

    int& ret = cache[r][c];
    if (ret != -1)
        return ret;

    ret = max(fun(r + 1, c), fun(r + 1, c + 1));
    return ret = ret + grid[r][c];
}
