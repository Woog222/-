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

int N;
double cal(double x, const vector<double>& coef);
vector<double> differential(const vector<double>& coef);
vector<double> fun(int k, vector<double> coef);
double bisection(double x1, double x2, const vector<double>& coef);
int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cout << fixed;
    cout.precision(10);
   
    int t; cin >> t;
    while (t--)
    {
        cin >> N;
        vector<double> coef(N+1); 
        for (int i = 0; i <= N; ++i)
            cin >> coef[N - i];

        auto ans = fun(N, coef);
        for (double k : ans)
            cout << k << " ";
        cout << '\n';
    }
    
}

double cal(double x, const vector<double>& coef) {
    double ret = 0.0;
    double temp = 1.0;
    for (int i = 0; i < coef.size(); ++i) {
        ret += coef[i] * temp;
        temp *= x;
    }
    return ret;
}


vector<double> fun(int k, vector<double> coef)
{
    if (k == 1)
        return vector<double> {-coef[0] / coef[1]};

    vector<double> polars = fun(k - 1, differential(coef));
    vector<double> ret;

    vector<double> temp = vector<double>(polars.size() + 2);
    temp[0] = -11.0;
    for (int i = 0; i < polars.size(); ++i) 
        temp[i + 1] = polars[i];
    temp[polars.size() + 1] = 11.0;
    // 0~1 , 1~2, .. back ~11.0
    for (int i = 0; i < temp.size()-1; ++i) {
        double x1 = temp[i], x2 = temp[i + 1];
        double y1 = cal(x1, coef);
        double y2 = cal(x2, coef);
        if (y1 == 0.0 || y2 == 0.0) {
            if (y1 == 0.0)
                ret.push_back(x1);
            if (y2 == 0.0)
                ret.push_back(x2);
        }
        else if (y1 * y2 < 0.0) {
            ret.push_back(bisection(x1, x2, coef));
        }
    } 


    sort(ret.begin(), ret.end());
    ret.erase(unique(ret.begin(), ret.end()), ret.end());
    return ret;
}

double bisection(double x1, double x2, const vector<double>& coef)
{
    if (cal(x1, coef) > cal(x2,coef))
        swap(x1, x2);
    // f(x1) ~ 0 ~ f(x2)

    double lo = x1, hi = x2;
    for (int i = 0; i < 100; ++i) {
        double mid = (lo + hi) / 2;
        if (cal(mid, coef) > 0)
            hi = mid;
        else
            lo = mid;
    }

    return (lo + hi) / 2;
}

vector<double> differential(const vector<double>& coef) {

    vector<double> ret = vector<double>(coef.size() - 1);
    for (int i = 1; i < coef.size(); ++i) {
        ret[i - 1] = coef[i] * i;
    }
    return ret;
}
