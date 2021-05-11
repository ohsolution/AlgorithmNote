// nlog(n)

int main()
{
#ifdef OHSOLUTION
	freopen("input.txt", "r", stdin);
#endif
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n;
    string s;
    ci(n >> s);
       
    vector<int> sa(n), pos(n);
    int g;

    auto cmp = [&](int i, int j)
    {
        if (pos[i] ^ pos[j]) return pos[i] < pos[j];
        i += g;
        j += g;
        return (i < n && j < n) ? pos[i] < pos[j] : i>j;
    };

    auto getsa = [&]()
    {
        fa(i, 0, n) sa[i] = i, pos[i] = s[i];

        for (g = 1;; g <<= 1)
        {
            sort(sa.begin(), sa.end(), cmp);

            vector<int> tmp(n);

            fa(i, 0, n - 1) tmp[i + 1] = tmp[i] + cmp(sa[i], sa[i + 1]);

            fa(i, 0, n) pos[sa[i]] = tmp[i];

            if (tmp[n - 1] == n - 1) break;
        }
    };

    getsa();

    vector<int> lcp(n);

    auto getlcp = [&]()
    {
        for (int i = 0, k = 0; i < n; ++i,k=max(k-1,0))
        {            
            if (pos[i] + 1 == n) continue;

            for (int j = sa[pos[i] + 1]; s[i + k] == s[j + k]; ++k);
            lcp[pos[i]] = k;
        }
    };

    getlcp();
   
    int ans = 0;
    fa(i, 0, n) ckmax(ans, lcp[i]);
    co(ans);

	return 0;
}
