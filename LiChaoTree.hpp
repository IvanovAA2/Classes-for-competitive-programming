struct Line
{
	ll k, b;
	ll operator() (ll x) const
	{
		return k * x + b;
	}
	Line (ll k, ll b) : k(k), b(b)
	{}
};
class LiChaoTree
{
	// границы запросов [l, r]
	static const ll lb = 0;
	static const ll rb = 1e6;
	
	struct Node
	{
		Line f = Line(0, 1e18);
		int l = -1, r = -1;
	};
	vector<Node> t{1};
public:
	ll get (ll x, ll cl = lb, ll cr = rb, int c = 0)
	{
		if (c == -1)
		{
			return 1e18;
		}
		if (cr - cl == 1)
		{
			return t[c].f(x);
		}

		ll cm = (cl + cr) / 2;
		if (x < cm)
		{
			return min(t[c].f(x), get(x, cl, cm, t[c].l));
		}
		else
		{
			return min(t[c].f(x), get(x, cm, cr, t[c].r));
		}
	}
	int add (Line newLine, ll l = lb, ll r = rb, ll cl = lb, ll cr = rb, int c = 0)
	{
		if (cr <= l or r <= cl)
		{
			return c;
		}
		if (c == -1)
		{
			t.emplace_back(newLine);
			return size(t) - 1;
		}

		ll cm = (cl + cr) / 2;
		if (l <= cl and cr <= r)
		{
			if (newLine(cm) < t[c].f(cm))
			{
				swap(t[c].f, newLine);
			}

			bool isl = newLine(cl) <= t[c].f(cl);
			bool isr = newLine(cr) <= t[c].f(cr);
			if (isl != isr)
			{
				if (isl)
				{
					t[c].l = add(newLine, l, r, cl, cm, t[c].l);
				}
				else
				{
					t[c].r = add(newLine, l, r, cm, cr, t[c].r);
				}
			}
			return c;
		}

		t[c].l = add(newLine, l, r, cl, cm, t[c].l);
		t[c].r = add(newLine, l, r, cm, cr, t[c].r);
		return c;
	}
};