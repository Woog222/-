#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

int N, K;
string fun(const string& formula);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; cin >> t;
    while (t-- > 0)
    {
        string formula; cin >> formula;
        cout << fun(formula) << '\n';
        
    }
}

inline bool is_open(char c) {
    return (c == '(' || c == '{' || c == '[');
}

bool match(char open, char close)
{
    if (open == '(' && close == ')')
        return true;
    else if (open == '{' && close == '}')
        return true;
    else if (open == '[' && close == ']')
        return true;

    return false;
}

string fun(const string& formula)
{
    stack<char> st;
    for (int i = 0; i < formula.length(); ++i) 
    {
        char c = formula[i];
        if (is_open(c)) {
            st.push(c);
            continue;
        }

        if ( st.empty() || !match(st.top(), c) ) 
            return "NO";
        st.pop();

    }

    if (st.empty())
        return "YES";
    else
        return "NO";
}
