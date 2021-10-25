//================code===================//

#ifndef OHSOLUION
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#endif

#include <bits/stdc++.h>

#define ci(t) cin>>t
#define co(t) cout<<t
#define LL long long
#define ld long double
#define fa(i,a,b) for(int i=a;i<b;++i)
#define fd(i,a,b) for(int i=a;i>b;--i)
#define setp tuple<LL,LL,LL>
#define setl pair<LL,LL>
#define seti pair<int,int>
#define VL vector<LL>
#define VI vector<int>
#define eps 0.000000001
#define LLL __int128_t

using namespace std;


LL gcd(LL a, LL b)
{
	if (!(a && b)) return max(a, b);
	return a % b ? gcd(b, a % b) : b;
}

#ifdef OHSOLUTION
#define ce(t) cerr << t
#define AT cout << "\n=================ANS=================\n"
#define AE cout << "\n=====================================\n"
#define DB(a) cout << __LINE__ << ": " << #a << " = " << (a) << endl;
#else
#define AT
#define AE
#define ce(t)
#define DB(a)
#endif

pair <int, int> vu[9] = { {-1,0},{0,-1},{-1,0} ,{0,-1},{1,1}, {1,-1} , {-1,1},{-1,-1},{0,0} }; //RDLU EWSN
//mt19937 rng((unsigned int)chrono::steady_clock::now().time_since_epoch().count());


template<typename T, typename U> void ckmax(T& a, U b) { a = a < b ? b : a; }
template<typename T, typename U> void ckmin(T& a, U b) { a = a > b ? b : a; }
struct gcmp { bool operator()(LL a, LL b) { return a < b; } bool operator()(setl& a, setl& b) { return a.second < b.second; } };
struct lcmp { bool operator()(LL a, LL b) { return a > b; } bool operator()(setl& a, setl& b) { return a.second > b.second; } };

const int max_v = 1e5 + 7;
const int max_k = 5e2 + 7;
const int bsz = 27;
const int INF = 0x3f3f3f3f;
const LL LNF = 0x3f3f3f3f3f3f3f3f;
const LL mod = 1e9 + 9;//998244353;// 
template<typename T, typename U> void MOD(T& a, U b) { a += b;if(a<0) a+=mod; if (a >= mod) a -= mod; };

struct PST
{
    struct Node
    {
        int l=-1;int r=-1;
        LL v = 0;
    };
    
    vector<Node> vt;
    vector<int> root;
    int sz;
    
    void init(int n)
    {
        vt.clear();
        root.clear();
        root.push_back(1);
        
        sz=1;
        while(sz<=n) sz<<=1;
        
        vt.assign(sz*2,Node());
        //fa(i,0,n) vt[i+sz].v = d[i];
        fd(i,sz-1,0) vt[i].l = i<<1,vt[i].r=i<<1|1;
    }
    
    LL query(int l,int r,int node,int nl,int nr)
    {
        if(l<=nl && nr <=r) return vt[node].v;
        if(nr <l || nl > r) return 0ll;
        int mid = nl+nr>>1;
        return query(l,r,vt[node].l,nl,mid) + query(l,r,vt[node].r,mid+1,nr);
    }
    
    void upd(int i,LL v)
    {
        int nl = 0, nr = sz-1;
        int cur = root.back();
        int nxt = vt.size();
        
        root.push_back(nxt);
        vt.push_back(vt[cur]);
        
        while(nl ^ nr)
        {
            int mid= nl+nr>>1;
            
            if(i <= mid) 
            {
                nr=mid,vt[nxt].l = ++nxt;
                cur = vt[cur].l;
                vt.push_back(vt[cur]);
            }
            else
            {
                nl = mid+1,vt[nxt].r=++nxt;
                cur = vt[cur].r;
                vt.push_back(vt[cur]);    
            }            
        }
        
        vt[nxt].v += v;
        --nxt;
        while(nxt>= root.back()) vt[nxt].v= vt[vt[nxt].l].v + vt[vt[nxt].r].v,--nxt;        
    }    
}pst;



int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);
    
    int cnt; ci(cnt);
    
    while(cnt--)
    {
        int n,q; ci(n>>q);
        
        pst.init(n);
        
        vector<seti> vi(n);
        
        for(auto & x : vi) ci(x.first >> x.second);
        sort(vi.begin(),vi.end());
        
        map<int,int> sp;
        
        int cn= 0;        
        for(auto &[x,y] : vi)
        {
            if(!sp.count(x)) sp[x]= cn;
            pst.upd(y,1);
            ++cn;
        }
        
        
        while(q--)
        {
            int l,r, d,u; ci(l>>r >> d >> u);
            
            pst.query(d,u,r) - pst.query(d,u,l-1);
        }
        
    }    
    
    
    
}

