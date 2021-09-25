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

class Solution{
public:
    void solve(){
        int n;
        cin >> n;
        vi a(n);
        rep(i, 0, n){
            cin >>a[i];
        }
        int ans = 0;
        int cnt = 0;
        int curr = a[0];
        for(int i = 0; i+1 < n ; i++){
            if(a[i+1] <= curr){
                ans+=(3-cnt);
                curr = a[i+1];
                cnt = 0;
            }else{
                if(a[i+1]-curr <= 10){
                    curr = a[i+1];
                    cnt++;
                    cnt%=4;
                }else{
                    while(curr < a[i+1] && a[i+1]-curr <= 10 && cnt!=0){
                        curr = curr+10;
                        ans++;
                        cnt = (cnt+1)%4;
                    }
                    if(cnt!=0) curr = a[i+1];
                }
                if(cnt == 0){
                    i++;
                    curr = a[i];
                } 
            }
        }
        cout<<ans<<endl;
    }
};
int main(){
    int t = 1;
    cin >> t;
    for(int test = 0; test < t; test++){
        Solution inst;
        // CASE(test+1);
        inst.solve();
    }
    return 0;
}
