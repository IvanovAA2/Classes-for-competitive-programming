class ImplicitSegmentTree
{
	// нейтральный элемент
	static const ll ne = 0; 
	// границы запросов [l, r)
	static const ll lb = 0;
	static const ll rb = 1e9 + 1;

	struct Node
	{
		ll value = ne; 
		int l = -1, r = -1;
	};
    vector<Node> t{1};
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
public:
	ll get (ll l, ll r, ll cl = lb, ll cr = rb, int c = 0) 
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
	void set (ll i, ll x, ll cl = lb, ll cr = rb, int c = 0)
	{
		if (cr - cl == 1)
		{
			t[c].value = x;
			return;
		}

		ll cm = (cl + cr) / 2;
		if (i < cm)
		{
			set(i, x, cl, cm, t[c].l = get_position(t[c].l));
		}
		else
		{
			set(i, x, cm, cr, t[c].r = get_position(t[c].r));
		}
		// операция
		t[c].value = get_value(t[c].l) + get_value(t[c].r);
	}
};  