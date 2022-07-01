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
const int INF = 1987654321;
const int ALPHABET = 2;

int dr[] = { 0 ,0,-1,-1,-1, 1, 1, 1 };
int dc[] = { 1,-1,-1, 0, 1,-1, 0, 1 };
string grid[5];
int cache[5][5][10];

int fun(int idx, int r, int c, const string& s);
int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);

    int t; cin >> t;

    while (t-- > 0)
    {
        for (int i = 0; i < 5; ++i)
            cin >> grid[i];

        int q; cin >> q;
        while (q--)
        {
            string s; cin >> s;
            memset(cache, -1, sizeof(cache));

            bool success = false;
            for (int i = 0; i < 5; ++i) {
                for (int j=0; j<5; ++j)
                    if (fun(0, i, j, s) == 1) {
                        success = true;
                        i = 5; //outer loop 탈출
                        break;
                    }
            }

            if (success)
                cout << s <<" YES\n";
            else
                cout << s <<" NO\n";
        }
    }


}

inline bool valid(int r, int c)
{
    return r >= 0 && r < 5 && c >= 0 && c < 5;
}

int fun(int idx, int r, int c, const string& s)
{
    if (grid[r][c] != s[idx])
        return false;
    if (idx == s.size()-1)
        return true;

    int& ret = cache[r][c][idx];
    if (ret != -1)
        return ret;
    
    ret = 0;
    for (int k = 0; k < 8; ++k) {
        int nr = r + dr[k];
        int nc = c + dc[k];
        if (!valid(nr, nc)) continue;
        if (fun(idx + 1, nr, nc, s))
            return ret = 1;
    }
    return ret;
}
