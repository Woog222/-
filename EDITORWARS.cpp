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
typedef pair<ll, ll> pii;
const int INF = 987654321;



int p[10000];
int Rank[10000];
int enemy[10000];
int Size[10000];
int N, M;


bool ack(int a, int b);
void init();
int FIND(int a);
int UNION(int a, int b);
bool dis(int a, int b);
int partySize();

int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    int t; cin >> t;

    while (t-- > 0)
    {
        cin >> N >> M;
        init();

        bool fail = false;
        int i = 1;
        int spot = 0;
        for (; i <= M; ++i) 
        {
            string com; cin >> com;
            int a, b; cin >> a >> b;

            if (fail) continue;

            if (com == "ACK" && !ack(a, b)) {
                fail = true;
                spot = i;
            }
            if (com == "DIS" && !dis(a, b)) {
                spot = i;
                fail = true;
            }
        }

        if (fail) {
            cout << "CONTRADICTION AT " << spot << '\n';
        }
        else {
            cout << "MAX PARTY SIZE IS " << partySize() << '\n';
        }
    }

}

void init()
{
    for (int i = 0; i < N; ++i)
        p[i] = i;
    for (int i = 0; i < N; ++i)
        Size[i] = 1;
    memset(Rank, 0, sizeof(Rank));
    memset(enemy, -1, sizeof(enemy));
}

int FIND(int a) {
    if (p[a] == a) return a;

    else
        return p[a] = FIND(p[a]);
}
// 변형, 새로운 그룹의 리더 리턴
int UNION(int a, int b)
{
    if (a == -1 || b == -1)
        return max(a, b);

    int pa = FIND(a);
    int pb = FIND(b);

    if (pa == pb)
        return pa;

    // A is larger
    if (Rank[pa] < Rank[pb])
        swap(pa, pb);

    p[pb] = pa;
    Size[pa] += Size[pb];
    if (Rank[pa] == Rank[pb])
        Rank[pa]++;


    return pa;
}



bool ack(int a, int b)
{
    int pa = FIND(a), pb = FIND(b);
    if (enemy[pa] == pb)
        return false;

    int our = UNION(pa, pb);
    int your = UNION(enemy[pa], enemy[pb]);
    enemy[our] = your;
    if (your != -1)
        enemy[your] = our;

    return true;
}

bool dis(int a, int b)
{
    int pa = FIND(a), pb = FIND(b);
    if (pa == pb)
        return false;

    int our = UNION(pa, enemy[pb]);
    int your = UNION(pb, enemy[pa]);

    enemy[our] = your;
    enemy[your] = our;
    return true;
}

int partySize()
{
    int ret = 0;

    for (int i = 0; i < N; ++i) 
    {
        if (p[i] != i) continue;

        // now, it's root!
        // 중복제거
        if (enemy[i] > i) continue;

        int ourSize = Size[i];
        int enemySize = ( enemy[i] == -1 ? 0 : Size[enemy[i]] );

        ret += max(ourSize, enemySize);
    }

    return ret;
}
