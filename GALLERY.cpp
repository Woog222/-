#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define el '\n'
using namespace std;
typedef vector<int> vi;
const int MAX = 1000;

vector<int> adj[MAX];
int N;
bool on[MAX], visit[MAX];

void readInput() {
    int e; cin >> N >> e;

    for (int i = 0; i < N; ++i) adj[i].clear();
    memset(on, false, sizeof(on));
    memset(visit, false, sizeof(visit));

    while (e--) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
}
// 0 not watched 1 watched 2 installed
int dfs(int here, bool isRoot = false) {
    visit[here] = true;

    int ret = 0;
    for (int there : adj[here]) {
        if (visit[there]) continue;
        int temp = dfs(there);
        if (temp == 0) ret |= 2;
        if (temp == 2) ret |= 1;
    }
    if (ret & 2) {
        on[here] = true;
        return 2;
    }
    else if (ret & 1)  return 1;
    if (isRoot) on[here] = true;
    return 0;
}


int main() {
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        readInput();
        for (int i = 0; i < N; ++i) if (!visit[i]) dfs(i, true);
        int ans = 0;
        for_each(on, on + N, [&](bool b) {ans += b; });
        cout << ans << el;
    }
}
