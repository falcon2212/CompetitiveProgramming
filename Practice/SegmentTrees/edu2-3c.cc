#include"bits/stdc++.h"
// #include "ext/pb_ds/assoc_container.hpp"
// using namespace __gnu_pbds;
using namespace std;
 
// typedef tree<int,null_type,less<int>,rb_tree_tag, tree_order_statistics_node_update> indexed_set;
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
        ll sum;
        ll lazy;
        vector<pii> v;
        vector<int> pref_ind_min;
        node(){
            sum = 0;lazy = 0;
            v = {};
            pref_ind_min = {};
        }
        void assign(ll value, int index){
            sum = value;
            v.push_back({value, index});
            pref_ind_min.pb(index);
        }
        void combine(node &left, node &right, int length){
            sum = (left.sum + right.sum);
            v = left.v;
            for(auto p: right.v) v.push_back(p);
            sort(all(v));
            pref_ind_min.assign(length, INT_MAX);
            pref_ind_min[length-1] = v[length-1].ss;
            for(int i = length-2; i >= 0; i--){
                pref_ind_min[i] = min(pref_ind_min[i+1], v[i].ss);
            }
        }
        // update the sum with the lazy value and also the update lazy value in the node
        void apply(ll value, int lx, int rx){
            int length = rx-lx;
            lazy += value;
            sum += value*(length);
            for(int i = lx; i < rx; i++) v[i-lx] = {v[i-lx].ff+value, v[i-lx].ss};
            // sort(all(v));
            // pref_ind_min[length-1] = v[length-1].ss;
            // for(int i = length-2; i >= 0; i--){
            //     pref_ind_min[i] = min(pref_ind_min[i+1], v[i].ss);
            // }
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
            tree[x].assign(0, lx); 
            return;
        } 
        int left = (x<<1)+1, right=left+1, midx = (lx+rx)>>1;
        build(a, left, lx, midx);
        build(a, right, midx, rx);
        tree[x].combine(tree[left], tree[right], rx-lx); 
    }
    void push(int x, int lx, int rx){
        if(tree[x].lazy == 0 || rx-lx == 1) return;
        int left = (x<<1)+1, right=left+1, mx = (lx+rx)>>1;
        ll lazy = tree[x].lazy;
        tree[left].apply(lazy, lx, mx);
        tree[right].apply(lazy, mx, rx);
        tree[x].lazy = 0;
    }
    ll check(int x, int lx, int rx, int value){
        int lo = 0, hi = rx-lx-1;
        if(tree[x].v[hi].ff < value) return INT_MAX;
        while(lo+1 < hi){
            int mid = (lo+hi)/2;
            // tr(lo,hi,mid, tree[x].v[mid], value);
            if(tree[x].v[mid].ff >= value) hi = mid;
            else lo = mid;
        }
        return tree[x].pref_ind_min[hi];
    }
    // query for range [l,r)
    ll query(int v, int l, int r, int x, int lx, int rx){
        if(lx >= r || l >= rx) return INT_MAX;
        if(lx >= l && rx <= r){
            // tr(x, tree[x].v, tree[x].sum, tree[x].lazy);
            return check(x, lx, rx, v);
        };
        push(x, lx, rx);
        int left = (x<<1)+1, right=left+1, midx = (lx+rx)>>1;
        return min(query(v, l, r, left, lx, midx), query(v, l, r, right, midx, rx));
    }
    // query for range [l,r)
    ll query(int v, int l, int r){
        return  query(v, l, r, 0, 0, size);
    }
    void range_add(int l, int r, int value, int x, int lx, int rx){
        if(lx >= r || l >= rx) return;
        if(lx >= l && rx <= r){
            tree[x].apply(value, lx, rx);
        } 
        else{
            int left = (x<<1)+1, right=left+1, midx = (lx+rx)>>1;
            push(x, lx, rx);
            range_add(l, r, value, left, lx, midx);
            range_add(l, r, value, right, midx, rx);
            tree[x].combine(tree[left], tree[right], rx-lx);
        }
    }
    void range_add(int l, int r, int value){
        range_add(l, r, value, 0, 0, size);
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
            cin >> l >> r >> v;
            st.range_add(l, r, v);
        }else{
            int x;
            cin >> x >> l;
            int ret = st.query(x, l, n);
            if(ret == INT_MAX) 
                cout<<-1;
            else
                cout<<st.query(x, l, n);
            cout<<endl;

        }
    }
    return 0;
}
/*
8 2
1 0 5 3
2 1 2
*/