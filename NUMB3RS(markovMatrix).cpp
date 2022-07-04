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
const int MOD = 10000000;

// 행렬 곱셈 (행렬의 k제곱 구하기 위해)
struct Matrix {
    int n;
    vector<vector<double>> m;
    

    Matrix(const vector<vector<double>> &a) {
        m = a;
        n = m.size();
    }

    friend Matrix operator*(const Matrix& a, const Matrix& b)
    {
        vector<vector<double>> ret(a.n, vector<double>(a.n, 0.0));
        for (int i = 0; i < a.n; ++i) {
            for (int j = 0; j < a.n; ++j) {
                for (int k = 0; k < a.n; ++k) {
                    ret[i][j] += a.m[i][k] * b.m[k][j];
                }
            }
        }

        return Matrix(ret);
    }


    void printMatrix()
    {
        cout << fixed; cout.precision(3);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << m[i][j] << " ";
            }
            cout << '\n';
        }
    }

    static Matrix Identity(int size)
    {
        vector<vector<double>> ret(size, vector<double>(size, 0.0));
        for (int i = 0; i < size; ++i) {
            ret[i][i] = 1.0;
        }

        return Matrix(ret);
    }
};





int N, D, P;

int adj[100][100];
int deg[100];

void init();
void makeGraph();
Matrix makeMarkov();
Matrix matrixPow(const Matrix& a, int k);
int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cout.tie(NULL);

    int t; cin >> t;
    while (t--)
    {
        cin >> N >> D >> P;
        init();
        makeGraph();
        //주어진 마르코프 행렬의 d제곱
        //[d][n] : d일후 n번째마을 확률
        //초기값을 곱하면 바로 결과가 
        Matrix markov = matrixPow(makeMarkov(), D);

        vector<double> temp(N, 0.0);
        temp[P] = 1.0;
        vector<double> ans(N, 0.0);
        for (int i = 0; i < N; ++i) {
            for (int k = 0; k < N; ++k) {
                ans[i] += markov.m[i][k] * temp[k];
            }
        }
        
        int q; cin >> q;
        while (q--) {
            int n; cin >> n;

            cout << fixed; cout.precision(8);
            cout << ans[n] << " ";
            cout << '\n'; 
        }
        

        
    }
}

void init()
{
    memset(deg, 0, sizeof(deg));
    memset(adj, 0, sizeof(adj));
}

void makeGraph()
{
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> adj[i][j];
            if (adj[i][j]) deg[i]++;
        }
    }
}

Matrix makeMarkov()
{
    vector<vector<double>> ret(N, vector<double>(N, 0.0));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (deg[j] == 0) continue;
            ret[i][j] = (double)adj[i][j] / deg[j];
        }
    }
    return Matrix(ret);
}

Matrix matrixPow(const Matrix &a, int k)
{
    if (k == 1)
        return a;
    else if (k == 0)
        return Matrix::Identity(a.n);

    if (k % 2 == 1) {
        return  a* matrixPow(a, k - 1);
    }
    else {
        Matrix temp = matrixPow(a, k / 2);
        return temp * temp;
    }
        
}
