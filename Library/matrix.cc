#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
 
typedef tree<int,null_type,less<int>,rb_tree_tag, tree_order_statistics_node_update> indexed_set;
typedef vector<int> vi;
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define sz(v) (int)v.size()
#define ll long long int
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(v) v.begin(),v.end()
#define rep(i, a, b) for(int i = a; i < b; i++)
#define endl "\n"
#define CASE(t) cout<<"Case #"<<t<<": ";
 
#define trarr(a,n) rep(i,0,n) cerr<<a[i]<<" \n"[i==n-1];
#define trmat(g,n,m) rep(i,0,n)rep(j,0,m) cerr<<g[i][j]<<" \n"[i==m-1];
#define tr(...) cerr<<__FUNCTION__<<' '<<__LINE__<<" = ";trace(#__VA_ARGS__, __VA_ARGS__)
template<typename S, typename T> 
ostream& operator<<(ostream& out,pair<S,T> const& p){out<<'('<<p.ff<<", "<<p.ss<<')';return out;}
template<typename T>
ostream& operator<<(ostream& out,vector<T> const& v){
int l=v.size();for(int i=0;i<l-1;i++)out<<v[i]<<' ';if(l>0)out<<v[l-1];return out;}
template<typename T>
void trace(const char* name, T&& arg1){cout<<name<<" : "<<arg1<<endl;}
template<typename T, typename... Args>
void trace(const char* names, T&& arg1, Args&&... args){
const char* comma = strchr(names + 1, ',');cout.write(names, comma-names)<<" : "<<arg1<<" | ";trace(comma+1,args...);}
 
const ld PI = acos(-1);
const ld EPS = 1e-9;
const int inf = 1e9+10;
const ll INF = 1e18+10;
const int P = 1e9+7;
const int N = 2e5+10;

int add(int i, int j) {
	if ((i += j) >= P)
		i -= P;
	return i;
}
int mul(int i, int j) {
	return int((long long) i * j % P);
}

template<class T> struct Matrix {
	T **mat; int a, b;

	Matrix() : a(0), b(0) {}
	Matrix(int a_, int b_) : a(a_), b(b_) {
		int i, j;

		mat = new T*[a];
		for (i = 0; i < a; ++i) {
			mat[i] = new T[b];
			for (j = 0; j < b; ++j)
				mat[i][j] = 0;
		}
	}
	Matrix(const vector<vector<T>>& vt) {
		int i, j;

		*this = Matrix((int) vt.size(), (int) vt[0].size());
		for (i = 0; i < a; ++i)
			for (j = 0; j < b; ++j)
				mat[i][j] = vt[i][j];
	}
	Matrix operator*(const Matrix& m) {
		int i, j, k;

		assert(b == m.a);
		Matrix r(a, m.b);
		for (i = 0; i < a; ++i)
			for (j = 0; j < m.b; ++j)
				for (k = 0; k < b; ++k)
					r.mat[i][j] = add(r.mat[i][j],
						mul(mat[i][k], m.mat[k][j]));
		return r;
	}
	Matrix& operator*=(const Matrix& m) {
		return *this = (*this) * m;
	}
	friend Matrix power(Matrix m, long long p) {
		int i;

		assert(m.a == m.b);
		Matrix r(m.a, m.b);
		for (i = 0; i < m.a; ++i)
			r.mat[i][i] = 1;
		for ( ; p > 0; p >>= 1, m *= m)
			if (p & 1)
				r *= m;
		return r;
	}
};
void solve(){

}
int main(){
    int t = 1;
    cin >> t;
    for(int test = 0; test < t; test++){
        solve();
    }
    return 0;
}
