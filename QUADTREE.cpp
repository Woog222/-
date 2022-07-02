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


string fun(string::iterator& it);
int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);
    
    int t; cin >> t;
    while (t-- > 0)
    {
        string s; cin >> s;
        string::iterator it = s.begin();
        cout << fun(it) << '\n';
    }
}

string fun(string::iterator& it)
{
    char c = *(it++);

    if (c != 'x')
        return string(1, c);

    string lu = fun(it);
    string ru = fun(it);
    string ld = fun(it);
    string rd = fun(it);

    return c + ld + rd + lu + ru;
}
