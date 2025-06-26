class MST
{
private:
	vector<vector<ll>> t;
	int p = 1;
public:
	MST (const vector<ll> &v)
	{
		int n = size(v);
		while (p < n)
		{
			p *= 2;
		}
		t.assign(2 * p, {});
		for(int i = 0; i < n; ++i)
		{
			t[p + i].push_back(v[i]);
		}
		for (int i = p - 1; i > 0; --i)
		{
			t[i].resize(size(t[i * 2]) + size(t[i * 2 + 1]));
			merge
			(
				begin(t[i * 2]), end(t[i * 2]),
				begin(t[i * 2 + 1]), end(t[i * 2 + 1]),
				begin(t[i])
			);
		}
	}
	int less(int l, int r, ll x, int cl = 0, int cr = -1, int c = 1) 
	{
		if (c == -1)
		{
			c = p;
		}
		if (cr <= l or r <= cl)
		{
			return 0;
		}
		if (l <= cl and cr <= r)
		{
			return lower_bound(begin(t[c]), end(t[c]), x) - begin(t[c]);
		}

		int cm = (cl + cr) / 2;
		return less(l, r, x, cl, cm, c * 2)
			 + less(l, r, x, cm, cr, c * 2 + 1);
	}
	int less_or_eq(int l, int r, ll x)
	{
		return less(l, r, x + 1);
	}
	int greater(int l, int r, ll x)
	{
		return (r - l) - less_or_eq(l, r, x);
	}
	int greater_or_eq(int l, int r, ll x)
	{
		return (r - l) - less(l, r, x);
	}
	bool check(int l, int r, ll x, int cl = 0, int cr = -1, int c = 1) 
	{
		if (c == -1)
		{
			c = p;
		}
		if (cr <= l or r <= cl)
		{
			return false;
		}
		if (l <= cl and cr <= r)
		{
			auto it = lower_bound(begin(t[c]), end(t[c]), x);
			return it != end(t[c]) and *it == x;
		}

		int cm = (cl + cr) / 2;
		return check(l, r, x, cl, cm, c * 2)
			or check(l, r, x, cm, cr, c * 2 + 1);
	}
	int count(int l, int r, ll x)
	{
		return r - l - less(l, r, x) - greater(l, r, x);
    }
};