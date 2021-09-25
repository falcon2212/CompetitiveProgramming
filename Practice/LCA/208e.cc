#include<bits/stdc++.h>
using namespace std;
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
        for(int i = 0; i < n; i++){
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
        DFS();
        for(int i = 0; i < flat_depth.size(); i++){
            occurInd[flat_depth[i]].push_back(i);
        }
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
int main(){
    int n;
    cin >> n;
    vector<int> pi(n);
    vector<vector<int>> adj(n, vector<int>());
    for(int i = 0; i < n; i++){
        cin >> pi[i];
        pi[i]--;
        if(pi[i] > -1){
            adj[i].push_back(pi[i]);
            adj[pi[i]].push_back(i);
        }
    }
    EulerTour obj(adj);
    int q;
    cin >> q;
    while(q--){
        int v, p;
        cin >> v >> p;
        cout<<obj.findPcousins(v-1, p)<<endl;
    }
    return 0;
}
// problem link - https://codeforces.com/contest/208/problem/E