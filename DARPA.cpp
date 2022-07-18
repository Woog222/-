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

int N, M;
vector<double> loc;
double fun();
int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
   
    int t; cin >> t;
    while (t--)
    {
        cin >> N >> M;
        loc.resize(M);
        for (int i = 0; i < M; ++i)
            cin >> loc[i];
        sort(loc.begin(), loc.end());
        cout << fixed;
        cout.precision(2);
        cout << fun() << '\n';

    }
}

bool possible(double least)
{
    int left = N;
    double last = -500.0;
    for (double spot : loc) {
        if (spot - last >= least)
        {
            last = spot;
            left--;
        }
        if (left == 0)
            return true;
    }
    return false;
}
double fun()
{
    double ret = 240.0;
    double lo = 0.0 , hi = 240.0;
    while ((hi - lo) >= 0.000000001)
    {
        double mid = (lo + hi) / 2;
        if (possible(mid)) {
            ret = mid;
            lo = mid;
        }
        else
            hi = mid;
    }

    return ret;
}
