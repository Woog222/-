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
int fun(vi& v);
int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    
    int t; cin >> t;
    while (t--)
    {
        cin >> N;
        vi v(N);
        for (int i = 0; i < N; ++i)
            cin >> v[i];
        cout << fun(v) << '\n';
    }
}

int fun(vi& v)
{
    if (v.size() == 1)
        return 0;


    sort(v.begin(), v.end(), greater<int>());

    int n = v.size();
    v[n - 2] = v[n-1] + v[n-2];
    v.pop_back();

    int temp = v.back();
    return temp + fun(v);
}
