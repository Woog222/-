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
const double PI = acos(-1.0);

int N;
double X[100];
double Y[100];
double R[100];
pair<double, double> range[100];

void makeRange();
int greedy(double from, double to);
int fun();
int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    
    int t; cin >> t;
    while (t--)
    {
        cin >> N;
        for (int i = 0; i < N; ++i)
            cin >> Y[i] >> X[i] >> R[i];
        makeRange();

        int ans = fun();
        if (ans == INF)
            cout << "IMPOSSIBLE\n";
        else
            cout << ans << '\n';
    }
}

void makeRange()
{
    for (int i = 0; i < N; ++i) {
        double mid = fmod(2 * PI + atan2(Y[i], X[i]), 2 * PI);
        double ceta = 2 * asin(R[i] / 16.0);
        range[i] = { mid - ceta, mid + ceta };
    }

    sort(range, range + N);
}

int fun()
{
    int ans = INF;
    // 0 포함하는것중에 하나 선택하고 그리디
    for (int i = 0; i < N; ++i) 
    {
        // 0 덮는다면
        if (range[i].first <= 0.0 || range[i].second >= 2 * PI)
        {
            double from = fmod(range[i].second, 2 * PI);
            double to = fmod(range[i].first + 2 * PI, 2 * PI);
            ans = min(ans, 1 + greedy(from, to));
        }
    }

    return ans;
}

int greedy(double from, double to)
{
    int ret = 0;
    int idx = 0;
    while (from < to)
    {
        // from보다 앞에서 시작하면서 제일 긴 걸 찾는다
        double maxCover = -1;
        while (idx < N && range[idx].first <= from) {
            
            maxCover = max(maxCover, range[idx].second);
            idx++;
        }

        // if can't cover all
        if (maxCover <= from)
            return INF;

        from = maxCover;
        ret++;
    }

    return ret;
}
