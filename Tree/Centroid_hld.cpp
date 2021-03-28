vector<setl> adj[max_v];
int dep[max_v], p[max_v], sz[max_v],in[max_v],top[max_v],t,cp[max_v];
bool vist[max_v],color[max_v];
map<int, vector<int>> xh[max_v];

void dfs(int idx,int d=0, int par = -1)
{
	sz[idx] = 1;
	p[idx] = par;
	dep[idx] = d;

	if (adj[idx].size()>1 && adj[idx][0].first == par) swap(adj[idx][0], adj[idx][1]);

	for (auto& x : adj[idx]) if (x.first != par)
	{
		dfs(x.first,d+x.second, idx);
		sz[idx] += sz[x.first];
		if (sz[x.first] > sz[adj[idx][0].first]) swap(x, adj[idx][0]);
	}
}

void dfs2(int idx, int par = -1)
{
	in[idx] = t++;
	for (auto& x : adj[idx]) if(x.first != par)
	{
		top[x.first] = x.first == adj[idx][0].first ? top[idx] : x.first;
		dfs2(x.first, idx);
	}
}

int dfsz(int idx,int par=-1)
{
	sz[idx] = 1;
	for (auto& x : adj[idx]) if (par != x.first && !vist[x.first]) sz[idx] += dfsz(x.first, idx);
	return sz[idx];
}

int fc(int idx,int csz, int par = -1)
{
	for (auto& x : adj[idx]) if (!vist[x.first] && x.first != par && sz[x.first] > csz) return fc(x.first, csz, idx);
	return idx;
}

void mk(int idx, int par = -1)
{
	int csz = dfsz(idx);
	int cen = fc(idx, csz / 2);

	vist[cen] = 1;
	cp[cen] = par;

	for (auto& x : adj[cen]) if (!vist[x.first]) mk(x.first, cen);
}

int lca(int u, int v)
{
	while (top[u] != top[v])
	{
		int& c = sz[top[u]] > sz[top[v]] ? v : u;
		c = p[top[c]];
	}

	if (in[u] > in[v]) swap(u, v);
	return u;
}

inline int getdist(int u, int v)
{
	return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

void upd(int v)
{
	if (color[v]) return;
	color[v] = 1;

	int i = v;
	int pv = v;

	while (~i)
	{
		int dist = getdist(i, v);
		xh[i][pv].push_back(dist);
		pv = i;
		i = cp[i];
	}
}

int query(int v)
{	
	int ret = 0;

	int i = v;
	int pv = v;

	while (~i)
	{		
		int dist = getdist(i, v);

		for (auto& x : xh[i])
		{
			if (x.first == pv) continue;
			for (auto& y : x.second) ret += dist + y;
		}

		pv = i;
		i = cp[i];
	}

	return ret;
}

int main()
{
#ifdef OHSOLUTION
	freopen("input.txt", "r", stdin);
#endif	
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int v; ci(v);

	fa(i, 1, v)
	{
		int x, cost;
		ci(x >> cost);
		adj[i].push_back({ x,cost });
		adj[x].push_back({ i,cost });
	}

	// decomposition order is important hld > ctd slow
	
	mk(0); // centroid decomposition > mk centroid tree
	
	// heavy light decomposition
	dfs(0); 
	dfs2(0);

	int q; ci(q);

	while (q--)
	{
		int x, y; ci(x >> y);
		if (x & 1) upd(y);
		else co(query(y) << "\n");
	}


	return 0;
}
