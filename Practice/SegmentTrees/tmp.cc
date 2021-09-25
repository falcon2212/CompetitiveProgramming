#include<bits/stdc++.h>
using namespace std;
#define int long long int
int tree[1000] = {0};

void add(int num[], int l, int r, int v, int n){
    for(int i=l-1; i<r; i++){
        num[i] += v;
    }
}

void sumofsquares(int num[], int l, int r, int n){
    int sum=0;
    for(int i=l-1; i<r; i++){
        sum += num[i]*num[i];
    }
    cout << sum << endl;
}

int32_t main(){
    int n, q;
    cin >> n;
    cin >> q;
    int num[n];
    int l,r,v, query;
    for(int i=0; i<n; i++){
        cin >> num[i];
    }
    for(int i=0; i<q; i++){
        cin >> query;
        if(query == 1){
            cin >> l >> r >> v;
            add(num, l, r, v, n);
        }
        if(query == 2){
            cin >> l >> r;
            sumofsquares(num, l, r, n);
        }
    }
}