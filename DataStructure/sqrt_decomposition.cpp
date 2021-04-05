// get the number of elem bigger than k in l to r

int arr[1157][max_v]; // isin , scnt,val;
int crr[1157][1157];
int sn;

void update(int idx, int k, int val)
{
    auto upd = [&](int i, int sc, int val)
    {
        for (; i <= max_v; i += i & -i) arr[sc][i] += val;
    };

    int sidx = idx / sn;
    upd(k,sidx,val);
    int cidx = idx - sidx * sn;
    crr[sidx][cidx] = ~val?k:0;
}

int query(int l, int r, int k)
{
    auto qur = [&](int i, int sc)
    {
        int ret = 0;
        for (; i; i -= i & -i) ret += arr[sc][i];
        return ret;
    };

    auto get = [&](int x)
    {
        int cs = 0;
        int scn = x / sn;
        int sidx = x - scn * sn;
        int cret = 0;
        while (cs != scn)
        {
            cret += qur(10001, cs) - qur(k, cs);
            ++cs;
        }

        fa(i, 0, sidx+1) cret += crr[cs][i] > k;

        return cret;
    };

    return get(r) - get(l-1);
}

int main()
{
#ifdef OHSOLUTION
    freopen("input.txt", "r", stdin);
#endif	    
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);        
    int n; ci(n);
    sn = sqrt(n*log2(1e4));
    vector <int> vi(n);
    fa(i, 0, n) ci(vi[i]),update(i,vi[i],1);

    int q; ci(q);
    while (q--)
    {
        int t; ci(t);
        if (t & 1)
        {
            int a, b; ci(a >> b); --a;
            update(a, vi[a], -1);
            vi[a] = b;
            update(a, vi[a], 1);
        }
        else
        {
            int l, r, k; ci(l >> r >> k); --l, --r;
            co(query(l, r, k)<<"\n");
        }
    }

    return 0;
}
