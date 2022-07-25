#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define el '\n'
using namespace std;
typedef long long ll;
const int MOD = 10000;
const int SEED = 1983;

struct RNG {
    unsigned seed;

    RNG(unsigned _seed=SEED) : seed(_seed){}

    int next() {
        int ret = seed % MOD + 1;
        seed = seed * 214013u + 2531011u;
        return ret;
    }
};

int N, K; // 박스 수, 어린이의 수

int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--)
    {
        cin >> K >> N;
        RNG rng;
        queue<int> q;

        int ans = 0;
        int sum = 0;
        for (int i = 0; i < N; ++i) {
            int num = rng.next();
            sum += num;
            q.push(num);

            while (sum > K) {
                sum -= q.front();
                q.pop();
            }
            if (sum == K) {
                ans++;
            }
        }

        cout << ans << el;
    }
}
