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
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
const int INF = 1987654321;
const int MOD = 20090711;


struct RmMQ {

    int n;

    vector<pii> segTree;
    RmMQ(const vi& height)
    {
        n = height.size();
        segTree.resize(4 * static_cast<std::vector<pii, std::allocator<pii>>::size_type>(n));
        init(height , 1, 0, n-1);
    }

    pii query(int lo, int hi) {
        return query(lo, hi, 1, 0, n - 1);
    }

private:
    pii init(const vi& h, int node, int nodeLeft, int nodeRight) 
    {
        if (nodeLeft == nodeRight)
            return segTree[node] = make_pair(h[nodeLeft], h[nodeLeft]);

        int mid = (nodeLeft + nodeRight) / 2;
        pii leftPair = init(h, node * 2, nodeLeft, mid);
        pii rightPair = init(h, node * 2 + 1, mid + 1, nodeRight);

        segTree[node] = make_pair(
            min(leftPair.first, rightPair.first),
            max(leftPair.second, rightPair.second)
        );

        return segTree[node];
    }

    pii query(int lo, int hi, int node, int nodeLeft, int nodeRight)
    {


        if (lo <= nodeLeft && nodeRight <= hi) {
            return segTree[node];
        }



        pii ret = pii(20001, -1);
        int mid = (nodeLeft + nodeRight) / 2;
        if (lo <= mid) {
            pii temp = query(lo, hi, node * 2, nodeLeft, mid);
            ret.first = min(ret.first, temp.first);
            ret.second = max(ret.second, temp.second);
        }
        if (mid < hi) {
            pii temp = query(lo, hi, node*2 + 1, mid+1, nodeRight);
            ret.first = min(ret.first, temp.first);
            ret.second = max(ret.second, temp.second);
        }

        return ret;
    }
};



int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    int t;
    cin >> t;
    while (t-- > 0)
    {
        int n, q;
        cin >> n >> q;

        vi h(n);
        for (int i = 0; i < n; ++i)
            cin >> h[i];


        RmMQ seg = RmMQ(h);

        while (q-- > 0) {
            int lo, hi;
            cin >> lo >> hi;

            pii minmax = seg.query(lo, hi);

            cout << minmax.second - minmax.first << '\n';
        }
    }
}
