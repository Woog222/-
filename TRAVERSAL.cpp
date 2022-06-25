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


int N;
int pre_order[100];
int in_order[100];

void printPostOrder(int from, int to, int infrom, int into);
int main()
{
    int t; cin >> t;
    while (t-- > 0)
    {
        cin >> N;
        for (int i = 0; i < N; ++i)
            cin >> pre_order[i];
        for (int i = 0; i < N; ++i)
            cin >> in_order[i];

        printPostOrder(0, N - 1, 0, N - 1);
        cout << '\n';
    }
    
}


void printPostOrder(int from, int to, int infrom, int into)
{
    if (from > to) {
        return;
    }

    int root = pre_order[from];
    int root_idx; // inorder
    for (int i=infrom; ; ++i)
        if (in_order[i] == root) {
            root_idx = i;
            break;
        }

    int left_size = root_idx - infrom;
    int right_size = into - root_idx;

    printPostOrder(from + 1            , from + left_size   , infrom      , root_idx - 1);
    printPostOrder(from + left_size + 1, to                 , root_idx + 1,  into       );
    cout << root << " ";
    return;
}
