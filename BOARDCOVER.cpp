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
#include <ctime>
#include <climits>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
const int INF = 987654321;

int dr[][3] = {
    {0,0,1}, {0,1,1}, {0,0,-1}, {0,-1,-1}, {0,0,-1}, {0,0,-1},
    {0,0,-1}, {0,1,1}, {0,0,1}, {0,-1,-1}, {0,0,1}, {0,0,1}
};
int dc[][3] = {
    {0,-1,-1}, {0,0,1}, {0,1,1}, {0,0,-1}, {0,-1,0}, {0,1,0},
    {0,-1,-1}, {0,0,-1}, {0,1,1}, {0,0,1}, {0,-1,0}, {0,1,0}
};



string grid[20];
int N, M;
bool covered[20][20];

void init();
int fun(int);


int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);

    int t; cin >> t;

    while (t-- > 0)
    {
        cin >> N >> M;
        init();
        for (int i = 0; i < N; ++i)
            cin >> grid[i];

        cout << fun(0) << '\n';
    }
}

void init() {
    memset(covered, false, sizeof(covered));
}
inline bool valid(int r, int c)
{
    return r >= 0 && r < N && c >= 0 && c < M;
}

// r, c를 p번 모양으로 덮을 수 있는가?
bool check(int r, int c, int p) 
{
    for (int k = 0; k < 3; ++k) {
        int nr = r + dr[p][k];
        int nc = c + dc[p][k];
        // 밖이거나 ,검은칸이거나 ,이미 덮였으면
        if (!valid(nr, nc) || grid[nr][nc] == '#' || covered[nr][nc])
            return false;
    }
    return true;
}


void print()
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == '#')
                cout << '#';
            else if (covered[i][j])
                cout << 'O';
            else
                cout << '.';
        }
        cout << '\n';
    }
}






int fun(int k)
{
    int r = k / M;
    int c = k % M;
    if (r == N && c == 0) {
        // if all covered!!
        return 1;
    }
    if (grid[r][c] == '#' || covered[r][c]) {
        return fun(k + 1);
    }
        

    // need to cover this
    int ret = 0;
    for (int p = 0; p < 12; ++p) {
        // (r,c)를 p번 유형으로 덮을 수 있는지?
        if (!check(r, c, p)) continue;
        //가능하니깐 덮자

        for (int q = 0; q< 3; ++q) {
            int nr = r + dr[p][q];
            int nc = c + dc[p][q];
            covered[nr][nc] = true;
        }
        ret += fun(k + 1);
        //다시 지우고
        for (int q = 0; q < 3; ++q) {
            int nr = r + dr[p][q];
            int nc = c + dc[p][q];
            covered[nr][nc] = false;
        }
    }

    return ret;
}
