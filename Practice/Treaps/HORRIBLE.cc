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
// #define sz(v) (int)v.size()
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
typedef struct node{
    int val,prior,size;
    ll sum, v;
    struct node *l,*r;
}node;
typedef node* pnode;
int sz(pnode t){
    return t?t->size:0;
}
int sum(pnode t){
    return t?t->sum:0;
}
void upd_sz(pnode t){
    if(t){
        t->size = sz(t->l)+1+sz(t->r);  
        t->sum = sum(t->l)+sum(t->r)+t->v;
    }
}
void split(pnode t,pnode &l,pnode &r,int key){
    if(!t)l=r=NULL;
    else if(t->val<=key)split(t->r,t->r,r,key),l=t;//elem=key comes in l
    else split(t->l,l,t->l,key),r=t;
    upd_sz(t);
}
void merge(pnode &t,pnode l,pnode r){
    if(!l || !r)t=l?l:r;
    else if(l->prior > r->prior)merge(l->r,l->r,r),t=l;
    else merge(r->l,l,r->l),t=r;
    upd_sz(t);
}
void insert(pnode &t,pnode it){
    if(!t) t=it;
    else if(it->prior>t->prior)split(t,it->l,it->r,it->val),t=it;
    else insert(t->val<=it->val?t->r:t->l,it);
    upd_sz(t);
}
void erase(pnode &t,int key){
    if(!t)return;
    else if(t->val==key){pnode temp=t;merge(t,t->l,t->r);free(temp);}
    else erase(t->val<key?t->r:t->l,key);
    upd_sz(t);
}
void unite (pnode &t,pnode l, pnode r) {
    if (!l || !r) return void(t = l ? l : r);
    if (l->prior < r->prior) swap (l, r);
    pnode lt, rt;
    split (r,lt, rt,l->val);
    unite (l->l,l->l, lt);
    unite (l->r,l->r, rt);
    t=l;upd_sz(t);
}
pnode init(int val, int V){
    pnode ret = (pnode)malloc(sizeof(node));
    ret->val=val;ret->size=1;ret->prior=rand();ret->l=ret->r=NULL;ret->sum =0; ret->v = V;
    return ret;
}
void solve(){
    int n, q;
    cin >> n >> q;
    pnode treap=nullptr;
    vector<pnode> a;
    for(int i = 0; i < n+1; i++){
        a.push_back(init(i+1, 0));
    }
    while(q--){
        int tp;
        cin >> tp;
        int l, r;
        if(tp == 0){
            int v;
            cin >> l >> r >> v;
            a[l-1]->v+=v;
            a[r]->v-=v;
            insert(treap, a[l-1]);
            insert(treap, a[r]);

        }else{
            cin >> l >> r;
            pnode lt, rt;
            split(treap, lt, rt, l-1);
            // lt = nullptr;
            pnode fin;
            split(rt, lt, fin, r+1);
            cout<<lt->sum<<endl;
            // print the sum 
        }
    }
}
int main(){
    int t = 1;
    cin >> t;
    for(int test = 0; test < t; test++){
        solve();
    }
    return 0;
}
