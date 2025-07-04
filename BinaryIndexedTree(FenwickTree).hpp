class FenwickTree
{
    vector<ll> v, t;
public:
    FenwickTree(int n) : v(n), t(n)
    {}
    void set(int i, ll x)
    {
        ll d = x - v[i];
        add(i, d);
    }
    void add(int i, ll d)
    {
        v[i] += d;
        while (i < size(t))
        {
            t[i] += d;
            i |= i + 1;
        }
    }
    ll sum(int i)
    {
        ll sum = 0;
        while (i >= 0)
        {
            sum += t[i];
            i &= i + 1;
            --i;
        }

        return sum;
    }
};

class FenwickTree2D
{
	vector<vector<ll>> t;
public:
	FenwickTree2D (int n)
	{
		t.assign(n, vector<ll>(n));
	}
	void add(ll x, ll y, ll d)
	{
		for (ll i = x; i < size(t); i |= i + 1)
		{
			for (ll j = y; j < size(t); j |= j + 1)
			{
				t[i][j] += d;
			}
		}
	}
	ll sum(ll x, ll y)
	{
		ll res = 0;
		for (ll i = x; i >= 0; i = (i & i + 1) - 1)
		{
			for (ll j = y; j >= 0; j = (j & j + 1) - 1)
			{
				res += t[i][j];
			}
		}
		return res;
	}
	ll get(ll x1, ll y1, ll z1, ll x2, ll y2, ll z2)
	{
		return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);
	}
};

class FenwickTree3D
{
	vector<vector<vector<ll>>> t;
public:
	FenwickTree3D (int n)
	{
		t.assign(n, vector<vector<ll>>(n, vector<ll>(n)));
	}
	void add(ll x, ll y, ll z, ll d)
	{
		for (ll i = x; i < size(t); i |= i + 1)
		{
			for (ll j = y; j < size(t); j |= j + 1)
			{
				for (ll k = z; k < size(t); k |= k + 1)
				{
					t[i][j][k] += d;
				}
			}
		}
	}
	ll sum(ll x, ll y, ll z)
	{
		ll res = 0;
		for (ll i = x; i >= 0; i = (i & i + 1) - 1)
		{
			for (ll j = y; j >= 0; j = (j & j + 1) - 1)
			{
				for (ll k = z; k >= 0; k = (k & k + 1) - 1)
				{
					res += t[i][j][k];
				}
			}
		}
		return res;
	}
	ll get(ll x1, ll y1, ll z1, ll x2, ll y2, ll z2)
	{
		ll sum1 = sum(x2, y2, z1 - 1) - sum(x2, y1 - 1, z1 - 1) - sum(x1 - 1, y2, z1 - 1) + sum(x1 - 1, y1 - 1, z1 - 1);
		ll sum2 = sum(x2, y2, z2) - sum(x1 - 1, y2, z2) - sum(x2, y1 - 1, z2) + sum(x1 - 1, y1 - 1, z2);
		return sum2 - sum1;
	}
};