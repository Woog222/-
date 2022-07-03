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

int cache[10002];
int level(const string s);
int fun(const string& s, int idx);

int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);
    
    //freopen("input.txt", "r", stdin);

    int t; cin >> t;
    while (t--)
    {
        string s; cin >> s;
        memset(cache, -1, sizeof(cache));
        cout << fun(s, 0) << '\n';
    }
    
 
}

int level(const string s)
{
    
    int n = s.length();
    //1
    bool ok = true;
    for (int i = 1; i < n; ++i) {
        if (s[i] != s[i - 1]) {
            ok = false; 
            break;
        }
    }
    if (ok)
        return 1;

    // 2
    ok = true;
    if (s[1] - s[0] == 1 || s[1] - s[0] == -1)
    {
        int d = s[1] - s[0];
        for (int i = 1; i < n; ++i) {
            if (s[i]-s[i-1] != d) {
                ok = false;
                break;
            }
        }
        if (ok)
            return 2;
    }

    // 4
    ok = true;
    for (int i = 2; i < n; ++i) {
        if (s[i] != s[i-2]) {
            ok = false;
            break;
        }
    }
    if (ok)
        return 4;

    // 5
    int d = s[1] - s[0];
    ok = true;
    for (int i = 1; i < n; ++i) {
        if (s[i]-s[i-1] != d) {
            ok = false;
            break;
        }
    }
    if (ok)
        return 5;

    return 10;
}
// 최근에 합쳐진것이 a b중하나.
int fun(const string& s, int idx)
{
    if (idx == s.length())
        return 0;

    int& ret = cache[idx];
    if (ret != -1)
        return ret;

    ret = INF;
    for (int L = 3; L <= 5; ++L) {
        if (idx + L <= (int)s.length())
            ret = min(ret, 
                level( s.substr(idx, L) ) + fun(s, idx + L) 
            );
    }

    return ret;
}
