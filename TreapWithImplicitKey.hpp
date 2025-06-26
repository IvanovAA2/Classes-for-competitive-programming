class TreapWIK
{
    struct Node
    {
        Node *l = nullptr, *r = nullptr;
        ll priority, value, cnt = 1;
        ll add = 0, mark;

        Node (ll value, ll mark) : 
            value(value),
            mark(mark)
        {
            static mt19937_64 gen;
            priority = gen();
        }
    } *treap = nullptr;

    static void propagate (Node* root)
    {
        if (!root)
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
        root->value += root->add;
        root->add = 0;
    }
    static void update (Node* root)
    {
        root->cnt = 1;

        if (root->l)
        {
            root->cnt += root->l->cnt;
        }
        if (root->r)
        {
            root->cnt += root->r->cnt;
        }
    }

    static ll get_amount (Node* root)
    {
        if (!root)
        {
            return 0;
        }

        return root->cnt;
    }

    static tuple<Node*, Node*> split (Node* root, ll amount)
    {
        if (!root)
        {
            return { nullptr, nullptr };
        }
        propagate(root);

        if (get_amount(root->l) >= amount)
        {
            auto [l, r] = split(root->l, amount);

            root->l = r;
            update(root);

            return { l, root };
        }
        else
        {
            auto [l, r] = split(root->r, amount - get_amount(root->l) - 1);

            root->r = l;
            update(root);

            return { root, r };
        }
    }
    static Node* merge (Node* a, Node* b)
    {
        propagate(a);
        propagate(b);

        if (!a)
        {
            return b;
        }
        if (!b)
        {
            return a;
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

    tuple<Node*, Node*, Node*> split (ll l, ll r) // [l, r)
    {
        auto [temp, right] = split(treap, r);
        auto [left, middle] = split(temp, l);

        return { left, middle, right };
    }
    void merge (Node* a, Node* b, Node* c)
    {
        treap = merge(merge(a, b), c);
    }
public:

    TreapWIK (ll n)
    {
        for (int i = 1; i <= n; ++i)
        {
            treap = merge(treap, new Node(0, i));
        }
    }

    void solve (ll l, ll r)
    {
        auto [left, middle, right] = split(l, r);

        ++middle->add;

        merge(middle, left, right);
    }
    void ans (Node* root = nullptr)
    {
        if (!root)
        {
            ans(treap);
        }
        else
        {
            propagate(root);

            if (root->l)
            {
                ans(root->l);
            }
            cout << root->mark << " " << root->value << "\n";
            if (root->r)
            {
                ans(root->r);
            }
        }
    }
};