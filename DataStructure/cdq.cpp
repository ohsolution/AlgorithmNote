void cdq(int l, int r)
{    
    if (l + 1 == r) return;

    int mid = l + r >> 1;

    cdq(l, mid); cdq(mid, r);

    vector<node> tmp;
    vector<setp> dirty;

    int a = l, b = mid;

    while (a < mid && b < r)
    {
        if (vi[a].x <= vi[b].x)
        {
            if (!vi[a].upd)
            {
                tmp.push_back(vi[a++]);
                continue;
            }

            upd(vi[a].y, vi[a].sgn,!vi[a].tp);
            dirty.push_back({ vi[a].y,-vi[a].sgn,!vi[a].tp });
            tmp.push_back(vi[a++]);
        }        
        else
        {
            if (vi[b].upd)
            {
                tmp.push_back(vi[b++]);
                continue;
            }

            ans[vi[b].idx] += vi[b].sgn * query(vi[b].y, vi[b].tp);                       
            tmp.push_back(vi[b++]);
        }
    }
    
    while (a < mid) tmp.push_back(vi[a++]);    
    while (b < r)
    {        
        if(!vi[b].upd) ans[vi[b].idx] += vi[b].sgn * query(vi[b].y, vi[b].tp);
        tmp.push_back(vi[b++]);        
    }
    
    fa(i, l, r) vi[i] = tmp[i - l];
    
    for (auto& x : dirty) upd(get<0>(x), get<1>(x), get<2>(x));
}
