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
const int MOD = 10000000;


int N, W;
string names[100];
int weight[100];
int value[100];
int cache[100][1001];
int fun(int idx, int left);
void fun2(int idx, int left, vector<string>& chosen);
int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);
    
    int t; cin >> t;
    while (t--)
    {
        cin >> N >> W;
        for (int i = 0; i < N; ++i) 
            cin >> names[i] >> weight[i] >> value[i];

        memset(cache, -1, sizeof(cache));
        vector<string> chosen;
        fun2(0, W, chosen);
        cout << fun(0, W) << " " << chosen.size() << '\n';
        for (string s : chosen) 
            cout << s << '\n';
    }
}

// 공간 left있고, idx부터 고려한 최대 가치
int fun(int idx, int left)
{
    if (idx == N) {
        return 0;
    }

    int& ret = cache[idx][left];
    if (ret != -1)
        return ret;


    ret = fun(idx + 1, left);
    if (left-weight[idx] >= 0)
        ret = max(ret, fun(idx + 1, left - weight[idx]) + value[idx]);
    return ret;
}

void fun2(int idx, int left, vector<string> &chosen)
{
    if (idx == N)
        return;
    int temp = fun(idx + 1, left);

    // choose idx
    if (left - weight[idx] >= 0 && 
        fun(idx + 1, left - weight[idx]) + value[idx] > temp ) 
    {
        chosen.push_back(names[idx]);
        fun2(idx + 1, left - weight[idx], chosen);
    }
    else {
        fun2(idx + 1, left, chosen);
    }
}
