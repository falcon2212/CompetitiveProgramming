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
            cin >> l >> r;
            cout<<st.query(l, r)<<endl;

        }
    }
    return 0;
}
/*
8 2
1 0 5 3
2 1 2
*/