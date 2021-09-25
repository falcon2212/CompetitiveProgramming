#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int>> dxy = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
bool valid(int r, int c, int n, int m){
    return (r >=0 && r < n) && (c >=0 && c < m);
}
void bfs(int i, int j, vector<vector<char>>& adj, vector<vector<bool>>& vis){
    queue<vector<int>> q;
    q.push({i, j});
    int n = adj.size();
    vis[i][j] = true;
    while (!q.empty())
    {
        vector<int> u = q.front();q.pop();
        for(int i = 0; i < 4; i++){
            int dx = dxy[i].first;
            int dy = dxy[i].second;
            int newi = u[0]+dx, newj = u[1]+dy;
            if(valid(newi, newj, n, n) && !vis[newi][newj] && adj[newi][newj] == '*'){
                // cout<<i<<" "<<j<<" "<<newi<<" "<<newj<<endl;
                q.push({newi, newj});
                vis[newi][newj] = true;
            }
        }

    }
    
}

void BFS(vector<vector<char>> adj, int n){
    vector<vector<bool>> vis(n, vector<bool>(n, false));
    int cc = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(!vis[i][j] && adj[i][j] == '*'){
                bfs(i, j, adj, vis);
                cc++;
                cout<<i<<" "<<j<<endl;
            }
        }
    }
    cout<<cc<<endl;
}
int main(){
    int n;
    cin >> n;
    vector<vector<char>> adj(n, vector<char>(n, '-'));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> adj[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout<<adj[i][j];
        }
        cout<<endl;
    }
    BFS(adj, n);
    
    return 0;
}