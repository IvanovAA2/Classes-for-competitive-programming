class SegmentTree
{
private:
	struct Node
	{
		static constexpr ll sum_ne = 0;		// нейтральный элемент сложения
		static constexpr ll max_ne = ll(1) << 63; // нейтральный элемент максимума
		static constexpr ll min_ne = (ll(1) << 63) - 1;	// нейтральный элемент минимума

		static constexpr ll cng_ne = 0; // нейтральный элемент изменения на отрезке

		ll sum;
		int sz;
		//ll max;
		//ll min;

		ll cng = Node::cng_ne;

		Node() :
			sum(sum_ne),
			sz(1)
			//max(max_ne)
			//min(min_ne)
		{}
		Node(ll x) :
			sum(x),
			sz(1)
			//max(x)
			//min(x)
		{}
	};

	int p = 1;
	vector<Node> t;

private:
	inline void update_cng(int x, ll d) // обновление изменения на отрезке
	{
		t[x].cng += d;
		//t[x].cng = d; 
		//t[x].cng = max(t[x].cng, d); 
		//t[x].cng = min(t[x].cng, d); 
	}

	inline void propagate(int x)
	{
		if (t[x].cng == Node::cng_ne)
		{
			return;
		}
		// влияние изменения на операицю
		t[x].sum += t[x].cng * t[x].sz;
		//t[x].max += t[x].cng;
		//t[x].min += t[x].cng;
		//t[x].sum = t[x].cng * t[x].sz;

		if (x < p)
		{
			update_cng(2 * x, t[x].cng);
			update_cng(2 * x + 1, t[x].cng);
		}
		t[x].cng = Node::cng_ne;
	}

	inline Node comb(Node a, Node b) // комбинирование узлов
	{
		Node res;
		res.sum = a.sum + b.sum;
		res.sz = a.sz + b.sz;
		//res.max = max(a.max, b.max);
		//res.min = min(a.min, b.min);
		return res;
	}

	inline Node get(int x)
	{
		propagate(x);
		return t[x];
	}

	inline void update(int x)
	{
		t[x] = comb(get(x * 2), get(x * 2 + 1));
	}

public:
	SegmentTree(int n, ll x)
	{
		while (p < n)
		{
			p <<= 1;
		}
		t.assign(2 * p, Node(x));
		for (int i = p - 1; i; --i)
		{
			update(i);
		}
	}

	void read(int n, int from = 0)
	{
		for (int i = 0; i < n; ++i)
		{
			ll x;
			cin >> x;
			t[p + from + i] = Node(x);
		}
		for (int i = p - 1; i; --i)
		{
			update(i);
		}
	}

	template<class S>
	SegmentTree(const vector<S> &v)
	{
		int n = size(v);
		while (p < n)
		{
			p <<= 1;
		}
		t.assign(2 * p, Node());

		for (int i = 0; i < n; i++)
		{
			t[p + i] = Node(v[i]);
		}

		for (int i = p - 1; i; i--)
		{
			update(i);
		}
	}

	Node get(int l, int r, int cl = 0, int cr = -1, int c = 1)
	{
		propagate(c);
		if (cr == -1)
		{
			cr = p;
		}
		if (cl >= r or cr <= l)
		{
			return Node();
		}
		if (cl >= l and cr <= r)
		{
			return t[c];
		}

		int cm = (cl + cr) / 2;
		return comb(get(l, r, cl, cm, c * 2), get(l, r, cm, cr, c * 2 + 1));
	}

	Node get_node(int i)
	{
		return get(i, i + 1);
	}

	void change(int l, int r, ll d, int cl = 0, int cr = -1, int c = 1)
	{
		propagate(c);
		if (cr == -1)
		{
			cr = p;
		}

		if (cl >= r or cr <= l)
		{
			return;
		}
		if (cl >= l and cr <= r)
		{
			update_cng(c, d);
			return;
		}

		int cm = (cl + cr) / 2;
		change(l, r, d, cl, cm, c * 2);
		change(l, r, d, cm, cr, c * 2 + 1);
		update(c);
	}
};