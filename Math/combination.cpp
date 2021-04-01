int main()
{
#ifdef OHSOLUTION
    freopen("input.txt", "r", stdin);
#endif	
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);        

    vector <int> sp(max_v);
    vector<int> prime;

    // get prime to max_v in O(n)
    auto sieve = [&]()
    {
        fa(i, 2, max_v)
        {
            if (!sp[i]) prime.push_back(i);
            for (auto& x : prime)
            {                
                if (x * i >= max_v) break;
                sp[x * i] = x;
                if (i % x == 0) break;
            }
        }
    };

    vector<LL> fact(max_v), inv(max_v), factinv(max_v);    
    auto precombi = [&]()
    {
        fact[0] = fact[1] = inv[1] = factinv[0] = factinv[1] = 1;
        fa(i, 2, max_v)
        {
            fact[i] = fact[i - 1] * i % mod;
            inv[i] = inv[mod % i] * (mod - (mod / i)) % mod;
            factinv[i] = factinv[i - 1] * inv[i] % mod;
        }
    };

    auto combi = [&](LL n, LL r)
    {
        return fact[n] * factinv[r] % mod * factinv[n - r] % mod;
    };

    // get combi to small prime modular p in O(p)
    auto lukas = [&](LL n,LL k, LL p)
    {        
        LL ret = 1;

        while (n || k)
        {
            LL an = n % p;
            LL ak = k % p;

            if (an < ak) return 0ll;

            ret *= (fact[an] * factinv[ak]) % p;
            ret %= p;
            ret *= factinv[an - ak];
            ret %= p;

            n /= p;
            k /= p;
        }

        return ret;        
    };

    return 0;
}
