#include<bits/stdc++.h>
using namespace std;
class EulerTour{
public:
    int n, logn, timer;
    vector<vector<int>> adj, up;
    vector<int> in, out;
    vector<int> upd;
    void dfs(int u, int pi){
        up[u][0] = pi;
        in[u] =timer++;
        for(int i = 1; i < logn; i++){
            up[u][i] = up[up[u][i-1]][i-1];
        }
        for(int v: adj[u]){
            if(v!=pi){
                dfs(v, u);
            }
        }
        out[u] = timer++;
    }
    EulerTour(vector<vector<int>>& adj_){
        n = adj_.size();
        adj = adj_;
        logn = ceil(log2(n))+1;
        timer = 0;
        up.resize(n);
        for(int i = 0; i < n; i++) up[i].resize(logn);
        in.resize(n);
        out.resize(n);
        upd.resize(n, 0);
        dfs(0, 0);
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
    int sum(int u, int pi, map<vector<int>, int>& ans){
        int ret = 0;
        for(auto v: adj[u]){
            if(v!=pi){
                int sm = sum(v, u, ans);
                ans[{u, v}] = ans[{v, u}] = sm;
                ret+=sm;
            }
        }
        return ret+upd[u];
    }
};
int main(){
    int n, q;
    cin >> n;
    vector<vector<int>> adj(n);
    vector<vector<int>> edg;
    for(int i = 0; i < n-1; i++){
        int u, v;
        cin >> u >> v;
        u--;v--;
        edg.push_back({u, v});
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    EulerTour obj(adj);
    cin >> q;
    while(q--){
        int u, v;
        cin >> u >> v;
        u--; v--;
        obj.upd[u]++;
        obj.upd[v]++;
        int lca = obj.lca(u, v);
        obj.upd[lca]-=2;
        // cout<<lca<<endl;
    }
    map<vector<int>, int> mp;
    obj.sum(0, 0, mp);
    vector<int> ans;
    for(auto e: edg){
        cout<<mp[e]<<" ";
    }
    cout<<endl;
    return 0;
}