vector<int> kuhn (const vector<vector<int>> &graph, int m)
{
	int n = size(graph), cnt = 0;
	vector<int> r(m, -1);
	vector<bool> used(n), matched(n);

	for (int i = 0; i < n; ++i)
	{
		for (int j : graph[i])
		{
			if (r[j] == -1)
			{
				r[j] = i;
				matched[i] = true;
				++cnt;
				break;
			}
		}
	}

	function<bool(int)> dfs = [&](int cur) -> bool
	{
		if (used[cur])
		{
			return false;
		}
		used[cur] = true;

		for (int next : graph[cur])
		{
			if (r[next] == -1 or dfs(r[next]))
			{
				r[next] = cur;
				return true;
			}
		}

		return false;
	};

	for (int i = 0; i < n; ++i)
	{
		if (matched[i] == false)
		{
			fill(begin(used), end(used), false);
			if (dfs(i))
			{
				++cnt;
				matched[i] = true;
			}
			if (cnt == min(n, m))
			{
				return r;
			}
		}
	}

	return r;
}

pair<vector<int>, ll> hungarian_min (const vector<vector<ll>> &a)
{
	int n = size(a);
	int m = size(a[0]);
	// n <= m
	vector<ll> u(n + 1), v(m + 1);
	vector<int> p(m + 1), way(m + 1);
	for (int row = 1; row <= n; ++row)
	{
		p[0] = row;
		int cur_col = 0;
		vector<ll> minv(m + 1, LLONG_MAX);
		vector<bool> used(m + 1, false);
		do
		{
			used[cur_col] = true;
			int cur_row = p[cur_col], next_col;
			ll delta = LLONG_MAX;
			for (int col = 1; col <= m; ++col)
			{
				if (not used[col])
				{
					ll value = a[cur_row - 1][col - 1] - u[cur_row] - v[col];
					if (value < minv[col])
					{
						minv[col] = value;
						way[col] = cur_col;
					}
					if (minv[col] < delta)
					{
						delta = minv[col]; 
						next_col = col;
					}
				}
			}
			for (int i = 0; i <= m; ++i)
			{
				if (used[i])
				{
					u[p[i]] += delta;
					v[i] -= delta;
				}
				else
				{
					minv[i] -= delta;
				}
			}
			cur_col = next_col;
		}
		while (p[cur_col] != 0);
		do
		{
			p[cur_col] = p[way[cur_col]];
			cur_col = way[cur_col];
		}
		while (cur_col);
	}

    vector<int> ans(n);
	for (int j = 1; j <= m; ++j)
	{
		ans[p[j] - 1] = j - 1;
	}
	return {ans, -v[0]};
}
pair<vector<int>, ll> hungarian_max (vector<vector<ll>> a)
{
	for (int i = 0; i < size(a); ++i)
	{
		for (int j = 0; j < size(a[i]); ++j)
		{
			a[i][j] = -a[i][j];
		}
	}

	auto [p, cnt] = hungarian_min(a);
	return {move(p), -cnt};
}