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
const ll MAX = 1000000050ll;

int nth;
int N, FROM, TO;
void fun(string s, int level);
int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);
    
    int t; cin >> t;
    while (t--)
    {
        int p, l;
        cin >> N >> p >> l;
        FROM = p; TO = p + l;
        nth = 1;
        fun("FX", 0);
        cout << '\n';
    }
}

ll count(int level)
{
    if (level == N)
        return 1;
    else
        return 2 * count(level + 1) + 2;
}
// "FX", 0, 1
void fun(string s, int level )
{

    for (int i = 0; i < s.length(); ++i) 
    {
        char c = s[i];
        if (nth >= TO)
            return;

        if (level == N || c=='F' || c=='+' || c=='-')
        {
            if (FROM <= nth && nth < TO)
                cout << c;
            nth++;
        }
        else if (c == 'X') 
        {
            ll temp = count(level);
            int cnt = (temp >= MAX) ? (int)MAX : (int)temp;
            if (cnt + nth <= FROM)
                nth += cnt;
            else
                fun("X+YF", level + 1);
        }
        else 
        {
            ll temp = count(level);
            int cnt = (temp >= MAX) ? (int)MAX : (int)temp;
            if (cnt + nth <= FROM)
                nth += cnt;
            else
                fun("FX-Y", level + 1);
        }
    }
}
