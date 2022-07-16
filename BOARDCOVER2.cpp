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

vector<vector<pii>> blocks;
int N, M, R, C;
vector<string> grid;
int best;
int blockSize;

bool check(int r, int c, int k);
void draw(vector<string>& a, int r, int c, int k, char target);
void fun(int idx, int cnt, int left);
void init();
int makeBlock();
int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    cout.tie(nullptr);

    int t; cin >> t;
    while (t--)
    {
        cin >> N >> M >> R >> C;
        init();
        for (int i = 0; i < N; ++i)
            cin >> grid[i];
        blockSize = makeBlock();

        int left = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (grid[i][j] == '.')
                    left++;
            }
        }
        fun(0, 0, left);
        cout << best << '\n';
    }

    
}
// (0,0)
void fun(int idx, int cnt, int left)
{
    if (idx == N * M) {
        best = max(best, cnt);
        return;
    }

    int possibleMax = left / blockSize;
    if (cnt + possibleMax <= best)
        return;

    int r = idx / M;
    int c = idx % M;

    for (int k = 0; k < blocks.size(); ++k) {
        if (!check(r,c,k))
            continue;

        draw(grid, r, c, k, '#');
        fun(idx + 1, cnt + 1, left - blockSize);
        draw(grid, r, c, k, '.');
    }
    if (grid[r][c] == '#')
        fun(idx + 1, cnt, left);
    else
        fun(idx + 1, cnt, left-1);
}

void draw(vector<string>& a, int r, int c, int k, char target) 
{
    for (pii p : blocks[k]) {
        int nr = r + p.first;
        int nc = c + p.second;
        a[nr][nc] = target;
    }
}

inline bool valid(int r, int c) {
    return r >= 0 && r < N&& c >= 0 && c < M;
}

bool check(int r, int c, int k)
{
    for (pii p : blocks[k]) {
        int nr = r + p.first;
        int nc = c + p.second;
        if (!valid(nr, nc) || grid[nr][nc] == '#')
            return false;
    }
    return true;
}

void init()
{
    best = 0;
    blocks.clear();
    grid.resize(N);
}

int makeBlock()
{
    vector<string> block(R);
    for (int i = 0; i < R; ++i)
        cin >> block[i];
    blocks.resize(4);
    // 0
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (block[i][j] == '#') {
                blocks[0].emplace_back(i, j);
            }
        }
    }
    // 1
    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < R; ++j) {
            if (block[R - j - 1][i] == '#')
                blocks[1].emplace_back(i, j);
        }
    }
    // 2
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (block[R-i-1][C-j-1] == '#') {
                blocks[2].emplace_back(i, j);
            }
        }
    }
    // 3
    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < R; ++j) {
            if (block[j][C - i - 1] == '#')
                blocks[3].emplace_back(i, j);
        }
    }
    //////////////// 반시계
    /*
    vector<string> block2(R);
    for (int i = 0; i < R; ++i) {
        block2[i] = block[R - i - 1];
    }
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (block2[i][j] == '#') {
                blocks[4].emplace_back(i, j);
            }
        }
    }
    // 1
    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < R; ++j) {
            if (block2[R - j - 1][i] == '#')
                blocks[5].emplace_back(i, j);
        }
    }
    // 2
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (block2[R - i - 1][C - j - 1] == '#') {
                blocks[6].emplace_back(i, j);
            }
        }
    }
    // 3
    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < R; ++j) {
            if (block2[j][C - i - 1] == '#')
                blocks[7].emplace_back(i, j);
        }
    }
    */
    sort(blocks.begin(), blocks.end());
    blocks.erase(unique(blocks.begin(), blocks.end()), blocks.end());
    return blocks[0].size();
    /*
    vector<string> show(N, string(M, '.'));
    for (int k = 0; k<blocks.size(); ++k) {
        draw(show, 0, 0, k, '@');
        for (int i = 0; i < N; ++i)
            cout << show[i] << '\n';
        draw(show, 0, 0, k, '.');
    }*/
}
