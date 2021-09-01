
struct edge
{
	int a, b, cap, flow, cost;
};

vector<edge> ve;
vector<int> adj[max_v];
int idx[max_v], dist[max_v];
int va[max_v], vb[max_v],inq[max_v];
bool vist[max_v];

int main()
{
#ifdef SCPC
	freopen("input.txt", "r", stdin);
#endif
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n; ci(n);

	fa(i, 1, n + 1) ci(va[i]);
	fa(i, 1, n + 1) ci(vb[i]);

	int S = 2 * n + 1;
	int T = 2 * n + 2;

	auto addedge = [&](int a, int b, int cap, int cost)
	{			
		edge e1 = { a,b,cap,0,cost };
		edge e2 = { b,a,0,0,-cost };
		adj[a].push_back(ve.size());
		ve.push_back(e1);		
		adj[b].push_back(ve.size());
		ve.push_back(e2);
	};

	// S a
	fa(i, 1, n + 1) addedge(S, i, 1, 0);
	// b T
	fa(i, 1, n + 1) addedge(i+n, T, 1, 0);
	// a b
	fa(i, 1, n + 1) fa(j, 1, n + 1) addedge(i, j + n,1, -((va[i]>=vb[j]) + (va[i]>vb[j])));	

	int ans = 0;

	auto spfa = [&]()
	{		
		memset(dist, 0x3f, sizeof(dist));
		memset(inq, 0, sizeof(inq));

		queue<int> bq; bq.push(S);
		dist[S] = 0; inq[S] = 1;
		while (bq.size())
		{
			int u = bq.front(); bq.pop(); inq[u] = 0;
			
			for (auto& v : adj[u])
			{
				auto c = ve[v];
				if (c.flow<c.cap && (dist[c.b] > dist[u] + c.cost))
				{
					dist[c.b] = dist[u] + c.cost;
					if (!inq[c.b])bq.push(c.b), inq[c.b] = 1;
				}
			}
		}

		return dist[T] != INF;
	};

	
	function<int(int, int)> dfs = [&](int u, int f)
	{	
		if (!f) return 0;
		vist[u] = 1;		
		if (u == T) return f;

		for (; idx[u] < adj[u].size(); ++idx[u])
		{
			int v = adj[u][idx[u]];
			auto c = ve[v];

			if (dist[c.b] != dist[u] + c.cost || vist[c.b]) continue;

			if (int flow = dfs(c.b, min(f, c.cap - c.flow)))
			{
				ve[v].flow += flow;
				ve[v ^ 1].flow -= flow;
				return flow;
			}
		}

		return 0;
	};

	while (spfa())
	{		
		memset(idx, 0, sizeof(idx));
		memset(vist, 0, sizeof(vist));
		while (int f = dfs(S, INF))
		{			
			ans += dist[T] * f;
			memset(vist, 0, sizeof(vist));
		}
		
	}

	co(-ans);

	return 0;
}
