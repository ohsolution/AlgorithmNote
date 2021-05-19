auto bfs = [&](int sp) // get longest dist from sp that can vist every vertex
{
	queue<int> bq;
	bitset<max_v> cur; 
	fa(i, 0, n) cur[i] = 1;

	bq.push(sp);
	cur[sp] = 0;
	int cnt = 0;

	while (bq.size())
	{
		int sz = bq.size();

		while (sz--)
		{
			int u = bq.front(); bq.pop();

			bitset<max_v> cbit = cur & adj[u];

			if ((cur ^= cbit) == 0) return cnt+1;

			while (cbit!=0)
			{
				int c = cbit._Find_first();
				cbit[c] = 0;
				bq.push(c);
			};
		}						
	}


	return -1; // impossible
};
