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
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> pii;
const ll INF = 987654321;
const ll MOD = 20090711;


int N, Q;
vi tree[100000];
int depth[100000];
int in[100000];

struct Fenwick
{
    vi tree;
    Fenwick(int size) : tree(size+1) {}

    void add(int idx, int val) {
        idx++;

        while (idx < tree.size()) {
            tree[idx] += val;
            idx += idx & -idx;
        }
    }

    int sum(int idx) 
    {
        idx++;
        int ret = 0;
        while (idx > 0) { 
            ret += tree[idx];
            idx = idx & (idx-1); // lsb 1 지우는 연산
        }
        return ret;
    }
};




int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    int t; cin >> t;

    while (t-- > 0)
    {
        cin >> N;
        vi a(N);
        for (int i = 0; i < N; ++i)
            cin >> a[i];

        Fenwick fenwick = Fenwick(1000000);

        ll ans = 0;
        for (int i = 0; i < N; ++i) {
            ans += (ll)fenwick.sum(999999) - fenwick.sum(a[i]);
            fenwick.add(a[i], 1);
        }

        cout << ans << '\n';
    }
}
