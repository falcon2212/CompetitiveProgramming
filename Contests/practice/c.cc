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
class EulerTour{
    public:
    int n, logn;
    vector<vector<int>> adj;
    vector<vector<int>> up;
    vector<int> depth;
    vector<int> flat_depth;
    int timer;
    vector<int> in, out;
    vector<vector<int>> occurInd;
    vector<bool> vis;
    void DFS(){
        vis.resize(n, false);
        for(int i = n-1; i >=0; i--){
            if(!vis[i]) dfs(i, i);
        }
    }
    void dfs(int u, int pi){
        vis[u] = 1;
        up[u][0] = pi;
        if(u!=pi)
            depth[u] = depth[pi]+1;
        in[u] = timer++;
        flat_depth.push_back(depth[u]);

        for(int i = 1; i < logn; i++) up[u][i] = up[up[u][i-1]][i-1];
        for(int v: adj[u]){
            if(v!=pi){
                dfs(v, u);
            }
        }
        flat_depth.push_back(depth[u]);
        out[u] = timer++;
    }
    EulerTour(vector<vector<int>>& adj_){
        adj = adj_;
        n = adj.size();
        logn = ceil(log2(n))+1;
        up.resize(n);
        for(int i = 0; i < n; i++) up[i].resize(logn);
        depth.resize(n, 0);
        timer = 0;
        occurInd.resize(n+1);
        in.resize(n);
        out.resize(n);
        // tr(n);
        DFS();
        // for(int i = 0; i < flat_depth.size(); i++){
        //     occurInd[flat_depth[i]].push_back(i);
        // }
    }

    int kthParent(int u, int k){
        for(int i = 0; i < logn; i++){
            if(k&(1<<i)) u = up[u][i];
        }
        return u;
    }
    int findOccur(int v, int l, int r){
        int left = lower_bound(occurInd[v].begin(), occurInd[v].end(), l)-occurInd[v].begin();
        int right = lower_bound(occurInd[v].begin(), occurInd[v].end(), r)-occurInd[v].begin();
        if(right >= occurInd[v].size() || occurInd[v][right] > r ) right--;
        return right-left+1;
    }
    int findPcousins(int v, int p){
        if(depth[v] < p) return 0;
        int anc = kthParent(v, p);
        // cout<<anc<<" "<<depth[anc]<<endl;
        int ans = findOccur(depth[anc]+p, in[anc], out[anc])/2-1;
        return ans;
    }


};
void solve(){
    ll n, k, s;
    cin >> n >> k >> s;
    vector<ll> a(n);
    rep(i, 0, n) cin >> a[i];
    int r = 1, l = 0;
    ll csum = a[0];
    vector<vector<int>> adj(n+1);
    while(l < n && r <= n){
        while(r+1 <= n && csum+a[r] <= s){
            csum+=a[r];
            r++;
        }
        // tr(l, r, csum);
        adj[l].pb(r);
        adj[r].pb(l);
        csum-=a[l++];
    }
    EulerTour et(adj);
    // return;
    int lo = 1, hi = n+1;
    while(lo+1 < hi){
        int mid = (lo+hi)/2;
        bool ok = false;
        for(int i = 0; i+mid-1 < n; i++){
            int j = et.kthParent(i, k);
            // tr(i, j);
            if(j-i >= mid){
                ok = true;
                break;
            }
        }
        if(ok)
            lo = mid;
        else
            hi = mid;
    }
    cout<<lo<<endl;
}
int main(){
    int t = 1;
    cin >> t;
    for(int test = 0; test < t; test++){
        solve();
    }
    return 0;
}
