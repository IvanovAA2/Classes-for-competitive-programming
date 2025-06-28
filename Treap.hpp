class Treap
{
	struct Node // new argument
	{
		Node *l, *r;
		ll key, priority, value;
		ll sum, kol = 1, add = 0, max;

		Node(ll key, ll value) :
			l(nullptr), r(nullptr),
			key(key), value(value),
			sum(value), max(value)
		{
			static mt19937 g(time(0));
			priority = g();
		}
	} *treap = nullptr;

	static void update(Node *root) // new argument
	{
		root->sum = root->value;
		root->kol = 1;
		root->max = root->value;

		if (root->l)
		{
			root->sum += root->l->sum + root->l->kol * root->l->add;
			root->kol += root->l->kol;
			root->max = std::max(root->max, root->l->max + root->l->add);
		}
		if (root->r)
		{
			root->sum += root->r->sum + root->r->kol * root->r->add;
			root->kol += root->r->kol;
			root->max = std::max(root->max, root->r->max + root->r->add);
		}
	}

	static void propagate(Node *root) // new argument
	{
		if (not root or root->add == 0)
		{
			return;
		}

		if (root->l)
		{
			root->l->add += root->add;
		}
		if (root->r)
		{
			root->r->add += root->add;
		}

		root->sum += root->add * root->kol;
		root->value += root->add;
		root->max += root->add;
		root->add = 0;
	}

	static pair<Node*, Node*> split(Node *root, ll key)
	{
		propagate(root);
		if (not root)
		{
			return { 0, 0 };
		}

		if (root->key < key)
		{
			auto [l, r] = split(root->r, key);
			root->r = l;
			update(root);

			return { root, r };
		}
		else
		{
			auto [l, r] = split(root->l, key);
			root->l = r;
			update(root);

			return { l, root };
		}
	}

	static Node* merge(Node *a, Node *b)
	{
		propagate(a);
		propagate(b);
		if (not a or not b)
		{
			return a ? a : b;
		}

		if (a->priority > b->priority)
		{
			a->r = merge(a->r, b);
			update(a);

			return a;
		}
		else
		{
			b->l = merge(a, b->l);
			update(b);

			return b;
		}
	}

	static Node *merge(Node *l, Node *m, Node *r)
	{
		return merge(l, merge(m, r));
	}

	static Node* min_node(Node *cur)
	{
		if (cur)
		{
			while (cur->l)
			{
				cur = cur->l;
			}
		}

		return cur;
	}

	static Node* max_node(Node *cur)
	{
		if (cur)
		{
			while (cur->r)
			{
				cur = cur->r;
			}
		}

		return cur;
	}

	static ll amount(Node *cur)
	{
		if (not cur)
		{
			return 0;
		}

		update(cur);
		return cur->kol;
	}

	tuple<Node*, Node*, Node*> split(ll l, ll r) // [l, r)
	{
		auto [less, right] = split(treap, l);
		auto [middle, greater] = split(right, r);

		return { less, middle, greater };
	}

	static void rek_output(map<ll, ll>& mp, Node *root)
	{
		if (not root)
		{
			return;
		}

		rek_output(mp, root->l);
		mp[root->key] = root->value;
		rek_output(mp, root->r);
	}

public:
	static constexpr ll ne = -1e18;

	Treap(ll n = 0, ll x = 0)
	{
		for (int i = 0; i < n; ++i)
		{
			insert(x, i);
		}
	}

	void insert(ll value, ll key = ne)
	{
		if (key == ne)
		{
			key = amount(treap);
		}
		if (not treap)
		{
			treap = new Node{ key, value };
			return;
		}

		auto [less, x, greater] = split(key, key + 1);

		delete_tree(x);
		x = new Node(key, value);

		treap = merge(less, x, greater);
	}

	bool erase(ll key)
	{
		if (not treap)
		{
			return false;
		}

		auto [less, x, greater] = split(key, key + 1);

		bool res = x;
		delete_tree(x);
		treap = merge(less, greater);

		return res;
	}

	static void delete_tree(Node *tree)
	{
		if (not tree)
		{
			return;
		}

		if (tree->l)
		{
			delete_tree(tree->l);
		}
		if (tree->r)
		{
			delete_tree(tree->r);
		}

		delete tree;
	}

	bool contains(ll key)
	{
		Node *cur = treap;

		while (cur)
		{
			if (cur->key == key)
			{
				return true;
			}
			cur = key < cur->key ? cur->l : cur->r;
		}

		return false;
	}

	ll sum(ll l, ll r) // [l, r)
	{
		auto [less, between, greater] = split(l, r);
		ll res = between ? between->sum + between->kol * between->add : 0;
		treap = merge(less, between, greater);

		return res;
	}

	void add(ll l, ll r, ll x) // [l, r)
	{
		auto [less, between, greater] = split(l, r);
		if (between)
		{
			between->add += x;
		}
		treap = merge(less, between, greater);
	}

	ll gr_key(ll key)
	{
		if (not treap)
		{
			return ne;
		}
		
		auto [left, greater] = split(treap, key + 1);
		Node *res = min_node(greater);
		ll ret = res ? res->value : ne; 
		treap = merge(left, greater);

		return ret;
	}

	ll gre_key(ll key)
	{
		if (not treap)
		{
			return ne;
		}

		auto [less, right] = split(treap, key);
		Node *res = min_node(right);
		ll ret = res ? res->value : ne; 
		treap = merge(less, right);

		return ret;
	}

	ll ls_key(ll key)
	{
		if (not treap)
		{
			return ne;
		}

		auto [less, right] = split(treap, key);
		Node *res = max_node(less);
		ll ret = res ? res->value : ne; 
		treap = merge(less, right);

		return ret;
	}

	ll max(ll l, ll r)
	{
		auto [less, between, greater] = split(l, r);
		ll res = between ? between->add + between->max : -2e18;
		treap = merge(less, between, greater);

		return res;
	}

	ll at_key(ll key)
	{
		Node *cur = treap;

		while (cur)
		{
			if (cur->key == key)
			{
				return cur->value;
			}

			cur = key < cur->key ? cur->l : cur = cur->r;
		}

		return ne;
	}

	ll at_pos(ll pos)
	{
		Node *cur = treap;

		while (cur)
		{
			ll amount_l = amount(cur->l);
			if (amount_l == pos)
			{
				return cur->value;
			}

			if (pos < amount_l)
			{
				cur = cur->l;
			}
			else
			{
				pos -= amount_l + 1;
				cur = cur->r;
			}
		}

		return ne;
	}

	ll size()
	{
		return amount(treap);
	}

	map<ll, ll> get_map()
	{
		map<ll, ll> mp;

		rek_output(mp, treap);

		return mp;
	}
};