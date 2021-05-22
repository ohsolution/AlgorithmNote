// O(v^2/64 +v)

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
		
			while (cbit!=0)
			{
				int c = cbit._Find_first();
				cbit[c] = 0;
				cur[c]=0;
				bq.push(c);
			};
			
			if(cur==0) return cnt+1;
		}						
		++
	}


	return -1; // impossible
};
