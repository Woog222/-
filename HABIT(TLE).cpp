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
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 987654321;

struct Pred {
    const vi& group;
    int t;
    Pred(const vi& _group, int _t) : group(_group), t(_t) {}

    bool operator() (int a, int b) {
        if (group[a] != group[b])
            return group[a] < group[b];
        return group[a + t] < group[b + t];
    }


};

string s;
int  K;

int fun(const vi& suffixArray, int from, int to);
vi getSuffixArray(const string& s);
int main() 
{
    int t; cin >> t;
    while (t-- > 0)
    {
        cin >> K >> s;
        vi suffixArray = getSuffixArray(s); // o(n * logn *logn)

        int ans = 0;
        // i n-k ~ n-1 is last
        // o(4000 최대문자열 길이) * o(fun)
        for (int i = 0; i + K <= s.size(); ++i) { 
            ans = max(ans, fun(suffixArray, i, i + K));
        }

        cout << ans << '\n';
    }

}

int fun(const vi& suffixArray, int from, int to)
{
    // [from, to)
    int ret = 0;
    vi temp = vi(suffixArray.begin() + from, suffixArray.begin() + to);

    if (temp.size() == 1) {
        return s.size() - temp[0];
    }

    while (true)
    {
        bool ok = true;
        for (int i = 0; i < temp.size() - 1; ++i) 
        {
            if (temp[i] >= s.size() || temp[i+1] >= s.size()) {
                ok = false;
                break;
            }

            if (s[temp[i]] != s[temp[i + 1]]) {
                ok = false;
                break;
            }
        }

        if (ok) {
            ret++;
            for (int& i : temp) ++i;
        }
        else
            break;
    }

    return ret;
}

vi getSuffixArray(const string& s)
{
    int n = s.size();

    int t = 1;
    vi group(n + 1);
    // 첫 문자열 숫자를 그대로 그룹에 넣기
    for (int i = 0; i < n; ++i) group[i] = s[i];
    group[n] = -1;

    vi ret(n);
    for (int i = 0; i < n; ++i)
        ret[i] = i;

    while (t < n) {

        Pred pred(group, t);
        sort(ret.begin(), ret.end(), pred);

        t *= 2;
        if (t >= n) break;

        vi newGroup(n + 1);
        newGroup[n] = -1;
        newGroup[ret[0]] = 0;
        for (int i = 1; i < n; ++i) {
            // 최소 비내림차순으로 정렬, 밑 조건이 false라면 같다는 뜻
            if (pred(ret[i - 1], ret[i]))
                newGroup[ret[i]] = newGroup[ret[i - 1]] + 1;
            else
                newGroup[ret[i]] = newGroup[ret[i - 1]];
        }
        group = newGroup;
    }

    return ret;
}
