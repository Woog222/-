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
const int MOD = 1000000007;

struct Matrix {
    int n;
    vector<vector<double>> m;

    static Matrix Identity(int size)
    {
        vector<vector<double>> ret(size, vector<double>(size, 0.0));
        for (int i = 0; i < size; ++i) {
            ret[i][i] = 1.0;
        }

        return Matrix(ret);
    }

    Matrix(int _n) : n(_n)
    {
        m.resize(n, vector<double>(n,0.0));
    }

    Matrix(const vector<vector<double>>& v) {
        n = v.size();
        m.resize(n, vector<double>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                m[i][j] = v[i][j];
            }
        }
    }

    friend Matrix operator*(const Matrix& a, const Matrix& b)
    {
        int n = a.n;
        Matrix ret(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    ret.m[i][j] += a.m[i][k] * b.m[k][j];
                }
            }
        }

        return ret;
    }

    Matrix pow(int k) 
    {
        Matrix matrix = *this;
        Matrix ret = Matrix(n);
        for (int i = 0; i < n; ++i)
            ret.m[i][i] = 1.0;

        while (k > 0) {
            if (k % 2 == 1)
                ret = ret * matrix;
            matrix = matrix * matrix;
            k /= 2;
        }

        return ret;
    }

    void print() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << m[i][j] << " ";
            }
            cout << '\n';
        }
         
    }
};

int N; // 곡의 수
int K; // K분 후?
int M; // 좋아하는 곡의 수
int Time[50]; // 곡의 플레이타임
double T[50][50];

Matrix matrixPow(const Matrix& a, int k);
int main()
{
    cin.tie(nullptr); ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cout << fixed;
    
    int t; cin >> t;
    while (t--)
    {
        cin >> N >> K >> M;
        for (int i = 0; i < N; ++i)
            cin >> Time[i];
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                cin >> T[i][j];

        vector<int> query(M); 
        for (int i = 0; i < M; ++i)
            cin >> query[i];

        ///////////////////////
        Matrix w = Matrix(N * 4);
        
        for (int i = 0; i < 3 * N; ++i) {
            w.m[i + N][i] = 1.0;
        }
        // t+1에 song이 틀어질 확률
        for (int song = 0; song < N; ++song) {
            
            // T[prev][song] * t[t+1-len][prev]
            for (int prev = 0; prev < N; ++prev) {
                int len = Time[prev];
                w.m[song][(len - 1)*N + prev] = T[prev][song];
            }
        }
      
        
        Matrix res = w.pow(K);
        vector<double> ans(N, 0.0);
        for (int song = 0; song < N; ++song) {
            for (int before = 0; before < Time[song]; ++before) {
                ans[song] += res.m[before * N + song][0];
            }
        }
        ////////////////////////////
        
        cout.precision(8);
        for (int q : query) {
            cout << ans[q] << " ";
        }
        cout << '\n';
    }
}
