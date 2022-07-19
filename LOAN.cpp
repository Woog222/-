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
#include <climits>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
const int INF = 987654321;

int M;
double N, P;

bool fun(double c);
int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cout << fixed;
    cout.precision(10);
   
    int t; cin >> t;
    while (t--)
    {
        cin >> N >> M >> P;

        double lo = 0.0, hi = N*2.0;
        for (int i = 0; i < 100; ++i) {
            double mid = (lo + hi) / 2.0;
            if (fun(mid))
                hi = mid;
            else
                lo = mid;
        }
        cout << (lo + hi) / 2 << '\n';
    }
    
}

bool fun(double c)
{
    double loan = N;
    double r = P / 12.0 / 100.0;
    for (int i = 0; i < M; ++i) {
        loan = loan *(1.0+r) - c;
        if (loan <= 0.0)
            return true;
    }

    return false;
}
