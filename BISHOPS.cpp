#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <cstring>
#include <cmath>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 987654321;

int dr[] = { 1,  1 }; // right down
int dc[] = { 1, -1 }; // left down
int id[2][8][8];
int n;
vector<string> grid(8);
vi graph[64];


inline bool valid(int r, int c) { 
    return r >= 0 && r < n && c >= 0 && c < n;
}
void init(); // reset and get input to make grid
pii  numbering(); // id matching 
void make_graph();
int bi_matching(int v1, int v2);
int main()
{
    cin.tie(nullptr); cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    int t; cin >> t;
    while (t-- > 0)
    {
        cin >> n;
        init(); // reset and make grid
        int v1, v2;
        tie(v1, v2) = numbering(); // vertex setting, and return vertex count
        make_graph();
        cout << bi_matching(v1, v2) << '\n';
    }
  
}

void init() 
{
    memset(id, -1, sizeof(id));
    for (int i = 0; i < 64; ++i)
        graph[i].clear();
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }
}
pii numbering()
{
    int v1, v2;

    int num = 0;
    for (int dir = 0; dir < 2; ++dir) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) 
            {
                if (id[dir][i][j] != -1 || grid[i][j] == '*')
                    continue;

                // not yet numbered and empty space
                int r = i, c = j;
                while (valid(r, c) && grid[r][c] =='.') {
                    id[dir][r][c] = num;
                    r += dr[dir]; c += dc[dir];
                }
                num++;
            }
        }
        if (dir == 0)
            v1 = num;
        else
            v2 = num - v1;
    }

    return make_pair(v1, v2);
}
void make_graph()
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
        { 
            // 1 also possible
            if (id[0][i][j] == -1) continue;

            graph[id[0][i][j]].push_back(id[1][i][j]);
        }
    }
}
bool dfs(vector<bool>& visit, vi &partner, int here)
{
    if (visit[here]) return false;
    visit[here] = true;

    for (int next : graph[here]) {
        if (partner[next] == -1 || dfs(visit, partner, partner[next])) {
            partner[here] = next;
            partner[next] = here;
            return true;
        }
            
    }
    return false;
}
int bi_matching(int v1, int v2)
{
    int ret = 0;
    vi partner(v1 + v2, -1);
    for (int i = 0; i < v1; ++i) {
        vector<bool> visit(v1+v2, false);
        if (dfs(visit, partner, i))
            ret++;
    }

    return ret;
}
