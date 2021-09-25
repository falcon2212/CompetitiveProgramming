#include<bits/stdc++.h>
using namespace std;
void bfs(int s, vector<int> adj[], vector<bool>& vis){
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();q.pop();
        for(int i = 0; i < adj[u].size(); i++){
            if(!vis[adj[u][i]]){
                q.push(adj[u][i]);
                vis[adj[u][i]] = 1;
            }
        }
    }
    
}

void BFS(vector<int> adj[], int n){
    vector<bool> vis(n, false);
    int cc = 0;
    for(int s = 0; s < n; s++){
        if(!vis[s]){
            bfs(s, adj, vis);
            cc++;
        }
    }
    cout<<cc<<endl;
}
int main(){
    int n, m;
    cin >> n >> m;
    vector<int> adj[n];
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u--;v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    BFS(adj, n);
    
    return 0;
}