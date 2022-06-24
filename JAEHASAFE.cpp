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
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 987654321;

int N;
vi make_fail(const string& p);
int fun(const string& s, const string& p);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t-- > 0)
    {
        cin >> N;
        N++;
        vector<string> s(N);
        for (int i = 0; i < N; ++i) {
            cin >> s[i];
        }

        int ans = 0;
        for (int i = 1; i < N; i += 2)
        {
            string extended = s[i] + s[i];

            ans += fun(extended, s[i - 1]);
            if (i + 1 < N)
                ans += fun(extended, s[i + 1]);
        }

        cout << ans << '\n';
    }
}


vi make_fail(const string& p)
{
    vi fail(p.size(), 0);

    int matched = 0;
    for (int i = 1; i < p.size(); ++i)
    {
        while (matched > 0 && p[i] != p[matched]) matched = fail[matched - 1];
        
        if (p[i] == p[matched]) {
            matched++;
            fail[i] = matched;
        }
        else {
            fail[i] = 0;
        }
    }

    return fail;
}

int fun(const string& s, const string& p)
{

    vi fail = make_fail(p);

    int matched = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        while (matched > 0 && s[i] != p[matched]) 
            matched = fail[matched - 1];

        if (s[i] == p[matched]) 
        {
            matched++; 
            if (matched == p.size()) {
                return i - matched + 1;
            }
        }
    }


    //never reach here
    assert(0);
    return 0;
}
