struct Node
	{
		int go[3] = { 0,0,0 };
		int p = -1;
		int leaf = 0;
	};

	vector<Node> arr(1);

	auto add = [&](string& s)
	{
		int u = 0;
		for (auto& x : s)
		{
			if (!arr[u].go[xh[x]])
			{
				arr[u].go[xh[x]] = arr.size();
				arr.push_back(Node());
			}

			u = arr[u].go[xh[x]];
		}

		++arr[u].leaf;
	};

	auto pre = [&]()
	{
		queue<int> bq; bq.push(0);
		arr[0].p = 0;

		while (bq.size())
		{
			int u = bq.front(); bq.pop();

			fa(i, 0, K) if (arr[u].go[i])
			{
				int nxt = arr[u].go[i];

				if (!u) arr[nxt].p = u;
				else
				{
					int v = arr[u].p;

					while (v && !arr[v].go[i]) v = arr[v].p;
					if (arr[v].go[i]) v = arr[v].go[i];
					arr[nxt].p = v;
				}

				arr[nxt].leaf += arr[arr[nxt].p].leaf;
				bq.push(nxt);
			}
		}
	};

	auto get = [&](string & needle)
	{
		int ans = 0;
		int u = 0;
		for (auto& x : needle)
		{
			while (u && !arr[u].go[x]) u = arr[u].p;
			if (arr[u].go[x]) u = arr[u].go[x];
			ans += arr[u].leaf;
		}
		return ans;
	}
