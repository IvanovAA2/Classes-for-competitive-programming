class DST
{
private:
	using T = pll; // modify
	vector<vector<T>> data;
	int k = 1;
public:
	DST(const vector<ll>& v)
	{
		int p = 1, n = ssize(v);
		while (p < n) 
		{
			p *= 2;
			k++;
		}
		data.assign(k, vector<T>(n));

		for (int i = 0, d = 1; i < k; ++i, d *= 2) 
		{
			bool dir = false;
			for (int l = 0; l < n; l += d) 
			{
				int r = min(n, l + d);
				if (dir) 
				{
					data[i][l] = init(v[l]);
					for (int j = l + 1; j < r; ++j) 
					{
						data[i][j] = comb(data[i][j - 1], init(v[j])); 
					}
				}
				else 
				{
					data[i][r - 1] = init(v[r - 1]); 
					for (int j = r - 2; j >= l; --j) 
					{
						data[i][j] = comb(data[i][j + 1], init(v[j]));
					}
				}
				dir = not dir;
			}
		}
	}
	T get(int l, int r) const // [l, r]
	{
		if (l == r)
		{
			return data[0][l];
		}
		int layer = 31 - countl_zero(uint32_t(l ^ r));

		return comb(data[layer][l], data[layer][r]);
	}
	// change
	T init (const ll &x) const
	{
		return T{x, 1};
	}
	T comb (const T &a, const T &b) const
	{
		if (a.first == b.first)
		{
			return T{a.first, a.second + b.second};
		}
		return a.first > b.first ? a : b;
	}
};