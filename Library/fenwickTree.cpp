#include<bits/stdc++.h>
using namespace std;
template <typename T>
class BIT{
    // 1-based indexing
    public:
    int n;
    vector<T> bit;
    void update(int id, T val){
        for(; id < n; id+=id&(-id)){
            bit[id] += val; 
        }
    }
    BIT(int n1, vector<T> a){
        n = n1+1;
        bit.resize(n);
        for(int i = 0; i < n1; i++){
            update(i+1, a[i]);
        }
    }
    T sum(int l){
        T ans = 0;
        for(; l > 0; l -= (l&(-l))){
            ans += bit[l];
        }
        return ans;
    }
    T sum(int l, int r){
        return sum(r)-sum(l-1);
    }

};

int main(){

    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    BIT bit(n, a);
    for(auto i: bit.bit){
        cout<<i<<" ";
    }
    cout<<endl;
    cout<<bit.sum(1, n)<<endl;
    return 0;
}