class Treap
{
	struct node // new argument
	{
		node *l, *r;
		ll key, priority, val;
		ll sum, kol = 1, add = 0, max;

		node(ll key, ll val) : l(nullptr), r(nullptr),
			key(key), val(val),
			sum(val), max(val) {
			static mt19937 g{ (unsigned int)time(0) };
			priority = g();
		}
	} *treap = nullptr;

	static void update(node* root) // new argument
	{
		root->sum = root->val;
		root->kol = 1;
		root->max = root->val;

		if (root->l) {
			root->sum += root->l->sum + root->l->kol * root->l->add;
			root->kol += root->l->kol;
			root->max = std::max(root->max, root->l->max + root->l->add);
		}
		if (root->r) {
			root->sum += root->r->sum + root->r->kol * root->r->add;
			root->kol += root->r->kol;
			root->max = std::max(root->max, root->r->max + root->r->add);
		}
	}

	static void propagate(node* root) // new argument
	{
		if (!root or !root->add) {
			return;
		}

		if (root->l) {
			root->l->add += root->add;
		}
		if (root->r) {
			root->r->add += root->add;
		}

		root->sum += root->add * root->kol;
		root->val += root->add;
		root->max += root->add;
		root->add = 0;
	}

	static pair<node*, node*> split(node* root, ll key)
	{
		propagate(root);
		if (!root) {
			return { 0, 0 };
		}

		if (root->key < key) {
			auto [l, r] = split(root->r, key);
			root->r = l;
			update(root);

			return { root, r };
		}
		else {
			auto [l, r] = split(root->l, key);
			root->l = r;
			update(root);

			return { l, root };
		}
	}

	static node* merge(node* a, node* b)
	{
		propagate(a);
		propagate(b);
		if (!a) {
			return b;
		}
		if (!b) {
			return a;
		}

		if (a->priority > b->priority) {
			a->r = merge(a->r, b);
			update(a);

			return a;
		}
		else {
			b->l = merge(a, b->l);
			update(b);

			return b;
		}
	}

	static node* merge(node* l, node* m, node* r) {
		return merge(l, merge(m, r));
	}

	static node* min_node(node* cur)
	{
		if (cur) {
			while (cur->l) {
				cur = cur->l;
			}
		}

		return cur;
	}

	static node* max_node(node* cur)
	{
		if (cur) {
			while (cur->r) {
				cur = cur->r;
			}
		}

		return cur;
	}

	static ll amount(node* cur)
	{
		if (!cur) {
			return 0;
		}

		update(cur);

		return cur->kol;
	}

	tuple<node*, node*, node*> split(ll l, ll r) // [l, r)
	{
		auto [less, right] = split(treap, l);
		auto [middle, greater] = split(right, r);

		return { less, middle, greater };
	}

	static void rek_output(map<ll, ll>& mp, node* root)
	{
		if (!root) {
			return;
		}

		rek_output(mp, root->l);
		mp[root->key] = root->val;
		rek_output(mp, root->r);
	}

public:
	static constexpr ll ne = -1e18;

	Treap(ll n = 0, ll x = 0)
	{
		for (int i = 0; i < n; ++i) {
			insert(x, i);
		}
	}

	void insert(ll val, ll key = ne)
	{
		if (key == ne) {
			key = amount(treap);
		}

		if (!treap) {
			treap = new node{ key, val };
			return;
		}

		auto [less, x, greater] = split(key, key + 1);

		delete_tree(x);
		x = new node(key, val);

		treap = merge(less, x, greater);
	}

	bool erase(ll key)
	{
		if (!treap) {
			return false;
		}

		auto [less, x, greater] = split(key, key + 1);

		bool res = x;
		delete_tree(x);
		treap = merge(less, greater);

		return res;
	}

	static void delete_tree(node* tree)
	{
		if (!tree) {
			return;
		}

		if (tree->l) {
			delete_tree(tree->l);
		}
		if (tree->r) {
			delete_tree(tree->r);
		}

		delete tree;
	}

	bool contains(ll key) {
		node* cur = treap;

		while (cur) {
			if (cur->key == key) {
				return true;
			}

			if (key < cur->key) {
				cur = cur->l;
			}
			else {
				cur = cur->r;
			}
		}

		return false;
	}

	ll sum(ll l, ll r) // [l, r)
	{
		ll res = 0;

		auto [less, between, greater] = split(l, r);
		if (between) {
			res = between->sum + between->kol * between->add;
		}
		treap = merge(less, between, greater);

		return res;
	}

	void add(ll l, ll r, ll x) // [l, r)
	{
		auto [less, between, greater] = split(l, r);
		if (between) {
			between->add += x;
		}
		treap = merge(less, between, greater);
	}

	ll gr_key(ll key)
	{
		if (!treap) {
			return ne;
		}
		ll ret = ne;

		auto [left, greater] = split(treap, key + 1);
		node* res = min_node(greater);
		if (res) {
			ret = res->val;
		}
		treap = merge(left, greater);

		return ret;
	}

	ll gre_key(ll key)
	{
		if (!treap) {
			return ne;
		}
		ll ret = ne;

		auto [less, right] = split(treap, key);
		node* res = min_node(right);
		if (res) {
			ret = res->val;
		}
		treap = merge(less, right);

		return ret;
	}

	ll ls_key(ll key)
	{
		if (!treap) {
			return ne;
		}
		ll ret = ne;

		auto [less, right] = split(treap, key);
		node* res = max_node(less);
		if (res) {
			ret = res->val;
		}
		treap = merge(less, right);

		return ret;
	}

	ll max(ll l, ll r)
	{
		ll res = -2e18;

		auto [less, between, greater] = split(l, r);
		if (between) {
			res = between->add + between->max;
		}
		treap = merge(less, between, greater);

		return res;
	}

	ll at_key(ll key)
	{
		node* cur = treap;

		while (cur) {
			if (cur->key == key) {
				return cur->val;
			}

			if (key < cur->key) {
				cur = cur->l;
			}
			else {
				cur = cur->r;
			}
		}

		return ne;
	}

	ll at_pos(ll pos)
	{
		node* cur = treap;

		while (cur) {
			ll amount_l = amount(cur->l);
			if (amount_l == pos) {
				return cur->val;
			}

			if (pos < amount_l) {
				cur = cur->l;
			}
			else {
				pos -= amount_l + 1;
				cur = cur->r;
			}
		}

		return ne;
	}

	ll size() {
		return amount(treap);
	}

	map<ll, ll> get_map()
	{
		map<ll, ll> mp;

		rek_output(mp, treap);

		return mp;
	}
};