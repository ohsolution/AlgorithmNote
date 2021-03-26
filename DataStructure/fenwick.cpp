int main()
{
	int n; ci(n);
	vector<int> arr(max_v);

	auto query = [&](int i) // point query about idx
	{
		int ret = 0;
		for (; i; i -= i & -i) ret += arr[i];
		return ret;
	};

	auto update = [&](int l,int r,int k) // range update [l,r] += k
	{
		for (; l < max_v; l += l & -l) arr[l] += k;
		++r;
		for (; r < max_v; r += r & -r) arr[r] -= k;
	};

	fa(i, 0, n)
	{
		int x, y; ci(x >> y);

		int nx = query(x);
		int ny = query(y);

		co(nx + ny << "\n");

		update(x, x, -nx);
		update(y, y, -ny);
		if (y - x > 1) update(x + 1, y - 1, 1);
	}
	return 0;
}
