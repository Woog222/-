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
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                cin >> grid[i][j];
        memset(cache, -1, sizeof(cache));
        if (fun(0, 0))
            cout << "YES\n";
        else
            cout << "NO\n";

    }
    
 
}


inline bool valid(int r, int c) {
    return r >= 0 && r < N && c >= 0 && c < N;
}

int fun(int r, int c)
{
    if (r == N - 1 && c == N - 1)
        return true;
    if (!valid(r, c))
        return false;

    int& ret = cache[r][c];
    if (ret != -1)
        return ret;

    ret = 0;

    int d = grid[r][c];
    if (fun(r + d, c) || fun(r, c + d)) return ret = 1;

    return ret;
}
