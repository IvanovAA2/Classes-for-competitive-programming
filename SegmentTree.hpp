class SegmentTree
{
private:
	struct Node
	{
		static constexpr ll sum_ne = 0;
		static constexpr ll max_ne = LLONG_MIN;
		static constexpr ll min_ne = LLONG_MAX;
		
		static constexpr ll cng_ne = 0; // нейтральное значение изменения не отрезке

		//ll sum;
		ll max;
		//ll min;

		ll cng = Node::cng_ne;

		Node() :
			//sum(sum_ne)
			max(max_ne)
			//min(min_ne)
		{
		}
		Node(ll x) :
			//sum(x)
			max(x)
			//min(x)
		{
		}
	};

	const int p; 
	vector<Node> t;

private:
	void apply(int c, int cl, int cr, ll cng) // приминение изменения на отрезке
	{
		//t[c].cng = cng;
		t[c].cng += cng; 
		//t[c].cng = max(t[c].cng, cng); 
		//t[c].cng = min(t[c].cng, cng);
		
		t[c].max += cng;
	}

	Node comb(Node a, Node b) // комбинирование узлов
	{
		Node res;

		//res.sum = a.sum + b.sum;
		res.max = max(a.max, b.max);
		//res.min = min(a.min, b.min);

		return res;
	}

	void propagate(int c, int cl, int cr)
	{
		if (t[c].cng != Node::cng_ne and cr - cl != 1)
		{
			int cm = (cl + cr) / 2;
			apply(2 * c + 0, cl, cm, t[c].cng);
			apply(2 * c + 1, cm, cr, t[c].cng);

			t[c].cng = Node::cng_ne;
		}
	}

	void update(int c)
	{
		t[c] = comb(t[c * 2 + 0], t[c * 2 + 1]);
	}

public:
	SegmentTree(int n, ll x)
		: p (bit_ceil(size_t(n))), t (2 * p, Node(x))
	{
		for (int i = p - 1; i; --i)
		{
			update(i);
		}
	}

	template<class S>
	SegmentTree(const vector<S>& v)
		: p (bit_ceil(size(v))), t (2 * p)
	{
		for (int i = 0; i < size(v); i++)
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
		if (cr == -1)
		{
			cr = p;
		}
		propagate(c, cl, cr);

		if (cl >= r or cr <= l)
		{
			return Node();
		}
		if (cl >= l and cr <= r)
		{
			return t[c];
		}

		int cm = (cl + cr) / 2;
		return comb(
			get(l, r, cl, cm, c * 2 + 0), 
			get(l, r, cm, cr, c * 2 + 1)
		);
	}

	void change(int l, int r, ll cng, int cl = 0, int cr = -1, int c = 1)
	{
		if (cr == -1)
		{
			cr = p;
		}
		propagate(c, cl, cr);

		if (cl >= r or cr <= l)
		{
			return;
		}
		if (cl >= l and cr <= r)
		{
			apply(c, cl, cr, cng);
			return;
		}

		int cm = (cl + cr) / 2;
		change(l, r, cng, cl, cm, c * 2 + 0);
		change(l, r, cng, cm, cr, c * 2 + 1);
		update(c);
	}
};