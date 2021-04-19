
//================code===================//

//#define TLE

#ifdef TLE
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#endif

#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <ctime>

#define ci(t) cin>>t
#define co(t) cout<<t
#define LL long long
#define ld long double
#define fa(i,a,b) for(LL i=(a);i<(LL)(b);++i)
#define fd(i,a,b) for(LL i=(a);i>(LL)(b);--i)
#define setp pair<LL,point>
#define setl pair<LL,LL>
#define micro 0.000001

using namespace std;



#ifdef OHSOLUTION
#define ce(t) cerr<<t
#define AT cerr << "\n=================ANS=================\n"
#define AE cerr << "\n=====================================\n"
#define DB(a) cerr << __LINE__ << ": " << #a << " = " << (a) << endl;
#else
#define AT
#define AE
#define ce(t)
#define __popcnt64 __builtin_popcountll 
#define __popcnt __builtin_popcount  
#endif

pair <int, int> vu[9] = { {0,1},{1,0},{0,-1} ,{-1,0},{0,0},{1,1}, {-1,1} , {1,-1},{-1,-1} }; //RDLU EWSN

template<typename T, typename U> void ckmax(T& a, U b) { a = a < b ? b : a; }
template<typename T, typename U> void ckmin(T& a, U b) { a = a > b ? b : a; }
struct gcmp { bool operator()(LL a, LL b) { return a < b; } bool operator()(setl a, setl b) { return a.second < b.second; } };
struct lcmp { bool operator()(LL a, LL b) { return a > b; } bool operator()(setl a, setl b) { return a.second > b.second; } };

const int max_v = 4e2 + 7;
const int max_k = 3e2 + 7;
const int INF = 1e9 + 7;
const LL LNF = (LL)5e18 + 7ll;
const LL mod = 1e9 + 7;

struct edge 
{
	int a, b, cap, flow;
};

int n, s, t, dist[max_v], idx[max_v];
vector<edge> ve;
vector<int> adj[max_v];

void addedge(int a, int b, int cap) {	
	edge e1 = { a, b, cap, 0 };
	edge e2 = { b, a, 0, 0 };
	adj[a].push_back(ve.size());
	ve.push_back(e1);
	adj[b].push_back(ve.size());
	ve.push_back(e2);
}

bool bfs() {	
	queue<int> bq;
	bq.push(s);
	memset(dist, -1, sizeof(dist));
	dist[s] = 0;

	while (bq.size() && dist[t] == -1)
	{
		int v = bq.front(); bq.pop();
		
		for (auto& u : adj[v])
		{			
			auto c = ve[u];
			if (dist[c.b] == -1 && c.flow < c.cap)
			{
				bq.push(c.b);
				dist[c.b] = dist[v] + 1;
			}
		}
	}	
		
	return ~dist[t];
}

int dfs(int v, int flow) 
{
	if (!flow)  return 0;
	if (v == t)  return flow;

	for (; idx[v] < adj[v].size(); ++idx[v])
	{
		int u = adj[v][idx[v]];
		auto c = ve[u];
		if (dist[c.b] != dist[v] + 1) continue;

		if (int f = dfs(c.b, min(flow, c.cap - c.flow)))
		{
			ve[u].flow += f;
			ve[u ^ 1].flow -= f;
			return f;
		}		
	}

	return 0;	
}

int main()
{
#ifdef OHSOLUTION
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int v, e; ci(v >> e);
	s = 1, t = 2;	
  
	fa(i, 0, e)
	{
      int a,b; ci(a>>b);
      addedge(a,b,1);
  }
  
	int ans = 0;
	while (bfs())
	{
		memset(idx, 0, sizeof(idx));
		while (int tmp = dfs(s, INF)) ans += tmp;
	}
	co(ans);

    return 0;
}
