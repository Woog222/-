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
int fun(const string& w, const string& s, int widx, int sidx);

int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);

    int t; cin >> t;
    while (t--)
    {
        string w; cin >> w;
        int n; cin >> n;
        vector<string> ans;
        while (n--) {
            string s; cin >> s;
            if (fun(w, s, 0, 0))
                ans.push_back(s);
        }

        sort(ans.begin(), ans.end());
        for (string s : ans)
            cout << s << '\n';

    }
    
 
}



int fun(const string& w, const string& s, int widx, int sidx)
{
    if (widx == w.length() && sidx == s.length())
        return true;
    if (widx == w.length())
        return false;
    if (sidx == s.length()) {
        if (w[widx] =='*')
            return fun(w,s,widx+1, sidx);
        else
            return false;
    }

    if (w[widx] == '*')
    {
        for (int k = 0; sidx + k <= s.length(); ++k) {
            if (fun(w, s, widx + 1, sidx + k))
                return true;
        }
    }
    else
    {
        if (w[widx] == '?' || w[widx] == s[sidx])
            return fun(w, s, widx + 1, sidx + 1);
    }

    return false;
}
