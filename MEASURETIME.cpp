#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <cstring>
#include <cmath>
#include <list>
#include <stack>
#include <assert.h>
#include <string>
#include <map>
#include <set>
#include <cstdlib>
#include <climits>
#include <cstdio>
#define el '\n'
using namespace std;
typedef long long ll;
typedef vector<int> vi;

struct FenwickTree{
    vector<int> tree;

    FenwickTree(int n) : tree(n+1) {}

    // 1부터이다! 0부터아님
    int sum(int idx) {
        idx++;
        int ret = 0;
        while (idx > 0) {
            ret += tree[idx];
            idx &= (idx - 1);
            // idx -= (idx&-idx); 
            // 끝의 1비트만큼 뺌
        }
        return ret;
    }
    
    void add(int idx, int val) {
        idx++;
        while (idx < tree.size()) {
            tree[idx] += val;
            idx += idx & -idx; // 끝의 1비트만큼 더함
        }
    }
};

int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false); cout.tie(nullptr);
    int t; cin >> t;
    while (t--)
    {
        int n; cin >> n;
        vi a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        FenwickTree fenwick(1000000);
        ll ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += (ll)fenwick.sum(999999) - fenwick.sum(a[i]);
            fenwick.add(a[i], 1);
        }
        cout << ans << el;
    }
}
