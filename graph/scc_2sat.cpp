
vector<int> adj[max_v], radj[max_v];

int main()
{
#ifdef OHSOLUTION
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    int n; ci(n);    

    auto tof = [&](int x)
    {
        return x >= n ? x - n : x + n;
    };

    auto addedge = [&](int u, int v,int tp)
    {
        if (tp) u = tof(u), v = tof(v);
        adj[tof(u)].push_back(v);
        adj[tof(v)].push_back(u);
        radj[v].push_back(tof(u));
        radj[u].push_back(tof(v));
    };

    // a^b == (~a || ~b) & (a||b)
    // a eq b == (~a||b) &(a||~b)
    // a-> b == (~a||b)
    // (a+b+c<=1) == (~a||~b) & (~a||~c) &(~b||~c)
    // set a =1 (a||a), set a=0 (~a||~a)

    vector<bool> vist(max_v);
    vector<int> sn(max_v);
    int cn;
    stack<int> st;

    function<void(int)> dfs = [&](int u)
    {
        vist[u] = 1;
        for (auto& v : adj[u]) if (!vist[v]) dfs(v);
        st.push(u);
    };

    fa(i, 0, max_v) if (!vist[i]) dfs(i);

    vist.assign(max_v, 0);

    function<void(int)> dfs2 = [&](int u)
    {
        vist[u] = 1;
        sn[u] = cn;
        for (auto& v : radj[u]) if (!vist[v]) dfs2(v);
    };

    while (st.size())
    {
        int u = st.top(); st.pop();
        if (vist[u]) continue;
        dfs2(u);
        ++cn;
    }

    bool flag = 1;
    fa(i, 0, 1e4) flag &= (sn[i] != sn[i + 1e4]);
    flag ? co("YES") : co("NO");

    return 0;
}
