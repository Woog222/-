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

int skip;
int bi[201][201]; 
void cal();

void fun(int a, int b, string ans);
int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);
    cal();
    int t; cin >> t;
    while (t--)
    {
        int n, m, k;
        cin >> n >> m >> k;
        skip = k - 1;
        fun(n, m, string());
    }
}

void cal()
{
    int M = 1000000100;
    bi[1][0] = bi[1][1] = 1;
    for (int i = 2; i <= 200; ++i) {
        bi[i][0] = bi[i][i] = 1;
        for (int j = 1; j < i; ++j)
            bi[i][j] = min(M, bi[i - 1][j] + bi[i - 1][j - 1]);
    }
}

void fun(int a, int b, string ans)
{
    if (a == 0 && b == 0) {
        cout << ans << endl;
        return;
    }

    if (a == 0) {
        fun(a, b - 1, ans+ 'o');
        return;
    }
    if (b == 0) {
        fun(a - 1, b, ans + '-');
        return;
    }
    
    int temp = bi[a + b - 1][a - 1];
    if (skip >= temp) {
        skip -= temp;
        fun(a, b - 1, ans + 'o');
    }
    else {
        fun(a - 1, b, ans + '-');
    }
}
