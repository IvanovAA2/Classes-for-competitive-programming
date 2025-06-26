class AhoCorasick
{
    struct Node
    {
        char pchar;
        int p, link = -1, exit = -1;
 
        array<ll, 26> next, go;
 
        vector<int> leaf;
 
        Node (int p, char pchar)
            : p(p), pchar(pchar)
        {
            next.fill(-1);
            go.fill(-1);
        }
    };
 
    vector<Node> t = { Node(-1, -1) };
 
    int order (char c)
    {
        return c - 'a';
    }
 
    int link (int cur)
    {
        if (t[cur].link == -1)
        {
            if (cur == 0 or t[cur].p == 0)
            {
                t[cur].link = 0;
            }
            else
            {
                t[cur].link = go(link(t[cur].p), t[cur].pchar);
            }
        }
 
        return t[cur].link;
    }
 
    int go (int cur, char c)
    {
        if (t[cur].go[c] == -1)
        {
            if (t[cur].next[c] == -1)
            {
                if (cur == 0)
                {
                    t[cur].go[c] = 0;
                }
                else
                {
                    t[cur].go[c] = go(link(cur), c);
                }
            }
            else
            {
                t[cur].go[c] = t[cur].next[c];
            }
        }
 
        return t[cur].go[c];
    }
 
    int exit (int cur)
    {
        if (t[cur].exit == -1)
        {
            if (cur == 0 or link(cur) == 0)
            {
                t[cur].exit = 0;
            }
            else
            {
                if (size(t[link(cur)].leaf))
                {
                    t[cur].exit = link(cur);
                }
                else
                {
                    t[cur].exit = exit(link(cur));
                }
            }
        }
 
        return t[cur].exit;
    }
 
public:
 
    void add (string word, int index)
    {
        int cur = 0;
 
        for (char c : word)
        {
            if (t[cur].next[order(c)] == -1)
            {
                t[cur].next[order(c)] = size(t);
 
                t.push_back(Node(cur, order(c)));
            }
 
            cur = t[cur].next[order(c)];
        }
 
        t[cur].leaf.push_back(index);
    }
 
    void solve (const string& s, int n)
    {
        vector<int> ans(n), count(size(t));
 
        int cur = 0;
        for (char c : s)
        {
            cur = go(cur, order(c));
            ++count[cur];
        }
 
        for (int cur = 0; cur < size(t); ++cur)
        {
            if (count[cur])
            {
                for (int leaf = cur; leaf != 0; leaf = exit(leaf))
                {
                    for (int s : t[leaf].leaf)
                    {
                        ans[s] += count[cur];
                    }
                }
            }
        }
 
        for (int x : ans)
        {
            cout << x << "\n";
        }
    }
};