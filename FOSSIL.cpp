#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
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
#include <climits>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
const int INF = 987654321;

struct Point {
    double x, y;

    friend bool operator<(const Point& a, const Point& b) {
        return a.x < b.x;
    }
};

struct ConvexHull {

    // 위쪽, 아래쪽 점들 x오름차순으로 넣어둠
    vector<Point> up;
    vector<Point> down;
    // 제일왼쪽, 오른쪽 x
    double lo, hi;

    // lo~hi값만 유효함, 에러처리는 안함 알아서입력잘해
    // x 수직선에서 볼록다각형과 만나는 아래, 위값 리턴 
    // {downy, upy}
    pair<double, double> f(double x) const {
        double upy = -1.0, downy = -1.0;
        // up
        auto iter = lower_bound(up.begin(), up.end(), Point{x,0});
        if (iter->x == x)
            upy = iter->y;
        else {
            Point a = *(iter - 1);
            Point b = *iter;
            upy = (b.y - a.y) / (b.x - a.x) * (x - a.x) + a.y;
        }
        //down
        iter = lower_bound(down.begin(), down.end(), Point{x,0});
        if (iter->x == x)
            downy = iter->y;
        else {
            Point a = *(iter - 1);
            Point b = *iter;
            downy = (b.y - a.y) / (b.x - a.x) * (x - a.x) + a.y;
        }
        return make_pair(downy, upy);
    }

    ConvexHull(const vector<Point>& points)
    {
        lo = min_element(points.begin(), points.end())->x;
        hi = max_element(points.begin(), points.end())->x;

        deque<Point> q = deque<Point>(points.begin(), points.end());
        while (q.front().x != lo) {
            q.push_back(q.front());
            q.pop_front();
        }

        while (q.front().x != hi) {
            down.push_back(q.front());
            q.pop_front();
        }
        down.push_back(q.front());

        q.push_back(down.front());
        sort(q.begin(), q.end());
        while(!q.empty()) {
            up.push_back(q.front());
            q.pop_front();
        }
    }

    void print() {
        for (Point& p : up) {
            printf("(%.2f, %.2f) ", p.x, p.y);
        }
        printf("\n");
        for (Point& p : down) {
            printf("(%.2f, %.2f) ", p.x, p.y);
        }
        printf("\n");
    }

    
};

int N, M;
double fun(const ConvexHull& a, const ConvexHull& b);
int main()
{
    
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cout << fixed;
    cout.precision(10);
    
    int t; cin >> t;
    while (t--)
    {
        cin >> N >> M;
        vector<Point> temp = vector<Point>(N);
        for (int i = 0; i < N; ++i)
            cin >> temp[i].x >> temp[i].y;
        ConvexHull convex1 = ConvexHull(temp);

        temp.resize(M);
        for (int i = 0; i < M; ++i)
            cin >> temp[i].x >> temp[i].y;
        ConvexHull convex2 = ConvexHull(temp);
        cout << fun(convex1, convex2) << '\n';

    }

}
// a, b의  x에서 겹치는 길이 반환 (음수가 반환될 수도 있으나, 호출측에서 잘 처리해야)
double cal(const ConvexHull& a, const ConvexHull& b, double x) {
    auto p = a.f(x);
    auto p2 = b.f(x);

    double up = min(p.second, p2.second);
    double down = max(p.first, p2.first);
    return up - down;
}

double fun(const ConvexHull& a, const ConvexHull& b) 
{
    double left= max(a.lo, b.lo);
    double right= min(a.hi, b.hi);
    if (left >= right) // 좌우로 겹치지 않음
        return 0.0;

    for (int i = 0; i < 100; ++i) {
        double m1 = (left*2  + right) / 3;
        double m2 = (left + right*2 ) / 3;

        if (cal(a, b, m1) < cal(a, b, m2)) {
            left = m1;
        }
        else
            right = m2;
    }

    return max(0.0, cal(a,b, (left + right) / 2));
}
