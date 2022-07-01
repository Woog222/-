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
#include <ctime>
#include <climits>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
const int INF = 987654321;


vi adj[10];

int N, M;
void init();
int fun(int idx, vector<bool> &chosen);
int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);

    int t; cin >> t;

    while (t-- > 0)
    {
        cin >> N >> M;
        init();
        for (int i = 0; i < M; ++i) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        vector<bool> chosen(N, false);
        cout << fun(0, chosen) << '\n';
    }


}

void init()
{
    for (int i=0; i<N; ++i) {
        vi().swap(adj[i]);
    }
}

int fun(int cur, vector<bool> &chosen)
{
    if (cur == N) {
        return 1;
    }


    int ret = 0;
    if (chosen[cur])
        return fun(cur + 1, chosen);

    for (int frd : adj[cur])
    {

        if (frd < cur || chosen[frd]) continue;
        chosen[cur] = true;
        chosen[frd] = true;
        ret += fun(cur + 1, chosen);
        chosen[frd] = false;
        chosen[cur] = false;
    }

    return ret;
}
