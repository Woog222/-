#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <set>
#define el '\n'
using namespace std;
typedef pair<int, int> pii;

int N;

int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    int t;  cin >> t;
    while (t--) {
        cin >> N;
        set<pii> members;

        int ans = 0;
        for (int i = 1; i < N; ++i) {
            int x, y; cin >> x >> y;
            if (members.empty()) {
                members.emplace(x, y);
                ans += members.size();
                continue;
            }
                
            auto iter = members.lower_bound(pii(x, y));
            //본인보다 오른쪽에 있는게 y값까지 나보다 크면, 
            //내 자리는 없다
            if (iter != members.end() && (iter->second) > y) {
                ans += members.size();
                continue;
            }
            //본인보다 x값이 왼쪽에 있으면서 y값도 작은거 지우기
            if (iter != members.begin()) {
                --iter;
                while ( (iter->second) < y) {
                    iter = members.erase(iter);
                    if (iter == members.begin())
                        break;
                    --iter;
                }
            }
            
            members.insert(pii(x, y));
            ans += members.size();
        }

        cout << ans << el;
    }

}
