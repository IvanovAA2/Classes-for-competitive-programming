class MergeSortTree
{
private:
	vector<vector<ll>> t;
	vector<vector<array<int, 2>>> cascad;
	int p = 1;
public:
	MergeSortTree (const vector<ll> &v)
	{
		int n = size(v);
		while (p < n)
		{
			p *= 2;
		}
		t.resize(2 * p);
		for (int i = 0; i < n; ++i)
		{
			t[p + i].push_back(v[i]);
		}
		cascad.resize(p);
		for (int i = p - 1; i > 0; --i)
		{
			auto &v = t[i], &vl = t[i * 2], &vr = t[i * 2 + 1];
			v.resize(size(vl) + size(vr));
			merge
			(
				begin(vl), end(vl),
				begin(vr), end(vr),
				begin(v)
			);
			cascad[i].resize(size(v) + 1);
			int l = 0, r = 0;
			for (int j = 0; j < size(v); ++j)
			{
				while (l < size(vl) and vl[l] < v[j])
				{
					++l;
				}
				while (r < size(vr) and vr[r] < v[j])
				{
					++r;
				}
				cascad[i][j] = {l, r};
			}
			cascad[i][size(v)][0] = size(vl);
			cascad[i][size(v)][1] = size(vr);
		}
	}
	int less(int l, int r, ll x, int cl = 0, int cr = -1, int c = 1, int i = -1)
	{
		if (cr == -1)
		{
			cr = p;
			i = lower_bound(begin(t[c]), end(t[c]), x) - begin(t[c]);
		}
		if (cr <= l or r <= cl)
		{
			return 0;
		}
		if (l <= cl and cr <= r)
		{
			return i;
		}

		int cm = (cl + cr) / 2;
		return less(l, r, x, cl, cm, c * 2, cascad[c][i][0])
			 + less(l, r, x, cm, cr, c * 2 + 1, cascad[c][i][1]);
	}
	int lessOrEqual(int l, int r, ll x)
	{
		return less(l, r, x + 1);
	}
	int greater(int l, int r, ll x)
	{
		return (r - l) - less(l, r, x + 1);
	}
	int greaterOrEqual(int l, int r, ll x)
	{
		return (r - l) - less(l, r, x);
	}
	int count(int l, int r, ll lx, ll rx)
	{
		return less(l, r, rx) - less(l, r, lx);
	}
};