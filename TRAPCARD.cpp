#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <cstring>
#include <cmath>
#include <iomanip>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 987654321;

int dr[] = { 0,  0, 1, -1 }; 
int dc[] = { 1, -1, 0,  0 }; 
int id[20][20];
int H, W;
int v1, v2; // each vertex num
vector<string> grid(20);
int graph[400][400];


inline bool valid(int r, int c) { 
    return r >= 0 && r < H && c >= 0 && c < W;
}
void init(); // reset and get input to make grid
pii  numbering(); // id matching 
void make_graph();
int bi_matching(vi& partner); // partner cnt return at the same time setting partner
void change_grid(vi& partner); // print ans based on bi matching result
int main()
{
    cin.tie(nullptr); cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    int t; cin >> t;
    while (t-- > 0)
    {
        cin >> H >> W;
        init(); // reset and make grid
        
        tie(v1, v2) = numbering(); // vertex setting, and return vertex count
        make_graph();
        // bi_partition
        vi partner(400, -1);
        int matched_num = bi_matching(partner);
        // cal and print
        cout << (v1 + v2 - matched_num) << '\n';
        change_grid(partner);
    }
  
}

void init() 
{
    memset(graph, 0, sizeof(graph));
    memset(id, -1, sizeof(id));
    for (int i = 0; i < H; ++i) {
        cin >> grid[i];
    }
}
pii numbering()
{
    int num_0 = 0;
    int num_1 = 200;

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) 
        {
            if (grid[i][j] == '#') continue;

            if ((i + j) % 2 == 0) {
                id[i][j] = num_0++;
            }
            else {
                id[i][j] = num_1++;
            }

        }
    }
    return make_pair(num_0, num_1 - 200);
}
void make_graph()
{
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (grid[i][j] == '#' || (i + j) % 2 == 1) continue;

            // valid space, 0
            for (int k = 0; k < 4; ++k) {
                int ni = i + dr[k];
                int nj = j + dc[k];
                if (valid(ni, nj) && grid[ni][nj] != '#') {
                    graph[ id[i][j] ][ id[ni][nj] ] = 1;
                }
            }
        }
    }
}
bool dfs(vector<bool>& visit, vi &partner, int here)
{
    if (visit[here]) return false;
    visit[here] = true;

    for (int i = 0; i < v2; ++i) {
        if (graph[here][i + 200] == 0) continue;

        int next = 200 + i;
        
        if (partner[next] == -1 || dfs(visit, partner,  partner[next])) {
            partner[here] = next;
            partner[next] = here;
            return true;
        }
            
    }
    return false;
}
int bi_matching(vi& partner)
{
    int ret = 0;
    for (int i = 0; i < v1; ++i) {
        vector<bool> visit(400, false);
        if (dfs(visit, partner , i))
            ret++;
    }

    return ret;
}
void change_grid(vi& partner)
{
    // a all, and not matched b are selected initially
    vi chosen(400, false);
    for (int i = 0; i < v1; ++i) {
        chosen[i] = true;
    }
    for (int j = 0; j < v2; ++j) {
        if (partner[j + 200] == -1)
            chosen[j + 200] = true;
    }

    while (true)
    {
        bool changed = false;
        for (int i = 0; i < v1; ++i) {
            for (int j = 0; j < v2; ++j) {
                if ( chosen[i] && chosen[200 + j] && graph[i][200+j] ) {
                    //assert( partner[i] != -1 );
                    chosen[partner[i]] = true;
                    chosen[i] = false;
                    changed = true;
                }
            }
        }

        if (changed == false)
            break;
    }

    //Print Grids
    
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) 
        {
            //#
            if (id[i][j] == -1) {
                cout << grid[i][j];
                continue;
            }
            // chosen or not
            if ( chosen[id[i][j]] ) {
                cout << '^';
            }
            else
                cout << '.';
            
        }
        cout << '\n';
    }
    
}
