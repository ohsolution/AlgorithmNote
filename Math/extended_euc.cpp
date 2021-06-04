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
