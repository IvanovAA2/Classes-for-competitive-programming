const ll MOD = 1e9 + 7;
using mat = vector<vector<ll>>;
ll powm (ll x, ll pw)
{
	ll res = 1;
	while (pw)
	{
		if (pw & 1)
		{
			res = res * x % MOD;
		}
		x = x * x % MOD;
		pw >>= 1;
	}
	return res;
}
mat mat_inv (mat a)
{
	int n = size(a);
	mat inv(n, vector<ll>(n));
	for (int i = 0; i < n; ++i)
	{
		inv[i][i] = 1;
	}
	for (int i = 0; i < n; ++i)
	{
		if (a[i][i] == 0)
		{
			for (int j = n - 1; j >= 0; --j)
			{
				if (a[j][i])
				{
					for (int l = 0; l < n; ++l)
					{
						a[i][l] += a[j][l];
						a[i][l] -= a[i][l] >= MOD ? MOD : 0;
						inv[i][l] += inv[j][l];
						inv[i][l] -= inv[i][l] >= MOD ? MOD : 0;
					}
					break;
				}
			}
		}
		ll k = powm(a[i][i], MOD - 2);
		for (int j = 0; j < n; ++j)
		{
			a[i][j] = a[i][j] * k % MOD;
			inv[i][j] = inv[i][j] * k % MOD;
		}
		for (int j = 0; j < n; ++j)
		{
			if (j == i)
			{
				continue;
			}
			k = a[j][i];
			for (int l = 0; l < n; ++l)
			{
				a[j][l] -= k * a[i][l] % MOD;
				a[j][l] += a[j][l] < 0 ? MOD : 0;
				inv[j][l] -= k * inv[i][l] % MOD;
				inv[j][l] += inv[j][l] < 0 ? MOD : 0;
			}
		}
	}
	return inv;
}
 
mat mat_mul (const mat &a, const mat &b)
{
	int n = size(a);
	int m = size(b);
	int p = size(b[0]);
	mat c(n, vector<ll>(p));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			for (int k = 0; k < p; ++k)
			{
				c[i][k] += a[i][j] * b[j][k];
				c[i][k] %= MOD;
			}
		}
	}
	return c;
}
 
mat powm (mat x, ll pw)
{
	int n = size(x);
	mat res(n, vector<ll>(n));
	for (int i = 0; i < n; ++i)
	{
		res[i][i] = 1;
	}
	while (pw)
	{
		if (pw & 1)
		{
			res = mat_mul(res, x);
		}
		x = mat_mul(x, x);
		pw >>= 1;
	}
	return res;
}
mat sub_I (mat a)
{
	int n = size(a);
	for (int i = 0; i < n; ++i)
	{
		a[i][i] = a[i][i] ? a[i][i] - 1 : MOD - 1;
	}
	return a;
}
void mat_add (mat &to, const mat &from)
{
	int n = size(to);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			to[i][j] += from[i][j];
			to[i][j] -= to[i][j] >= MOD ? MOD : 0;
		}
	}
}