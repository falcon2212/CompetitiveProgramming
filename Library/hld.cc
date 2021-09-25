#include<bits/stdc++.h>
using namespace std;
#define ll long long int
struct segment_tree{

    struct node{
        ll sum;
        ll lazy;
        node(){sum = 0;lazy = 0;}
        void assign(ll value){
            sum = value;
        }  
        // The merge function that merges children to parent
        void combine(node &left, node &right){
            sum = (left.sum + right.sum);
        }
        // update the sum in the with the lazy value and also the update lazy value in the node
        void apply(ll value, ll length){
            lazy += value;
            sum += value*(length);
        }
    };
    int size;
    node* tree;

    // node x covers range [lx, rx)
    void init(int n, vector<int>& a){
        size = 1;
        while(size < n) size*=2;
        tree = new node[size<<1]();
        build(a, 0, 0, size);
    }
    segment_tree(){}
    segment_tree(int n, vector<int>& a){
        size = 1;
        while(size < n) size*=2;
        tree = new node[size<<1]();
        build(a, 0, 0, size);
    }
    void build(vector<int>& a, int x, int lx, int rx){
        if(rx-lx == 1){
            if(lx < (int)a.size()) tree[x].assign(a[lx]); 
            return;
        } 
        int left = (x<<1)+1, right=left+1, midx = (lx+rx)>>1;
        build(a, left, lx, midx);
        build(a, right, midx, rx);
        tree[x].combine(tree[left], tree[right]); 
    }
    // Pushing the lazy values to the children
    void push(int x, int lx, int rx){
        if(tree[x].lazy == 0 || rx-lx == 1) return;
        int left = (x<<1)+1, right=left+1, mx = (lx+rx)>>1;
        ll lazy = tree[x].lazy;
        tree[left].apply(lazy, mx-lx);
        tree[right].apply(lazy, rx-mx);
        tree[x].lazy = 0;
    }
    // query for range [l,r)
    ll query(int l, int r, int x, int lx, int rx){
        if(lx >= r || l >= rx) return 0;
        if(lx >= l && rx <= r) return tree[x].sum;
        push(x, lx, rx);
        int left = (x<<1)+1, right=left+1, midx = (lx+rx)>>1;
        return (query(l, r, left, lx, midx) + query(l, r, right, midx, rx));
    }
    // query for range [l,r)
    ll query(int l, int r){
        return  query(l, r, 0, 0, size);
    }
    void range_add(int l, int r, int value, int x, int lx, int rx){
        if(lx >= r || l >= rx) return;
        if(lx >= l && rx <= r){
            tree[x].apply(value, rx-lx);
        } 
        else{
            int left = (x<<1)+1, right=left+1, midx = (lx+rx)>>1;
            push(x, lx, rx);
            range_add(l, r, value, left, lx, midx);
            range_add(l, r, value, right, midx, rx);
            tree[x].combine(tree[left], tree[right]);
        }
    }
    void range_add(int l, int r, int value){
        range_add(l, r, value, 0, 0, size);
    }
    void update(int index, int value, int x, int lx, int rx){
        if(rx-lx == 1 && lx == index){
            tree[x].assign(value);
            return;
        }
        int left = (x<<1)+1, right=left+1, midx = (lx+rx)>>1;
        if(index < midx) update(index, value, left, lx, midx);
        else update(index, value, right, midx, rx);
        tree[x].combine(tree[left], tree[right]); 
    }
    void update(int index, int value){
        update(index, value, 0, 0, size);
    }
};

class HLD{
    public:
    int n, logn;
    vector<int> chain, chainHead, pos, splChild; 
    vector<int> lvl, subTreeSz;
    vector<int> baseArr, val;
    segment_tree stree;
    int chainNo, posIndx;

    vector<vector<int>> adj, up;
    
    HLD(int n_, vector<vector<int>>& adj_){
        n = n_; logn = (int)ceil(log2(n));
        adj = adj_;
        up.resize(n);
        for(int i = 0; i < n; i++) up[i].resize(logn, -1);
        subTreeSz.resize(n, 0); lvl.resize(n, 0);
        splChild.resize(n -1); chain.resize(n, -1);
        chainHead.resize(n, -1); pos.resize(n);
        chainNo = 0; posIndx = 0;

        dfs(0, -1); hld(0, -1);
        stree.init(n, baseArr);
    }

    int dfs(int u, int pi){
        if(pi != -1) lvl[u] = lvl[pi]+1;
        up[u][0] = pi;
        for(int l = 1; l < logn; l++) up[u][l] = up[up[u][l-1]][l-1];
        int sz = 1, splSize = 0;
        splChild[u] = -1;
        for(int v: adj[u]){
            if(v!=pi){
                int szChild=dfs(v, u);
                if(splSize < szChild) splSize = szChild, splChild[u] = v;
                sz+=szChild;
            }
        }
        return subTreeSz[u] = sz;
    }
    int LCA(int u, int v){
        if(lvl[u] < lvl[v]) swap(u, v);
        int diff = lvl[u]-lvl[v];
        for(int i = 0; i < logn; i++) if((diff>>i)&1) u = up[u][i];
        if(u!=v){
            for(int i = logn-1; i >= 0; i--){
                if(up[u][i]!=up[v][i]) u = up[u][i], v = up[v][i];
            }
            u = up[u][0];
        }
        return u;
    }

    int hld(int u, int pi){
        chain[u] = chainNo; pos[u] = posIndx++;
        baseArr[posIndx] = val[u];
        int sc = splChild[u];
        if(sc != -1) hld(sc, u);

        for(int nc: adj[u]){
            if(nc == sc || nc == pi) continue;
            chainHead[++chainNo] = nc;
            hld(nc, u);
        }
    }
    ll queryChain(int u, int v){ // v is ancestor of u
        int uchain, vchain = chain[v];
        ll ans = 0;
        while(1){
            uchain = chain[u];
            if(uchain ==  vchain){
                ans = ans+stree.query(pos[v], pos[u]+1);    
                break;
            }
            ans = ans+stree.query(pos[chainHead[u]], pos[u]+1);
            u = up[chainHead[u]][0];
        } 
        return ans;
    }
    void updateChain(int u, int v, int value){ // v is ancestor of u
        int uchain, vchain = chain[v];
        while(1){
            uchain = chain[u];
            if(uchain ==  vchain){
                stree.range_add(pos[v], pos[u]+1, value);    
                break;
            }
            stree.range_add(pos[chainHead[u]], pos[u]+1, value);
            u = up[chainHead[u]][0];
        } 
    }
    int pathQuery(int u, int v){
        int lca = LCA(u, v);
        return queryChain(u, lca)+queryChain(v, lca);
    }
};

int main(){
    return 0;
}