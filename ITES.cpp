#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 987654321;
const int MAX = 50000000;

struct RNG {
    unsigned int seed;
    RNG() : seed(1983) {}

    unsigned int next() {
        unsigned int ret = seed % 10000 + 1;
        seed = seed * 214013u + 2531011u;
        return ret;
    }
};

int N, K;

int solve();
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t-- > 0)
    {
        cin >> K >> N;
        cout << solve() << '\n';
    }
}

int solve()
{
    RNG rng;

    queue<unsigned int> q;
    int left = 1, right = 1;
    int sum = rng.next();
    int ans = 0;

    q.push(sum);
    while (right <= N)
    {
        if (sum < K) // 더 작아서, 추가해야됨
        {
            q.push(rng.next());
            ++right;
            sum += q.back();
        }
        else if (sum == K) // 같음!
        {
            ans++;
            if (left == right) {
                q.push(rng.next());
                sum += q.back();
                right++;
            }
            sum -= q.front(); q.pop();
            left++;
        }
        else //넘침, 줄여야됨
        {
            if (left == right) {
                q.push(rng.next());
                sum += q.back();
                right++;
            }
            sum -= q.front(); q.pop();
            left++;
        }
    }

    return ans;
}
