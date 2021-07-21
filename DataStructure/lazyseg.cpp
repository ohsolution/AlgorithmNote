
// range maximum seg with range add operation

LL arr[max_v<<2];
LL lazy[max_v << 2];

void prop(int node, int nl, int nr)
{
	if (lazy[node])
	{
		if (nl != nr)
		{
			lazy[node << 1] += lazy[node];
			lazy[node << 1 | 1] += lazy[node];
		}

		arr[node] += lazy[node];
		lazy[node] = 0;
	}
}

void update(int l, int r, LL val, int node, int nl, int nr)
{
	prop(node, nl, nr);

	if (nr < l || nl > r) return;

	if (l <= nl && nr <= r)
	{
		lazy[node] += val;
		prop(node, nl, nr);
		return;
	}

	int mid = nl + nr >> 1;
	update(l, r, val, node << 1, nl, mid);
	update(l,r,val,node<<1|1,mid+1,nr);
	arr[node] = max(arr[node << 1], arr[node << 1 | 1]);
}

LL query(int l, int r, int node, int nl, int nr)
{
	prop(node, nl, nr);

	if (nr < l || nl > r) return -LNF;

	if (l <= nl && nr <= r) return arr[node];

	int mid = nl + nr >> 1;

	return max(query(l, r, node << 1, nl, mid), query(l, r, node << 1 | 1, mid + 1, nr));
}
