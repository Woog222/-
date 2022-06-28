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



struct SegTree 
{

    int n;
    vi seg;

    SegTree(const vi& a) {
        n = a.size();
        seg.resize(n * 4);
        init(a, 1, 0, n - 1);
    }


    int init(const vi& a, int node, int lo, int hi) 
    {
        if (lo == hi)
            return seg[node] = a[lo];

        int mid = (lo + hi) / 2;
        int leftHighestNode = init(a, node * 2, lo, mid);
        int rightHighestNode = init(a, node * 2 + 1, mid + 1, hi);

        if (depth[leftHighestNode] >= depth[rightHighestNode])
            seg[node] = rightHighestNode;
        else
            seg[node] = leftHighestNode;

        return seg[node];
    }

    int query(int lo, int hi) {
        return query(1,0,n-1, lo, hi);
    }

    int query(int node, int nodeLeft, int nodeRight, int lo, int hi) 
    {
        if (lo <= nodeLeft && nodeRight <= hi)
            return seg[node];

        int mid = (nodeLeft+ nodeRight) / 2;

        int leftHighestNode=-1, rightHighestNode=-1;
        if (lo <=mid)
            leftHighestNode = query(node * 2, nodeLeft, mid, lo, hi);
        if (mid < hi)
            rightHighestNode = query(node * 2+1,  mid+1, nodeRight, lo, hi);

        if (leftHighestNode == -1)
            return rightHighestNode;
        else if (rightHighestNode == -1)
            return leftHighestNode;

        if (depth[leftHighestNode] >= depth[rightHighestNode])
            return rightHighestNode;
        else
            return leftHighestNode;
    }
};



void init();
void make_tree();
void dfs(vi& Order, int here, int dep);

int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    int t; cin >> t;

    while (t-- > 0)
    {
        cin >> N >> Q;
        init();
        make_tree();

        vi Order;
        dfs(Order, 0, 0);
        SegTree seg(Order);

        while (Q-- > 0)
        {
            int a, b; cin >> a >> b;
            int lca;
            if (in[a] < in[b])
                lca = seg.query(in[a], in[b]);
            else
                lca = seg.query(in[b], in[a]);

            cout << depth[a]+depth[b] - 2*depth[lca] << '\n';
        }
    }
}

void init()
{
    memset(depth, -1, sizeof(depth));
    for (int i = 0; i < N; ++i)
        tree[i].clear();

}

void make_tree()
{
    for (int i = 1; i < N; ++i) {
        int p; cin >> p;
        tree[p].push_back(i);
    }
}


void dfs(vi& Order, int here, int dep)
{
    Order.push_back(here);
    depth[here] = dep;
    in[here] = (int)Order.size() - 1;

    for (int next : tree[here]) {
        dfs(Order, next, dep + 1);
        Order.push_back(here);
    }
}
