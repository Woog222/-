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

int c[16]; // 0 ~ 3, 0이 12시
vi swtch[10];

void make_switch();
int fun(int idx);
int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);

    make_switch();


    int t; cin >> t;
    while (t-- > 0)
    {
        for (int i = 0; i < 16; ++i) {
            cin >> c[i];
            c[i] = (c[i] / 3) % 4; // 0~3으로 압축 
        }
            
        cout << fun(0) << '\n';
    }
}

void make_switch()
{
    swtch[0] = { 0,1,2 };
    swtch[1] = { 3,7,9,11 };
    swtch[2] = { 4,10,14,15 };
    swtch[3] = { 0,4,5,6,7 };
    swtch[4] = { 6,7,8,10,12 };
    swtch[5] = { 0,2,14,15 };
    swtch[6] = { 3,14,15 };
    swtch[7] = { 4,5,7,14,15 };
    swtch[8] = { 1,2,3,4,5 };
    swtch[9] = { 3,4,5,9,13 };
}

int fun(int idx)
{
    if (idx == 10) 
    {
        bool ok = true;
        for (int i = 0; i < 16; ++i) {
            if (c[i] % 4 != 0) {
                ok = false; break;
            }
        }
        if (ok)
            return 0;
        else
            return -1;
    }

    int ret = INF;

    // 0~3번 클릭하는 경우 브루트포스
    for (int click = 0; click < 4; ++click)
    {
        for (int what : swtch[idx]) 
            c[what] += click;
        
        int temp = fun(idx + 1);
        if (temp >= 0) // not -1
            ret = min(ret, click + temp);

        for (int what : swtch[idx]) 
            c[what] -= click;
    }

    if (ret == INF)
        ret = -1;
    return ret;
}
