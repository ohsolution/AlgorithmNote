//================code===================//


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

const int max_v = 1e7 + 7;
const int max_k = 5e5 + 7;
const int bsz = 27;
const int INF = 0x3f3f3f3f;
const LL LNF = 0x3f3f3f3f3f3f3f3f;
const LL mod = 1e9 + 9;//998244353;// 
template<typename T, typename U> void MOD(T& a, U b) { a += b;if(a<0) a+=mod; if (a >= mod) a -= mod; };


struct Node
{
    int l,r,v;        
};

const int sz= 1<<20;     
Node vt[max_v+max_k];
int root[max_k];
int rn,cn;


void PST()
{
    root[rn++] = 1;
    cn = sz;    
    fd(i,sz-1,0) vt[i].l = i<<1,vt[i].r=i<<1|1;
}

void upd(int i,int v)
{          
    int cur = root[rn-1];
    int nxt = cn;

    root[rn++] = nxt;
    vt[cn++] = vt[cur];
    
    int dep = 18;
    
    while(~dep)
    {
        if(i & (1<< dep))
        {                
            vt[nxt].r = nxt+1; ++nxt;
            cur = vt[cur].r;
            vt[cn++]= vt[cur];
            
        }
        else
        {
            vt[nxt].l = nxt+1;
            ++nxt;
            cur = vt[cur].l;
            vt[cn++]= vt[cur];
            
        }
        
        --dep;
    }
    
    vt[nxt].v += v;
    --nxt;
    assert(nxt - root[rn-1] <=30);
    while(nxt >= root[rn-1]) vt[nxt].v = vt[vt[nxt].l].v + vt[vt[nxt].r].v,--nxt;
}  

int q2(int l,int r,int v)
{        
    int dep =18;    
    int ret = 0;
    
    while(~dep)
    {
        int dl=  vt[vt[r].l].v - vt[vt[l].l].v;
        int dr = vt[vt[r].r].v- vt[vt[l].r].v;
        
        if(dl && dr)
        {
            if(v&(1<<dep)) l= vt[l].l,r=vt[r].l;
            else ret |=1<<dep,l=vt[l].r,r=vt[r].r;
        }
        else if(dl) l= vt[l].l,r=vt[r].l;
        else if(dr) ret |=1<<dep,l=vt[l].r,r=vt[r].r;
        else assert(0);
        
        --dep;
    }
    
    return ret;
};

int q5(int l,int r,int k)
{
    int dep =18;    
    int ret = 0;
    
    while(~dep)
    {
        int dl=  vt[vt[r].l].v - vt[vt[l].l].v;            
        
        if(dl <= k) k-=dl,ret|=(1<<dep),l=vt[l].r,r=vt[r].r;
        else l=vt[l].l,r=vt[r].l;
        --dep;
    }
    
    return ret;
}

int q4(int l,int r,int k,int dep)
{
   // assert(dep >=0);
    if(dep==0) 
    {
        if(k & (1<< dep))return vt[r].v - vt[l].v;
            return (vt[vt[r].l].v - vt[vt[l].l].v);
        
    }
    
    if(k& (1<<dep)) // bit on
    {            
        return q4(vt[l].r,vt[r].r,k,dep-1) + (vt[vt[r].l].v - vt[vt[l].l].v);
    }
    else // bit off
    {
        return q4(vt[l].l,vt[r].l,k,dep-1);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);
    int q; ci(q);
        PST();
    while(q--)
    {
        int tp; ci(tp);
        
        if(tp==1)
        {
            int x; ci(x); upd(x,1);
        }
        else if(tp==2)
        {
            int l,r,x; ci(l>>r>>x);
            co(q2(root[l-1],root[r],x)<<"\n");            
        }
        else if(tp==3)
        {
            int x; ci(x); rn-=x;                
        }
        else if(tp==4)
        {
            int l,r,x; ci(l>>r>>x);
            co(q4(root[l-1],root[r],x,18)<<"\n");            
        }
        else
        {
            int l,r,x; ci(l>>r>>x);
            co(q5(root[l-1],root[r],x-1)<<"\n");
        }
    }
}

