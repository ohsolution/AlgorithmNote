LL arr[max_v];
multiset<LL> hmax, hmin;
LL ans;

void rminsert(LL val)
{
	int sz = hmax.size() - hmin.size();

	if (sz)
	{
		if (*(--hmax.end()) < val) hmin.insert(val);
		else
		{
			hmin.insert(*(--hmax.end()));
			hmax.erase(--hmax.end());
			hmax.insert(val);
		}
	}
	else
	{
		if (*hmin.begin() < val)
		{
			hmax.insert(*hmin.begin());
			hmin.erase(hmin.begin());
			hmin.insert(val);
		}
		else hmax.insert(val);
	}
}

void rmdelete(LL val)
{
	if (hmax.find(val) != hmax.end())
	{		
		if (hmax.size() == hmin.size())
		{
			hmax.insert(*hmin.begin());
			hmin.erase(hmin.begin());
		}
		hmax.erase(hmax.find(val));
	}
	else
	{
		if (hmax.size() != hmin.size())
		{
			hmin.insert(*(--hmax.end()));
			hmax.erase(--hmax.end());
		}
		hmin.erase(hmin.find(val));		
	}
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);

	int n, k;
	ci(n >> k);
	fa(i, 0, n) ci(arr[i]);

	if (k <= 2)
	{
		if (k & 1) fa(i, 0, n) ans += arr[i];
		else fa(i, 0, n - 1) ans += min(arr[i], arr[i+1]);
		co(ans);
		return 0;
	}

	hmax.insert(min(arr[0], arr[1]));
	hmin.insert(max(arr[0], arr[1]));
	fa(i, 2, k) rminsert(arr[i]);

	ans += *(--hmax.end());
	fa(i, k, n)
	{
		rmdelete(arr[i - k]);
		rminsert(arr[i]);
		ans += *(--hmax.end());
	}

	co(ans);

	return 0;
}
