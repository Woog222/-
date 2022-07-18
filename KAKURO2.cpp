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

int N; // get input
int board[20][20]; // get input
int groupNum; // init to 0

vi groupSum; // after groupSetting
int horizonGroup[20][20]; // init to -1
int verticalGroup[20][20]; // init to -1
vector<bool> use[800]; // after Groupsetting

void init();
void makeGroup();
void sumSetting();
void show(int arr[][20]);
bool fun(int k);
int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
   
    int t; cin >> t;
    while (t--)
    {
        cin >> N;
        init();
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                cin >> board[i][j];
        makeGroup();
        sumSetting();
        fun(0);
  
    }
}

bool fun(int k)
{
    if (k == N * N) {
        // print and return
        show(board);
        return true;
    }

    int r = k / N;
    int c = k % N;
    if (board[r][c] == 0)
        return fun(k + 1);

    ///////////////////////////////////////// Branching
    int hgrp = horizonGroup[r][c];
    int vgrp = verticalGroup[r][c];
    int hsize = 0, vsize = 0;
    int hmax = 0, vmax = 0;

    int tempr=r, tempc=c;
    while (tempc < N && horizonGroup[tempr][tempc++] == hgrp)
        hsize++;
    tempr = r, tempc = c;
    while (tempr < N && verticalGroup[tempr++][tempc] == vgrp)
        vsize++;

    int cnt = 0;
    for (int num = 9; num >= 1 && cnt < hsize; --num) {
        if (use[hgrp][num]) continue;
        hmax += num;
        cnt++;
    }
    cnt = 0;
    for (int num = 9; num >= 1 && cnt < vsize; --num) {
        if (use[vgrp][num]) continue;
        vmax += num;
        cnt++;
    }

    if (vmax < groupSum[vgrp] || hmax < groupSum[hgrp]) {
        //cout << r << c << " : " << endl;
        //cout << "vmax < groupSum : " << vmax << groupSum[vgrp] << endl;
        //cout << "hmax < groupSum : " << hmax << groupSum[hgrp] << endl;
        return false;
    }

    ///////////////////////////////////////////////////

    if (hsize == 1 || vsize == 1)
    {
        int num = (vsize == 1) ? groupSum[vgrp] : groupSum[hgrp];
        if (hsize==vsize && groupSum[vgrp] != groupSum[hgrp])
            return false;
        if (num >= 10 || num <= 0 )  
            return false;
        if (use[vgrp][num] || use[hgrp][num])
            return false;
        if (hsize > 1 && groupSum[hgrp] <= num)
            return false;
        if (vsize > 1 && groupSum[vgrp] <= num)
            return false;

        use[hgrp][num] = use[vgrp][num] = true;
        groupSum[hgrp] -= num;
        groupSum[vgrp] -= num;

        board[r][c] = num;
        if (fun(k + 1))
            return true;

        use[hgrp][num] = use[vgrp][num] = false;
        groupSum[hgrp] += num;
        groupSum[vgrp] += num;
    }
    else {
        for (int num = 1; num <= 9; ++num) {
            if (use[hgrp][num] || use[vgrp][num])
                continue;
            if (groupSum[hgrp] <= num || groupSum[vgrp] <= num)
                continue;

            use[hgrp][num] = use[vgrp][num] = true;
            groupSum[hgrp] -= num;
            groupSum[vgrp] -= num;

            board[r][c] = num;
            if (fun(k + 1))
                return true;

            use[hgrp][num] = use[vgrp][num] = false;
            groupSum[hgrp] += num;
            groupSum[vgrp] += num;
        }
    }
    return false;
}

void show(int arr[][20])
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << '\n';
    }
}

void sumSetting()
{
    int hints; cin >> hints;
    while (hints--)
    {
        int r, c, dir, sum;
        cin >> r >> c >> dir >> sum;
        r--; c--;

        if (dir == 0) {
            groupSum[horizonGroup[r][c + 1]] = sum;
        }
        else {
            groupSum[verticalGroup[r + 1][c]] = sum;
        }
    }
}

void makeGroup()
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == 1 && horizonGroup[i][j] == -1) {
                int r = i, c = j;
                while (c < N && board[r][c] == 1) {
                    horizonGroup[r][c++] = groupNum;
                }
                groupNum++;
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == 1 && verticalGroup[i][j] == -1) {
                int r = i, c = j;
                while (r < N && board[r][c] == 1) {
                    verticalGroup[r++][c] = groupNum;
                }
                groupNum++;
            }
        }
    }
    for (int i = 0; i < groupNum; ++i)
        use[i].resize(10, false);
    groupSum.resize(groupNum, 0);
    
}

void init() {
    groupNum = 0;
    memset(horizonGroup, -1, sizeof(horizonGroup));
    memset(verticalGroup, -1, sizeof(verticalGroup));
}
