int main()
{
#ifdef OHSOLUTION
	freopen("input.txt", "r", stdin);
#endif	
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	ci(v >> e >> q);

	vector <edge> vi(e);
	fa(i, 0, e) ci(vi[i].x >> vi[i].y >> vi[i].cost),--vi[i].x,--vi[i].y;
	sort(vi.begin(), vi.end(), [&](auto& a, auto& b) {
		return a.cost > b.cost;
	});

	vector <setl> query(q);
	vector <int> l(q, 0), r(q, e);

	fa(i, 0, q) ci(query[i].first >> query[i].second),--query[i].first,--query[i].second;

	while (1)
	{
		bool ck = true;
		vector <vector<int>> tar(e);

		fa(i, 0, q)
		{
			if (l[i] != r[i])
			{
				ck = false;
				tar[l[i] + r[i] >> 1].push_back(i);
			}
		}

		if (ck) break;

		memset(p, -1, sizeof(int)*v);

		fa(i, 0, e)
		{
			merge(vi[i].x, vi[i].y);
			for (auto& id : tar[i])
			{
				if (find(query[id].first) == find(query[id].second)) r[id] = i;
				else l[id] = i + 1;				
			}
		}
	}

	fa(i, 0, q) co(vi[l[i]].cost << "\n");

	return 0;
}
