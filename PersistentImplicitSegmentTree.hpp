class PersistentImplicitSegmentTree
{
	// нейтральный элемент
	static const ll ne = 0;
	// границы запросов [lb, rb)
	static const ll lb = 0;
	static const ll rb = 1e9 + 1;

	struct Node
	{
		ll value = ne;
		int l = -1, r = -1;
	};
	vector<Node> t = {Node()};
	vector<int> roots = {0};
private:
	int get_position (int i)
	{
		if (i == -1)
		{
			i = size(t);
			t.emplace_back();
		}
		return i;
	}
	ll get_value (int i)
	{
		if (i == -1)
		{
			return ne;
		}
		return t[i].value;
	}
	ll get (ll l, ll r, ll cl, ll cr, int c)
	{
		if (c == -1 or cr <= l or r <= cl)
		{
			return ne;
		}
		if (l <= cl and cr <= r)
		{
			return t[c].value;
		}

		ll cm = (cl + cr) / 2;
		// операция
		return get(l, r, cl, cm, t[c].l) +
			get(l, r, cm, cr, t[c].r);
	}
	int set (ll i, ll x, ll cl, ll cr, int c)
	{
		if (cr - cl == 1)
		{
			t.push_back(t[c]);
			c = size(t) - 1;
			t[c].value = x;
			return c;
		}

		ll cm = (cl + cr) / 2;
		if (i < cm)
		{
			int l = set(i, x, cl, cm, get_position(t[c].l));
			t.push_back(t[c]);
			c = size(t) - 1;
			t[c].l = l;
		}
		else
		{
			int r = set(i, x, cm, cr, t[c].r = get_position(t[c].r));
			t.push_back(t[c]);
			c = size(t) - 1;
			t[c].r = r;
		}
		// операция
		t[c].value = get_value(t[c].l) + get_value(t[c].r);
		return c;
	}
public:
	ll get (int time, ll l, ll r)
	{
		return get(l, r, lb, rb, roots[time]);
	}
	void set (ll i, ll x)
	{
		roots.push_back(set(i, x, lb, rb, roots.back()));
	}
};