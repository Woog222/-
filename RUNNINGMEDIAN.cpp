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
const int INF = 987654321;
const int MOD = 20090711;


struct RNG {
    ll seed;
    ll a, b;

    RNG(ll _a, ll _b) : seed(1983), a(_a), b(_b) {}

    ll next() {
        ll ret = (seed * a + b) % MOD;
        seed = ret;
        return seed;
    }

};

int N;

int fun(RNG& rng);
int main()
{
    int t; cin >> t;
    while (t--)
    {
        ll a, b;
        cin >> N >> a >> b;
        
        RNG rng = RNG(a, b);

        cout << fun(rng) << '\n';
    }
}

int fun(RNG& rng)
{
    ll ret = 1983;
    priority_queue<ll> left;
    priority_queue<ll, vector<ll>, greater<ll>> right;
    left.push(1983);

    for (int i = 1; i < N; ++i) 
    {
        ll next = rng.next();

        // to the right
        if (left.size() > right.size())
        {
            if (next >= left.top()) {
                right.push(next);
            }
            else {
                right.push(left.top());
                left.pop();
                left.push(next);
            }
        }
        // to the left
        else
        {
            if (next <= right.top()) {
                left.push(next);
            }
            else {
                left.push(right.top());
                right.pop();
                right.push(next);
            }
        }

        ret = (ret + left.top()) % MOD;
    }
    
    return ret;
}
