#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

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

// -------------------------------------------------------------------------------------------------------------------------------------------
#define trarr(a,n) rep(i,0,n) cerr<<a[i]<<" \n"[i==n-1];
#define trmat(g,n,m) rep(i,0,n)rep(j,0,m) cerr<<g[i][j]<<" \n"[i==m-1];
#define tr(...) cerr<<__FUNCTION__<<' '<<__LINE__<<" = ";trace(#__VA_ARGS__, __VA_ARGS__)
template<typename S, typename T> 
ostream& operator<<(ostream& out,pair<S,T> const& p){out<<'('<<p.ff<<", "<<p.ss<<')';return out;}
template<typename S, typename T> 
ostream& operator<<(ostream& out,map<S,T> const& p){for(auto i: p) out<<i<<" "; out<<endl; return out;}
template<typename S, typename T> 
ostream& operator<<(ostream& out,unordered_map<S,T> const& p){for(auto i: p) out<<i<<" "; out<<endl; return out;}
template<typename T>
ostream& operator<<(ostream& out,vector<T> const& v){for(T i: v) out<<i<<" ";out<<endl; return out;}
template<typename T>
ostream& operator<<(ostream& out,set<T> const& v){for(T i: v) out<<i<<" ";out<<endl; return out;}
template<typename T>
ostream& operator<<(ostream& out,unordered_set<T> const& v){for(T i: v) out<<i<<" ";out<<endl; return out;}
template<typename T>
void trace(const char* name, T&& arg1){cout<<name<<" : "<<arg1<<endl;}
template<typename T, typename... Args>
void trace(const char* names, T&& arg1, Args&&... args){
const char* comma = strchr(names + 1, ',');cout.write(names, comma-names)<<" : "<<arg1<<" | ";trace(comma+1,args...);}
// -------------------------------------------------------------------------------------------------------------------------------------------
 
const ld PI = acos(-1);
const ld EPS = 1e-9;
const int inf = 1e9+10;
const ll INF = 1e18+10;
const int P = 1e9+7;
const int N = 2e5+10;
ll nc2(ll n){
    return (n*(n-1))/2;
}
void solve(){
    int n;
    cin >> n;
    map<int, int> s;
    ll cd = 0;
    rep(i, 0, n){
        int tmp;
        cin >> tmp;
        s[tmp]++;
    }
    ll v2 = 0;
    for(auto p: s){
        v2+=nc2(p.ss);
    }
    cout<<2*(nc2(n)-v2)<<endl;
}
int main(){
    int t = 1;
    cin >> t;
    for(int test = 0; test < t; test++){
        solve();
    }
    return 0;
}
