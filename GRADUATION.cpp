#include <iostream>
#include <cstring>
#define el '\n'
using namespace std;
const int INF = 987654321;

//전공과목수, 들어야 할 과목수, 학기수, 한학기 최대 수강수
int N, K, M, L;
// 전체 수강했을때를 나타내는 상수 마스크 (1<<N)-1
// N 입력 받은 후 초기화
int ALLTAKEN;
// 선수조건 비트마스크 (입력 받으면서 초기화)
int prerequisite[12];
// 열리는 강의들, 비트마스크 (입력받으면서 초기화)
int courses[10];
int cache[10][1 << 12];

int fun(int sem, int taken);
int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--)
    {
        cin >> N >> K >> M >> L;
        ALLTAKEN = (1 << N) - 1;
        //선수 조건
        for (int i = 0; i < N; ++i) {
            int cnt; cin >> cnt;
            prerequisite[i] = 0;
            while (cnt--) {
                int need; cin >> need;
                prerequisite[i] |= (1 << need);
            }
        }
        // 강의들
        for (int i = 0; i < M; ++i) {
            int cnt; cin >> cnt;
            courses[i] = 0;
            while (cnt--) {
                int course; cin >> course;
                courses[i] |= (1 << course);
            }
        }

        memset(cache, -1, sizeof(cache));
        int ans = fun(0, 0);
        if (ans == INF)
            cout << "IMPOSSIBLE\n";
        else
            cout << ans << el;
    }    
}

int findPossibleSet(int sem, int taken) 
{
    // 1. 아직 안들은 강의중에서 열리는 강의
    int temp = ~taken & courses[sem];
    // 2. 과목 i가 선수과목 조건이 만족하고
    // 그게 아직안들었는데 이번에 열린다면 (temp에 있다면)
    int ret = 0;
    for (int i = 0; i < N; ++i) {
        if ((prerequisite[i] & taken) == prerequisite[i]) {
            if (temp & (1 << i))
                ret |= (1 << i);
        }
    }
    return ret;
}

int bitCount(unsigned mask) {
    int ret = 0;
    while (mask) {
        mask &= mask - 1;
        ret++;
    }
    return ret;
}

int fun(int sem, int taken)
{
    if (bitCount(taken) >= K)
        return 0;
    if (sem == M)
        return INF;

    int& ret = cache[sem][taken];
    if (ret != -1)
        return ret;

    ret = INF;
    // 이번학기 강의중, 아직 안들었고 선수과목 만족해서 들을 수 있는 강의들
    int possibleSet = findPossibleSet(sem, taken);
    for (int take = possibleSet; take > 0; take = (take - 1) & possibleSet) {
        // 한학기에 L개넘게 수강불가
        if (bitCount(take) > L) continue;
        ret = min(ret, fun(sem+1, taken | take) + 1);
    }

    // 하나도 안듣는 경우도 처리
    ret = min(ret, fun(sem + 1, taken));
    return ret;
}
