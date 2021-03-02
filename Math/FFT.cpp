const ld PI = acos(-1);
typedef complex<ld> cpx;

void fft(vector<cpx>& f, bool inv=false)
{
	int n = f.size();

	for (int i = 1, j = 0; i < n; ++i)
	{
		int b = n / 2;
		while (!((j ^= b) & b)) b >>= 1;
		if (i < j) swap(f[i], f[j]);
	}

	for (int k = 1; k < n; k <<= 1)	
	{
		double a = (inv ? PI / k : -PI / k);
		cpx w(cos(a), sin(a));

		for (int i = 0; i < n; i += k * 2)
		{
			cpx wp(1, 0);
			fa(j,0,k)
			{
				cpx x = f[i + j], y = f[i + j + k] * wp;
				f[i + j] = x + y;
				f[i + j + k] = x - y;
				wp *= w;
			}
		}
	}

	if (inv) fa(i, 0, n) f[i] /= n;
}

void mul(vector<cpx> a, vector<cpx>b, vector<cpx>& c)
{
	int n = 1;
	while (n < a.size() + 1 || n < b.size() + 1) n <<= 1;
	n <<= 1;

	a.resize(n);
	b.resize(n);
	c.resize(n);

	fft(a);
	fft(b);

	fa(i, 0, n) c[i] = a[i] * b[i];

	fft(c, 1);
	fa(i, 0, n) c[i] = (int)round(c[i].real());
}
