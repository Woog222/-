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
const int MOD = 1000000007;

char cache[1 << 25];
vector<pii> blocks[6];


int makeBoard();
void makeBlock();
int fun(int board);
int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    
    makeBlock();
    int t; cin >> t;
    while (t--)
    {
        memset(cache, -1, sizeof(cache));
        int board = makeBoard();

        if (fun(board))
            cout << "WINNING\n";
        else
            cout << "LOSING\n";
    }


}

int makeBoard()
{
    int ret = 0;
    vector<string> board(5);
    for (int i = 0; i < 5; ++i)
        cin >> board[i];

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board[i][j] == '#')
                ret |= (1 << (i * 5 + j));
        }
    }

    return ret;
}

void makeBlock()
{
    blocks[4] = { pii(1,0) };
    blocks[5] = { pii(0,1) };
    blocks[0] = { pii(1,0), pii(1,1) };
    blocks[1] = { pii(0,1), pii(1,1) };
    blocks[2] = { pii(1,0), pii(1,-1)};
    blocks[3] = { pii(1,0), pii(0,1) };
}

inline bool valid(int r, int c) {
    return r >= 0 && r < 5 && c >= 0 && c < 5;
}

int fun(int board)
{
    char& ret = cache[board];
    if (ret != -1)
        return ret;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) 
        {
            int k = i * 5 + j;
            if (board & (1 << k) ) continue;

            for (vector<pii>& block : blocks) 
            {
                bool ok = true;
                for (pii p : block) {
                    int nr = i + p.first, nc = j + p.second;
                    if (!valid(nr, nc) || board&(1<<(nr*5+nc)) ) {
                        ok = false; break;
                    }
                }

                if (ok) 
                {
                    for (pii p : block) {
                        int nr = i + p.first, nc = j + p.second;
                        board |= (1 << (nr * 5 + nc));
                    }
                    board |= 1 << k;

                    if (fun(board)==0)
                        return ret= 1;

                    for (pii p : block) {
                        int nr = i + p.first, nc = j + p.second;
                        board &= ~(1 << (nr * 5 + nc));
                    }
                    board &= ~(1 << k);
                }
            } // for block
        } // for j
    } // for i

    return ret = 0;
}
