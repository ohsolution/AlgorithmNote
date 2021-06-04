using ull = unsigned __int128; // 64bit g++

auto isprime = [&](ull t)
{
		vector<ull> pli = { 2,325, 9375, 28178, 450775, 9780504, 1795265022 };

		auto modpow = [&](ull base, ull k, ull m)
		{
				base %= m;
				ull ret = 1;
				while (k)
				{
						if (k & 1) ret = ret * base % m;
						base = base * base % m;
						k >>= 1;
				}

				return ret;
		};


		auto miler = [&](LL n, LL a)
		{
				if (a % n == 0) return true;

				ull d = n - 1;
				while (d % 2 == 0)
				{
						if (modpow(a, d, n) == n - 1) return true;
						d >>= 1;
				}

				ull tmp = modpow(a, d, n);

				return (tmp == n - 1 || tmp == 1);
		};

		for (auto& x : pli) if (!miler(t, x)) return false;
		return true;
};
