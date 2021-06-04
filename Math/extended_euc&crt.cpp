tuple<LL, LL, LL> egcd(LL a, LL b)
{
	if (!b) return { a,1,0 };
	LL g, x, y;
	tie(g, x, y) = egcd(b, a % b);
	return { g,y,x - (a / b) * y };
}

setl get_sol(LL a, LL b , LL r)
{
	//ax + by = r
	LL g, x, y;
	tie(g, x, y) = egcd(a, b);
	x *= r / g;
	y *= r / g;

	LL A = b/ g;
	LL B = a / g;

	// x' = x + t * A 일반해 t 정수
	// y' = y - t * B

	return { x,y }; // ax+by=r 의 해 반환
}

auto crt = [&](LL a1, LL a2,LL m1,LL m2)
{		
	// 법이 서로소가 아닐때 gcd(m1,m2) !=1
	// x= a1(mod m1), x= a2(mod m2) <- m1x+m2y = a2-a1 

	if (a1 > a2) swap(m1, m2), swap(a1, a2);

	LL r = a2 - a1;

	LL g, x, y;
	tie(g, x, y) = egcd(m1, m2);

	if (r % g != 0) return;

	x *= r / g;
	y *= r / g;

	LL A = m2 / g;
	LL B = m1 / g;

	// x' = x + t * A 일반해 t 정수
	// y' = y - t * B

	if (x < 0)
	{
		x += A * ceil(-x / (ld)A);
	}

	x -= A * (x / A);

	tar.push_back(a1 + x * m1); // init crt

	return;
};
