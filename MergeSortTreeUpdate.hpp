class MSTU
{
private:
	vector<multiset<ll>> t;
	int p = 1;
public:
	MSTU (const vector<ll>& v)
	{
		int n = size(v);
		while (p < n)
		{
			p *= 2;
		}
		t.assign(2 * p, {});

		for(int i = 0; i < n; ++i)
		{
			t[p + i].insert(v[i]);
		}
		for (int i = p - 1; i > 0; --i)
		{
			for (ll x : t[i * 2])
			{
				t[i].insert(x);
			}
			for (ll x : t[i * 2 + 1])
			{
				t[i].insert(x);
			}
		}
	}
	void set(int pos, ll x)
	{
		int prev = *begin(t[p + pos]);

		for (int i = p + pos; i > 0; i /= 2)
		{
			t[i].erase(prev);
			t[i].insert(x);
		}
	}
	bool check(int l, int r, ll x, int cl = 0, int cr = -1, int c = 1)
	{
		if (cr == -1)
		{
			cr = p;
		}
		if (cr <= l or r <= cl)
		{
			return false;
		}
		if (l <= cl and cr <= r)
		{
			return t[c].find(x) != end(t[c]);
		}

		int cm = (cl + cr) / 2;
		return 
			check(l, r, x, cl, cm, c * 2) or 
			check(l, r, x, cm, cr, c * 2 + 1);
	}
};