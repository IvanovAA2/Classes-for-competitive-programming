class SAT2
{
	vector<vector<int>> graph, rgraph;
private:
	inline int get(int x)
	{
		return x << 1;
	}
	inline int inv(int x)
	{
		return x ^ 1;
	}
public:
	SAT2 (int n)
	{
		graph.resize(2 * n);
		rgraph.resize(2 * n);
	}
	void add (int a, bool a_is_neg, int b, bool b_is_neg)
	{
		a = a_is_neg ? inv(get(a)) : get(a);
		b = b_is_neg ? inv(get(b)) : get(b);
		graph[inv(a)].push_back(b);
		graph[inv(b)].push_back(a);
		rgraph[b].push_back(inv(a));
		rgraph[a].push_back(inv(b));
	}
	pair<vector<bool>, bool> solve ()
	{
		int sz = size(graph);
		int n = sz / 2;
		for (int i = 0; i < sz; ++i)
		{
			sort(begin(graph[i]), end(graph[i]));
			auto new_end = unique(begin(graph[i]), end(graph[i]));
			graph[i].erase(new_end, end(graph[i]));
		}
		for (int i = 0; i < sz; ++i)
		{
			sort(begin(rgraph[i]), end(rgraph[i]));
			auto new_end = unique(begin(rgraph[i]), end(rgraph[i]));
			rgraph[i].erase(new_end, end(rgraph[i]));
		}

		vector<bool> bp(sz);
		vector<int> order(sz);
		int pos = sz;
		function<void(int)> dfs = [&](int cur)
		{
			bp[cur] = true;
			for (int next : graph[cur])
			{
				if (bp[next] == false)
				{
					dfs(next);
				}
			}
			order[--pos] = cur;
		};
		for (ll i = 0; i < n; i++)
		{
			int x = get(i);
			if (bp[x] == false)
			{
				dfs(x);
			}
			x = inv(x);
			if (bp[x] == false)
			{
				dfs(x);
			}
		}
		vector<int> c(sz, -1);
		int curc = 0;
		function<void(ll)> rdfs = [&](ll cur)
		{
			c[cur] = curc;
			for (ll x : rgraph[cur])
			{
				if (c[x] == -1)
				{
					rdfs(x);
				}
			}
		};
		for (int i : order)
		{
			if (c[order[i]] == -1)
			{
				rdfs(order[i]);
				++curc;
			}
		}

		for (ll i = 0; i < n; ++i)
		{
			if (c[get(i)] == c[inv(get(i))])
			{
				return {{}, false};
			}
		}

		vector<bool> ans(n);
		for (int i = 0; i < n; ++i)
		{
			ans[i] = c[get(i)] > c[inv(get(i))];
		}
		return {ans, true};
	}
};