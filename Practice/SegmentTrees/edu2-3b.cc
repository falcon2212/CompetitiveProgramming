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
struct segment_tree{

    struct node{
        ll zeros, ones;
        ll lazy;
        node(){zeros = ones = 0;lazy = 0;}
        void assign(ll value){
            if(value) ones++;
            else zeros++;
        }
        void combine(node &left, node &right){
            zeros = (left.zeros + right.zeros);
            ones = (left.ones + right.ones);
        }
        // update the sum with the lazy value and also the update lazy value in the node
        void apply(ll value, ll length){
            lazy = 1-lazy;
            swap(zeros, ones);
        }
    };
    int size;
    node* tree;

    // node x covers range [lx, rx)
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
    void push(int x, int lx, int rx){
        if(tree[x].lazy == 0 || rx-lx == 1) return;
        int left = (x<<1)+1, right=left+1, mx = (lx+rx)>>1;
        ll lazy = tree[x].lazy;
        tree[left].apply(lazy, mx-lx);
        tree[right].apply(lazy, rx-mx);
        tree[x].lazy = 0;
    }
    // query for range [l,r)
    ll query(int k, int x, int lx, int rx){
        if(rx-lx == 1){
            if(k == 1)
                return lx;
            return -1;
        }
        push(x, lx, rx);
        int left = (x<<1)+1, right=left+1, midx = (lx+rx)>>1;
        if(k <= tree[left].ones) return query(k, left, lx, midx);
        else return query(k-tree[left].ones, right, midx, rx);
    }
    ll query(int k){
        return  query(k+1, 0, 0, size);
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
    void range_add(int l, int r){
        range_add(l, r, 0, 0, 0, size);
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
int main(){
    int n ,q;
    cin >> n >> q;
    vector<int> a(n,0);
    // for(int i = 0; i < n; i++) cin >> a[i];
    segment_tree st(n, a);    
    while(q--){
        int l, r;
        int tp;
        cin >> tp;
        if(tp == 1){
            int v;
            cin >> l >> r ;
            st.range_add(l, r);
        }else{
            cin >> l;
            cout<<st.query(l)<<endl;

        }
    }
    return 0;
}
/*
8 2
1 0 5 3
2 1 2
*/