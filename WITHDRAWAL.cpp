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

int N, K;
int c[1000], r[1000];

bool fun(double k);
int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cout << fixed;
    cout.precision(10);
   
    int t; cin >> t;
    while (t--)
    {
        cin >> N >> K;
        for (int i = 0; i < N; ++i)
            cin >> r[i] >> c[i];

        double lo = 0.0, hi = 1.0;
        while ((hi - lo) >= 1e-11) {
            double mid = (lo + hi) / 2;
            if (fun(mid)) 
                hi = mid;
            else
                lo = mid;
        }
        cout << hi << '\n';
    }
    
}


bool fun(double grade) {
    vector<double> temp(N);
    for (int i = 0; i < N; ++i)
        temp[i] = c[i] * grade - r[i];

    sort(temp.begin(), temp.end(), greater<double>());

    double sum = 0;
    for (int i = 0; i < K; ++i)
        sum += temp[i];

    return sum >= 0.0;
}
