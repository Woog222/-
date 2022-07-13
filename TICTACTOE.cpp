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

int cache[19688];
char player[2] = { 'o', 'x' };

int fun(vector<string>& board, int turn);
int main()
{
    int t; cin >> t;
    while (t--)
    {
        for (int i = 0; i <= 19687; ++i)
            cache[i] = -2;
        vector<string> grid(3);
        for (int i = 0; i < 3; ++i)
            cin >> grid[i];

        int turn = 1;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (grid[i][j] == 'x') turn++;
                else if (grid[i][j] == 'o') turn--;
            }
        }
        turn %= 2;
        int res = fun(grid, turn);
        if (res == 0)
            cout << "TIE\n";
        else {
            cout << (res == 1 ? player[turn] : player[1 - turn]) << '\n';
        }
            
    }
  
}

int bijection(const vector<string>& board)
{
    int ret = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ret *= 3;
            if (board[i][j] == 'o') ret += 1;
            else if (board[i][j] == 'x') ret += 2;
        }
    }
    return ret;
}

bool isFinished(const vector<string>& board, int turn)
{
    char target = turn ? 'x' : 'o';

    for (int i = 0; i < 3; ++i) {
        bool row = true;
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] != target)
                row = false;
        }
        if (row)
            return true;
    }
    for (int j = 0; j < 3; ++j) {
        bool col = true;
        for (int i= 0; i < 3; ++i) {
            if (board[i][j] != target)
                col = false;
        }
        if (col)
            return true;
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] &&
        board[0][0] == target)
        return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] &&
        board[0][2] == target)
        return true;

    return false;

}
//1: can win, 0 : can 무승부, -1 : necessarily defeat
int fun(vector<string> &board, int turn)
{
    if (isFinished(board, 1-turn)) {
        // 승부났으면(꽉찬거말고) 결과 리턴
        // 전판애가 놓고나서 끝난거 니깐 turn기준으로 진거겠지?
        return -1;
    }

    int& ret = cache[bijection(board)];
    if (ret != -2)
        return ret;

    // turn : 0 -> o , 1 -> x
    bool full = true;
    bool candraw = false;
    bool canwin = false;
    bool candefeat = false;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] != '.')
                continue;

            full = false;
            board[i][j] = turn ? 'x' : 'o';
            int res = fun(board, 1 - turn);
            if (res == -1)
                canwin = true;
            else if (res == 0)
                candraw = true;
            else
                candefeat = true;
            board[i][j] = '.';
        }
    }
    if (canwin)
        return ret = 1;
    else if (full || candraw)
        return ret = 0;
    else
        return ret = -1;
}
