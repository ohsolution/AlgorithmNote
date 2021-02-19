
int sn;
int num[max_v];
int maxi[max_v];
int ans[max_v];
int vi[max_v];

struct query
{
	int l, r;
	int idx;

	bool operator <(query& x)
	{
		return l / sn == x.l / sn ? r < x.r : l / sn < x.l / sn;
	}
};

int main()
{
#ifdef OHSOLUTION
	freopen("input.txt", "r", stdin);
#endif	
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n; ci(n);
	sn = sqrt(n);
	

	fa(i, 0, n) ci(vi[i]);

	int q; ci(q);
	vector <query> tar(q);
	fa(i, 0, q)
	{
		ci(tar[i].l >> tar[i].r);
		--tar[i].l, --tar[i].r;
		tar[i].idx = i;
	}
	sort(tar.begin(), tar.end());

	int s = tar[0].l;
	int e = tar[0].r;	
	int ret = 0;

	fa(i, s, e + 1)
	{
		if(num[vi[i]]) --maxi[num[vi[i]]];
		++maxi[++num[vi[i]]];
		ckmax(ret, num[vi[i]]);
	}
	
	ans[tar[0].idx] = ret;

	fa(i, 1, q)
	{		
		while (s < tar[i].l)
		{						
			if ((--maxi[num[vi[s]]] == 0)&& ret == num[vi[s]]) --ret;
			--num[vi[s]];
			++maxi[num[vi[s++]]];			
		}
		while (s > tar[i].l)
		{
			if(num[vi[--s]]) --maxi[num[vi[s]]];
			++maxi[++num[vi[s]]];
			ckmax(ret, num[vi[s]]);			
		}
		while (e > tar[i].r)
		{	
			if ((--maxi[num[vi[e]]] == 0)&& ret == num[vi[e]]) --ret;
			--num[vi[e]];
			++maxi[num[vi[e--]]];						
		}
		while (e < tar[i].r)
		{
			if(num[vi[++e]]) --maxi[num[vi[e]]];
			++maxi[++num[vi[e]]];
			ckmax(ret, num[vi[e]]);			
		}
		ans[tar[i].idx] = ret;
	}

	fa(i, 0, q) co(ans[i] << "\n");

	return 0;
}
