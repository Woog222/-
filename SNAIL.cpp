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

int N ,M;
double cache[1001][1001];
double fun(int day, int climbed);
int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);
    
    int t; cin >> t;
    while (t--)
    {
        cin >> N >> M;
        cout << fixed;
        cout.precision(10);

        for (int i = 0; i <= M; ++i) 
            for (int j = 0; j <= N; ++j)
                cache[i][j] = -1.0;
        cout << fun(0, 0) << '\n';
    }
}

double fun(int day, int climbed)
{
    if (day == M) {
        if (climbed >= N)
            return 1;
        else
            return 0;
    }
    if (climbed >= N)
        return 1;

    double& ret = cache[day][climbed];
    if (ret != -1.0)
        return ret;

    return ret = 0.75 * fun(day + 1, climbed + 2) + 0.25 * fun(day + 1, climbed + 1);
}
