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
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
const int INF = 987654321;

struct Castle {
    double x, y, r;

    Castle(double _x=0, double _y=0, double _r=0) : x(_x), y(_y), r(_r) {}
};


int N;
Castle fortress[100];
vi adj[100];
int dist[100];

void dfs(int here);
void make_tree();
bool isInside(const Castle& a, const Castle& b);
int diameter();
int main()
{
    int t; cin >> t;
    while (t-- > 0)
    {
        cin >> N;

        // reset graph
        for (int i = 0; i < N; ++i)
            vi().swap(adj[i]);
        // get input
        for (int i = 0; i < N; ++i) {
            double x, y, r; cin >> x >> y >> r;
            fortress[i] = Castle(x, y, r);
        }

        make_tree();
        cout << diameter() << endl;
    }
    
}

// b include a? a in b?
bool isInside(const Castle& a, const Castle& b) 
{
    if (a.r >= b.r)
        return false;

    double x_diff = a.x - b.x;
    double y_diff = a.y - b.y;
    double center_dist = sqrt(x_diff * x_diff + y_diff * y_diff);

    if (a.r + center_dist < b.r)
        return true;
    else
        return false;
}


void make_tree()
{
    // 0 : is root 
    // top down 
    vector<bool> connected(N, false);

    // bfs로 만들기
    queue<int> q;
    q.push(0);
    connected[0] = true;
    while ( !q.empty() )
    {
        // parent의 직계자식 찾기
        int parent = q.front(); q.pop();

        for (int child = 0; child < N; ++child)
        {
            if (connected[child]) continue;
            if (!isInside(fortress[child], fortress[parent]) )
                continue;

            // child가 parent안에 있다! 직계인지 확인하자
            // child, parent가 아닌 다른 j가  child를 포함한다면, 직계가 아니다
            bool is_direct_child = true;
            for (int j = 0; j < N; ++j) 
            {
                if (child == j || j == parent) continue;

                if (isInside(fortress[child], fortress[j]) && 
                    isInside(fortress[j], fortress[parent]) ) {
                    is_direct_child = false;
                    break;
                }
            }

            if (is_direct_child) {
                adj[parent].push_back(child);
                adj[child].push_back(parent);
                q.push(child);
                connected[child] = true;
            }
        }
    }

}

void dfs(int here, int d)
{
    dist[here] = d;

    for (int next : adj[here]) {
        if (dist[next] == -1) {
            dfs(next, d + 1);
        }
    }
}

void print_dist()
{
    for (int i = 0; i < N; ++i)
        cout << dist[i] << " ";
    cout << endl;
}
int diameter()
{
    memset(dist, -1, sizeof(dist));
    dfs(0, 0);

    print_dist();



    int start = 0;
    for (int i=0; i<N; ++i) {
        if (dist[start] < dist[i]) {
            start = i;
        }
    }

    memset(dist, -1, sizeof(dist));
    dfs(start, 0); print_dist();

    return *(max_element(dist, dist + N));
}
