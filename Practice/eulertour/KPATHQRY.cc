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
ostream& operator<<(ostream& out,int* v){for(int i = 0; i < sizeof(v)/sizeof(v[0]); i++) out<<v[i]<<" ";out<<endl; return out;}
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
    int **up; // binary lifting
    int timer;
    int *in, *out;// intime and outtime of a node
    bool *vis; // for forest
    vector<vector<int>> adj;
    vector<int> arr;
    vector<int> linearTree;
    vector<int> depth;
    void DFS(){
        vis = new bool[n]();
        for(int i = 0; i < n; i++){
            if(!vis[i]) dfs(i, i);
        }
    }
    void dfs(int u, int pi){
        vis[u] = 1;
        up[u][0] = pi;
        if(pi!=-1) depth[u] = depth[pi]+1;
        in[u] = timer++;
        linearTree.push_back(arr[u]);
        for(int i = 1; i < logn; i++) up[u][i] = up[up[u][i-1]][i-1];
        for(int v: adj[u])
            if(v!=pi)
                dfs(v, u);            
        linearTree.push_back(arr[u]);
        out[u] = timer++;
    }
    EulerTour(vector<vector<int>>& adj_, vector<int>& arr_):arr(arr_), adj(adj_)
    {
        n = adj.size();
        logn = ceil(log2(n))+1;
        up = new int*[n]();
        for(int i = 0; i < n; i++) up[i] = new int[logn]();
        in = new int[n]();
        out = new int[n]();
        depth.resize(n);
        timer = 0;
        linearTree.resize(2*n);
        DFS();
    }
    bool isAncestor(int u, int v){
        return in[u] <= in[v] && out[u] >= out[v];
    }
    int lca(int u, int v){
        if(isAncestor(u, v)) return u;
        if(isAncestor(v, u)) return v;
        for(int i = logn-1; i >= 0; i--){
            if(!isAncestor(up[u][i], v))
                u = up[u][i];
        }
        return up[u][0];
    }

    int kthParent(int u, int k){
        for(int i = 0; i < logn; i++){
            if(k&(1<<i)) u = up[u][i];
        }
        return u;
    }
};
class Solution{
public:
    void solve(){
        int n;
        cin >> n;
        vector<vector<int>> adj(n);
        vector<int> arr(n);
        rep(i, 0, n-1){
            int u, v;
            cin >> u >> v;
            u--; v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        EulerTour obj(adj, arr);
        int q;
        cin >> q;
        while(q--){
            int k;
            cin >> k;
            vector<pii> fs(k);
            vector<int> v(k);
            int u;
            rep(i,0,k){
                cin >> u;u--;
                v[i] = u;
                fs[i] = {obj.depth[u], u};
            } 
            sort(all(fs));
            reverse(all(fs));
            bool ok = true;
            int curr1 = fs[0].ss, curr2 = -1;
            // tr(fs);
            rep(i, 1, k){
                if(!obj.isAncestor(fs[i].ss, curr1)){
                    if(curr2 == -1) curr2 = fs[i].ss;
                    else{
                        if(!obj.isAncestor(fs[i].ss, curr2)){
                            ok = false;
                            break;
                        }
                        else{
                            int lca = obj.lca(curr1, curr2);
                            // tr(lca, curr1, curr2, v[i], obj.isAncestor(curr2, v[i]));
                            if(obj.isAncestor(fs[i].ss, lca)){
                                ok = false;
                                break;
                            }
                        }
                    } 
                }
            }
            if(curr2!=-1){
                int lca = obj.lca(curr1, curr2);
                // tr(curr1, curr2, lca);
                rep(i, 0, k){
                    if(obj.isAncestor(fs[i].ss, lca) && fs[i].ss!=lca){
                        ok = false;
                        break;
                    }
                }
            }
            // tr(obj.in, obj.out);
            // rep(i, 0, n){
            //     tr(i, obj.in[i], obj.out[i]);
            // }
            // sort(all(fs));
            // bool ok = true;
            // bool inc = true;
            // pii curr = fs[0];
            // rep(i, 1, k){
            //     if(fs[i].ff > fs[i-1].ff && fs[i].ss < fs[i-1].ss){
            //         if(!inc){
            //             ok = false;
            //             break;
            //         }
            //     }else if(inc){
            //         inc = false;
            //     }
            //     if(fs[i-1].ff > fs[i].ff && fs[i-1].ss < fs[i].ss){
            //         if(inc){
            //             ok = false;
            //             break;
            //         }
            //     }else if(!inc){
            //         ok = false;
            //         break;
            //     }
            // }
            // tr(fs);
            if(ok) cout<<"YES";
            else cout<<"NO";
            cout<<endl;
        }
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
