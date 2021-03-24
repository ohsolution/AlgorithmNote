/* get longest segment that range max value - min value <= k
   
   INPUT
   n k
   a0 ... an
   
   TIME COMPLEXITY
   O(N)
*/

int main()
{
#ifdef OHSOLUTION
	freopen("input.txt", "r", stdin);
#endif	
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	LL n, k; ci(k >> n);

	vector <int> arr(n);
	fa(i, 0, n) ci(arr[i]);

	int l = 0;
	int ans = 0;
	deque<int> uq, bq;

	auto insert = [&](int idx)
	{
		while (uq.size() && arr[uq.back()] <= arr[idx]) uq.pop_back();
		while (bq.size() && arr[bq.back()] >= arr[idx]) bq.pop_back();
		uq.push_back(idx), bq.push_back(idx);
	};

	auto del = [&](int idx)
	{
		if (uq.front() == idx) uq.pop_front();
		if (bq.front() == idx) bq.pop_front();
	};

	fa(i, 0, n)
	{
		insert(i);
		while (arr[uq.front()] - arr[bq.front()] > k) del(l++);
		ckmax(ans, i - l + 1);
	}

	co(ans);
	return 0;
}
