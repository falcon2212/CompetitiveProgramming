/* winners never quit and quitters never win.
      #swap                                 */
      
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace std;
using namespace __gnu_pbds;
#pragma GCC optimize ("-O3")
using ll = long long;
using ld = long double;
const ll mod = 1000000007;
const ll inf = 1000000000000000000;
const ll rk = 256;
const ld PI = 3.141592653589793;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

template <typename T>
void make_unique(vector<T>& vec) {
  sort(all(vec));
  vec.erase(unique(all(vec)), vec.end());
}

#define endl '\n'
#define pb push_back
#define mp make_pair
#define vc vector
#define fs first
#define sec second
#define pql priority_queue<ll>
#define pqh priority_queue<ll,vc<ll>,greater<ll>>
#define lb lower_bound
#define ub upper_bound
#define pll pair<ll,ll> 
#define pls pair<ll,string>
#define psl pair<string,ll>
#define plc pair<ll,char>
#define pcl pair<char,ll>
#define pss pair<string,string>
#define all(x) (x).begin(), (x).end()
#define tol(s) transform(s.begin(),s.end(),s.begin(),::tolower);
#define tou(s) transform(s.begin(),s.end(),s.begin(),::toupper);
#define printclock cerr<<"Time : "<<1000*(ld)clock()/(ld)CLOCKS_PER_SEC<<"ms\n";

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << endl;
    err(++it, args...);
}

#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
#define T ll t=0;cin>>t;for(ll test=0;test<t;test++)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


ll nxt() {
    ll TemporaryVariable;
    cin >> TemporaryVariable;
    return TemporaryVariable;
}

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

 
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    //isprime();
    //coeff();
    /*freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);*/
    T
    {
        //cout<<"Case #"<<test+1<<": ";
        string s;
        cin>>s;
        ll n=(ll)s.length();
        ll dp[n][2];
        rep(a,0,n)
        {
            rep(b,0,2)
            {
                dp[a][b]=0;
            }
        }
        if(s[0]=='0')
            dp[0][0]++;
        else if(s[0]=='1')
            dp[0][1]++;
        else
        {
            dp[0][0]++;
            dp[0][1]++;
        }
        rep(a,1,n)
        {
            if(s[a]=='0')
            {
                dp[a][0]=dp[a-1][1]+1;
            }
            else if(s[a]=='1')
            {
                dp[a][1]=dp[a-1][0]+1;
            }
            else
            {
                dp[a][0]=dp[a-1][1]+1;
                dp[a][1]=dp[a-1][0]+1;
            }
        }
        ll ans=0;
        rep(a,0,n)
            ans+=max(dp[a][0],dp[a][1]);
        cout<<ans<<endl;
    }
    printclock;
    return 0;
}