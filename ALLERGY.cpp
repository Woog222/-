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
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
const int INF = 987654321;

int best;
int N, M;
vi canEat[50], eaters[50];

void init();

void fun(vi& eatcnt, int chosen);
int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    cout.tie(nullptr);

    int t; cin >> t;
    while (t--)
    {
        cin >> N >> M;
        init();
        vi eatcnt(N, 0);
        fun(eatcnt, 0);
        cout << best << '\n';

        /*
        for (int i = 0; i < N; ++i) {
            cout << i << ": ";
            for (int food : canEat[i])
                cout << food << " ";
            cout << '\n';
        }
        for (int i = 0; i < M; ++i) {
            cout << i << ": ";
            for (int food : eaters[i])
                cout << food << " ";
            cout << '\n';
        }
         */
    }

}

void fun(vi& eatcnt, int chosen)
{
    vi::iterator hungry = find(eatcnt.begin(), eatcnt.end(), 0);
    //전부 다먹음
    if (hungry == eatcnt.end()) {
        best = min(best, chosen);
        return;
    }

    if (chosen >= best)
        return;


    for (int food : canEat[hungry - eatcnt.begin()]) {
        for (int eater : eaters[food]) 
            eatcnt[eater]++;
        fun(eatcnt, chosen + 1);
        for (int eater : eaters[food])
            eatcnt[eater]--;
    }

}

void init() 
{
    best = 100;
    for (int i = 0; i < N; ++i)
        canEat[i].clear();
    for (int i = 0; i < M; ++i)
        eaters[i].clear();

    map<string, vi> caneat;
    for (int i = 0; i < N; ++i) {
        string name; cin >> name;
        caneat[name] = vi();
    }
    for (int food = 0; food < M; ++food) {
        int cnt; cin >> cnt;
        while (cnt--) {
            string name; cin >> name;
            caneat[name].push_back(food);
        }
    }

    // 먹을수 있는 음식 적은순으로 정렬
    vector<pair<int, string>> freq;
    auto iter = caneat.begin();
    while (iter != caneat.end()) {
        freq.emplace_back(iter->second.size(), iter->first);
        iter++;
    }
    // canEat 세팅
    sort(freq.begin(), freq.end());
    for (int name = 0; name < freq.size(); ++name) {
        canEat[name] = caneat[freq[name].second];
    }
    // eaters 세팅
    for (int person = 0; person < N; ++person) {
        for (int eatable : canEat[person])
            eaters[eatable].push_back(person);
    }
    //canEat의 음식 순서를, 가장 많이 먹을 수 있는 음식순으로 정렬

    for (int i = 0; i < N; ++i) {
        sort(canEat[i].begin(), canEat[i].end(),
            [](int a, int b) {
                return eaters[a].size() > eaters[b].size();
            }
        );
    }

}
