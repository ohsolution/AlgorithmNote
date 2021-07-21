
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




