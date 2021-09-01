
struct point
{
	ld x, y;

	bool operator >(point& b)
	{
		return x==b.x ? y > b.y : x > b.x;
	}
};

struct vc
{
	point sp, ep;
	ld dx, dy;
};

ld ccw(point a, point b, point c)
{
	ld val = 1ll * ((b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x));
	if (val > 0ll) return 1; // 반시계
	else if (val < 0ll) return -1; // 시계
	else return 0; // 평행
}

ld ccw(vc v, vc u)
{
	return (v.dx * u.dy) - (v.dy * u.dx);
}

bool Isintersect(vc v, vc u)
{
	int ab = ccw(v.sp, v.ep, u.sp) * ccw(v.sp, v.ep, u.ep);
	int cd = ccw(u.sp, u.ep, v.sp) * ccw(u.sp, u.ep, v.ep);

	if (ab == 0 && cd == 0) // 두 벡터 평행
	{
		if (v.sp > v.ep) swap(v.sp, v.ep);
		if (u.sp > u.ep) swap(u.sp, u.ep);
		return !(u.sp > v.ep || v.sp > u.ep);
	}

	return ab <= 0 && cd <= 0;
}

vc findv(point a, point b)
{
	return{ a,b,b.x - a.x,b.y - a.y };
}

point geteq(vc v, vc u)
{
	if ((LL)ccw(v, u) == 0) // 벡터 평행 시 처리
	{
		if (v.sp > v.ep) swap(v.sp, v.ep);
		if (u.sp > u.ep) swap(u.sp, u.ep);
		
		if (v.ep.x == u.sp.x && v.ep.y == u.sp.y) return v.ep;
		else if (u.ep.x == v.sp.x && u.ep.y == v.sp.y) return v.sp;
		else exit(0); // 수많은 점에서 교점
	}

	point ret = v.sp;

	ld p = ccw(u, findv(v.sp, u.sp)) / ccw(v, u);

	ret.x += p * (v.dx);
	ret.y += p * (v.dy);

	if (ccw(u.sp, u.ep, ret))
	{
		ret = v.sp;
		ret.x -= p * (v.dx);
		ret.y -= p * (v.dy);
	}

	return ret;
}

int main()
{
#ifdef OHSOLUTION
	freopen("input.txt", "r", stdin);
#endif
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	// 두 벡터 교점 구하는 코드
	point sp1, sp2, ep1, ep2;
	ci(sp1.x >> sp1.y >> ep1.x >> ep1.y);
	ci(sp2.x >> sp2.y >> ep2.x >> ep2.y);

	vc a = findv(sp1, ep1);
	vc b = findv(sp2, ep2);

	if (Isintersect(a, b)) 
	{
		co(1<<"\n");
		point ans = geteq(a, b);		
		co(setprecision(9) << fixed << ans.x << " " << ans.y);
	}
	else co(0);

	
	
	
	return 0;
}

void function()
{
	auto ccw = [&](setl a, setl b, setl c)
	{
		return (b.first-a.first)*(c.second-b.second) - (c.first-b.first)*(b.second-a.second);
	};


	auto Isintersect=[&](setl a, setl b, setl c, setl d)
	{
		int ab = ccw(a, b, c) * ccw(a, b, d);
		int cd = ccw(c, d, a) * ccw(c, d, b);

		if (ab == 0 && cd == 0) // 두 벡터 평행
		{
			if (a > b) swap(a, b);
			if (c > d) swap(c, d);
			return !(c > b || a > d);
		}

		return ab <= 0 && cd <= 0;
	};

	auto g = [&](setl p, vector<setl>& vi) // 볼록다각형 내부 점판정 log n
	{
		if (vi.size() == 2)
		{
			return ccw(vi[0],vi[1],p)==0&& vi[0] <= p && p <= vi[1];
		}

		int l = 1;
		int r = vi.size();

		while (l ^ r)
		{
			int m = l + r >> 1;

			if (ccw(vi[0], vi[m], p) >= 0) l = m + 1;
			else r = m;
		}

		l -= (l == vi.size()) && (ccw(vi[0],vi[l-1],p) == 0);

		return (l != 1 && l != vi.size() && ccw(vi[l-1],vi[l],p) >= 0);
	};

	auto f = [&](vector<setl>& vi) // convex hull
	{
		sort(vi.begin(), vi.end());
		sort(vi.begin() + 1, vi.end(), [&](setl& a, setl& b) {return ccw(vi[0], a, b) > 0; });

		vector<int> st(n, -1);
		st[0] = 0;
		st[1] = 1;
		int top = 2;

		fa(i, 2, n)
		{
			while (top >= 2 && ccw(vi[st[top - 2]], vi[st[top - 1]], vi[i]) <= 0) --top;
			st[top++] = i;
		}

		vector<setl> ret(top);
		fa(i, 0, top) ret[i] = vi[st[i]];
		return ret; 
	};


}
