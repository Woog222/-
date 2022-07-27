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
typedef vector<int> vi;

int  K;
string s;

int commonPrefix(int i, int j);
vi getSuffixArray();
int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false); cout.tie(nullptr);
    int t;  cin >> t;
    while (t--) {
        cin >> K >>  s;
        vi sa = getSuffixArray();
        int n = s.length();

        int ans = 0;
        for (int i = 0; i + K <= n; ++i) {
            ans = max(ans, commonPrefix(sa[i], sa[i + K-1]));
        }
        cout << ans << el;
    }
}

int commonPrefix(int i, int j)
{
    int n = s.length();
    int ret = 0;
    while (i+ret < n && j+ret < n && s[i+ret] == s[j+ret])
        ret++;
    return ret;
}


vi getSuffixArray()
{
    int n = s.length();
    vi group(n + 1), nextGroup(n + 1), ret(n);
    for (int i = 0; i < n; ++i) group[i] = s[i], ret[i] = i;
    group[n] = -1;

    int t = 1;
    while (true)
    {
        auto comp = [&](int i, int j) {
            if (group[i] == group[j])
                return group[i + t] < group[j + t];
            return group[i] < group[j];
        };
        sort(ret.begin(), ret.end(), comp);

        nextGroup[n] = -1;
        nextGroup[ret[0]] = 0;
        for (int i = 1; i < n; ++i)
            nextGroup[ret[i]] = nextGroup[ret[i - 1]] + comp(ret[i - 1], ret[i]);
        swap(group, nextGroup);

        t *= 2;
        if (group[ret[n - 1]] == n - 1)
            break;
    }
    return ret;
}
