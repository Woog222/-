#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#define el '\n'
using namespace std;
typedef vector<int> vi;

int N;
int indeg[26], outdeg[26], adj[26][26];
vector<string> word[26][26];
deque<int> ans;

void dfs(int here);
bool degreeFail();
void readInput();
int main() {
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        readInput();
        if (!degreeFail()) {
            cout << "IMPOSSIBLE" << el;
            continue;
        }
        // 시작 위치 결정
        ans.clear();
        bool trail = false;
        for (int i = 0; i < 26; ++i) 
            if (indeg[i] < outdeg[i]) {
                dfs(i);
                trail = true;
            }     
        if (!trail) {
            for (int i = 0; i < 26; ++i)
                if (outdeg[i]) {
                    dfs(i);
                    break;
                }
        }
        // 분리되어 있는 경우 전부 
        if (ans.size() <= N) cout << "IMPOSSIBLE" << el;
        else {
            for (int i = 0; i + 1 < ans.size(); ++i) {
                cout << word[ans[i]][ans[i + 1]].back() << " ";
                word[ans[i]][ans[i + 1]].pop_back();
            }
            cout << el;
        }
    } // big while  
} // main

void dfs(int here) {
    for (int i = 0; i < 26; ++i) {
        if (adj[here][i] > 0) {
            adj[here][i]--;
            dfs(i);
        }
    }

    ans.push_front(here);
}

bool degreeFail() {
    int st = 0, fi = 0;
    for (int i = 0; i < 26; ++i) {
        if (indeg[i] == outdeg[i]) continue;
        else if (indeg[i] == outdeg[i] + 1) st++;
        else if (indeg[i] + 1 == outdeg[i]) fi++;
        else return false;
    }

    return (st == 1 && fi == 1) || (st == 0 && fi == 0);
}

void readInput() {
    memset(indeg, 0, sizeof(indeg));
    memset(outdeg, 0, sizeof(outdeg));
    memset(adj, 0, sizeof(adj));
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            word[i][j].clear();
        }
    }
    cin >> N;
    for (int i = 0; i < N; ++i) {
        string s; cin >> s;
        int a = s.front() - 'a';
        int b = s.back() - 'a';
        adj[a][b]++;
        indeg[b]++; outdeg[a]++;
        word[a][b].push_back(s);
    }
}
