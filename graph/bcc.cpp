
int dfn[max_v], low[max_v], cn, ccn;
vector<int> adj[max_v];
vector<setl> st, bcc[max_v];
int ans[max_v];


int main()
{
#ifdef OHSOLUTION
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m; ci(n >> m);

    fa(i, 0, m)
    {
        int x, y; ci(x >> y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    function<void(int, int)> dfs = [&](int u, int p)
    {
        dfn[u] = low[u] = ++cn;

        for (auto& v : adj[u]) if (v != p)
        {
            if (dfn[v] < dfn[u]) st.push_back({ u,v });

            if (dfn[v]) ckmin(low[u], dfn[v]);
            else
            {
                dfs(v, u);
                ckmin(low[u], low[v]);
                if (low[v] >= dfn[u])
                {
                    while (1)
                    {
                        setl cur = st.back(); st.pop_back();
                        bcc[ccn].push_back(cur);
                        if (cur.first == u && cur.second == v) break;
                    }                    
                    ++ccn;
                }

            }
        }
    };


    fa(i, 1, n + 1) if (!dfn[i]) dfs(i, -1);
