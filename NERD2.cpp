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
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
const int INF = 987654321;


int N;



int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int t; cin >> t;
    while (t-- > 0)
    {
        cin >> N;
        set<pii> bst;

        int ans = 0;
        for (int i = 0; i < N; ++i) {
            int p, q;
            cin >> p >> q;
            auto iter = bst.lower_bound(pii(p, q));
            // empty
            if ( bst.size() == 0 ) {
                bst.emplace(p, q);
            }
            // 본인 p가 제일 크다
            // 본이보다 q도 작은사람 다 삭제한다
            else if (iter == bst.end()) 
            {
                auto riter = bst.rbegin();
                while (riter != bst.rend() && riter->second < q) {
                    bst.erase(--riter.base());
                }
                bst.emplace(p, q);
            }
            // 본인보다 p가 큰 사람이 있다.
            else
            {
                // 그 사람보다 q도 작다면, 난 탈락이므로
                // 그 사람보다 q는 커야된다
                // 그게 만족되면, 본인보다 작으면서 q도작은사람 지운다.
                if (iter->second < q) {

                    if (iter != bst.begin()) {
                        --iter;
                        while (true) 
                        {
                            if (iter->second > q)
                                break;
                            
                            if (iter == bst.begin()) {
                                bst.erase(iter);
                                break;
                            }
                            else {
                                set<pii>::iterator niter = iter;
                                niter--;
                                bst.erase(iter);
                                iter = niter;
                            }
                        }
                    }

                    bst.emplace(p, q);
                }
            }
            
            // 정답엔 bst사이즈
            ans += bst.size();
        }
        cout << ans << '\n';
    }
}
