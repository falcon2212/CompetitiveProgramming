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

void solve(int _t){
    int n;
    string s;
    cin >> s;
    n = s.length();
    vector<vector<ll>> dp(n+1, vector<ll>(3, 0));
    dp[0][0] = s[0] == '0';
    dp[0][1] = s[0] == '1';
    dp[0][2] = s[0] == '?';
    ll ans = 0;
    rep(i, 1, n){
        if(s[i] == '0'){
            dp[i][1] = 0;
            dp[i][0] = dp[i-1][1]+dp[i-1][2]+1;
        }else if(s[i] == '1'){
            dp[i][0] = 0;
            dp[i][1] = dp[i-1][0]+dp[i-1][2]+1;
        }else{
            dp[i][0] = dp[i-1][1];
            dp[i][1] = dp[i-1][0];
            dp[i][2] = dp[i-1][2]+1;
        }
        ans+=dp[i][0];
        ans+=dp[i][1];
        ans+=dp[i][2];
    }
    cout<<ans+1<<endl;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t = 1;
    cin >> t;
    rep(test, 1, t+1){
        solve(test);
    }
    return 0;
}  