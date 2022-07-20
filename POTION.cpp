#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
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
#include <climits>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
const int INF = 987654321;
const int MAX = 1000; // 백만

int minFactor[MAX + 1];
int N;

vi gcds(const vi& a);
void vectorSum(vi& a, const vi& b);
int main()
{
    
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
 
    int t; cin >> t;
    while (t--)
    {
        cin >> N;
        vi p(N), r(N);
        for (int i = 0; i < N; ++i) cin >> r[i];
        for (int i = 0; i < N; ++i) cin >> p[i];
        vi minimum = gcds(r);
        
        while (true)
        {
            bool ok = true;
            for (int i=0; i<N; ++i)
                if (r[i] < p[i]) {
                    ok = false;
                    break;
                }

            if (ok) {
                for (int i = 0; i < N; ++i)
                    cout << r[i] - p[i] << " ";
                cout << '\n';
                break;
            }
            else 
                vectorSum(r, minimum);
            
        }
        
    }

}

int gcd(int a, int b)
{
    // a >= b
    if (b > a)
        swap(a, b);
    while (b > 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }

    return a;
}

vi gcds(const vi& a)
{
    vi ret = a;
    if (a.size() == 1)
        return ret;

    int temp = gcd(a[0], a[1]);
    for (int i = 2; i < a.size(); ++i)
        temp = gcd(a[i], temp);

    for_each(ret.begin(), ret.end(),
        [temp](int& num) {
            num /= temp;
        }
        );
    return ret;
}

void vectorSum(vi& a, const vi& b) {
    for (int i = 0; i < a.size(); ++i) {
        a[i] += b[i];
    }
}
