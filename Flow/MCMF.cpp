vector<int> adj[max_v];
int vcap[max_v][max_v],vcost[max_v][max_v];
int d[max_v],p[max_v],inq[max_v];

bool spfa(int n, int s, int t)
{
    fill(d, d + n, INF);
    fill(p, p + n, -1);    

    d[s] = 0;
    queue<int> bq;
    bq.push(s);

    while (bq.size())
    {
        int u = bq.front(); bq.pop();

        inq[u] = 0;

        for (auto& v : adj[u])
        {
            if (vcap[u][v] > 0 && d[v] > d[u] + vcost[u][v])
            {
                d[v] = d[u] + vcost[u][v];
                p[v] = u;

                if (!inq[v]) inq[v] = 1, bq.push(v);
            }
        }
    }

    return d[t] != INF;
}

int mcmf(int n, int s, int t)
{
    int flow = 0;
    int cost = 0;    

    while (spfa(n, s, t))
    {
        int f = INF;
        int u = t;
        while (u ^ s) ckmin(f, vcap[p[u]][u]), u = p[u];
        flow += f;
        cost += f * d[t];
        u = t;
        while (u ^ s) vcap[p[u]][u] -= f, vcap[u][p[u]] += f, u = p[u];
    }

    return cost;
}

int main()
{
#ifdef OHSOLUTION
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m; ci(n >> m);

    auto cvt = [&](int x, int tp)
    {
        return x + 1 + tp * m;
    };

    auto addedge = [&](int a, int b, int cap, int cost)
    {
        adj[a].push_back(b);
        adj[b].push_back(a);
        vcost[a][b] = cost;
        vcost[b][a] = -cost;
        vcap[a][b] = cap;
    };
  
    int s = 0;
    int t = n + m + 2;

    fa(i, 0, n)
    {
        int x; ci(x);
        addedge(cvt(i,1),t, x, 0);
    }

    fa(i, 0, m)
    {
        int x; ci(x);
        addedge(s, cvt(i, 0), x, 0);
    }

    fa(i, 0, m) fa(j, 0, n)
    {
        int x; ci(x);
        addedge(cvt(i, 0), cvt(j, 1), INF, x);
    }

    co(mcmf(t + 1, s, t));

    return 0;
}
