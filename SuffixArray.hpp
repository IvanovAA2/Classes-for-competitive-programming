class SuffixArray
{
private:
	string s;
	vector<int> sa;
	vector<int> inv;
	vector<int> lcp;
	vector<vector<int>> st;
private:
	int get_shifted(int pos, int shift) const
	{
		int res = pos + shift;
		
		if (res < 0)
		{
			res += size(s);
		}
		if (res >= size(s))
		{
			res -= size(s);
		}
		
		return res;
	}
public:
	const int operator[] (size_t i) const
	{
		return sa[i];
	}
	SuffixArray(string str) : s(str)
	{
		char TERMINATOR = 0;
		s += TERMINATOR;
		int n = ssize(s);
		vector<pii> mp(n);
		vector<int> c(n);
		sa.resize(n);
		inv.resize(n);
		for (int i = 0; i < n; ++i)
		{
			mp[i] = {s[i], i};
		}
		sort(begin(mp), end(mp));
		for (int i = 0; i < n; ++i)
		{
			sa[i] = mp[i].second;
			if (i)
			{
				c[i] = c[i - 1] + (mp[i].first != mp[i - 1].first);
			}
		}

		vector<int> bucket(n);
		int pw = 1;
		while (pw < n)
		{
			vector<pair<pii, int>> temp(n);
			for (int i = 0; i < n; ++i)
			{
				inv[sa[i]] = i;
			}

			fill(begin(bucket), end(bucket), 0);
			for (int i = 0; i < n; ++i)
			{
				++bucket[c[i]];
			}
			for (int i = 1; i < n; ++i)
			{
				bucket[i] += bucket[i - 1];
			}

			for (int i = n - 1; i >= 0; --i)
			{
				int shifted = inv[get_shifted(sa[i], -pw)];
				temp[--bucket[c[shifted]]] = {{c[shifted], c[i]}, sa[shifted]};
			}
			for (int i = 0; i < n; ++i)
			{
				sa[i] = temp[i].second;
				if (i)
				{
					c[i] = c[i - 1] + (temp[i].first != temp[i - 1].first);
				}
			}

			pw *= 2;
		}

		for (int i = 0; i < n; ++i)
		{
			inv[sa[i]] = i;
		}
		lcp.assign(size(s), 0);
		int cnt = 0;

		for (int i = 0; i < size(s) - 1; ++i)
		{
			int j = sa[inv[i] - 1];
			
			while (s[i + cnt] == s[j + cnt])
			{
				++cnt;
			}
			lcp[inv[i]] = cnt;

			cnt -= cnt != 0;
		}

		int p = 1, k = 1;
		while (p < size(lcp))
		{
			p *= 2;
			++k;
		}

		st.assign(k, vector<int>(size(lcp)));
		for (int i = 0; i < size(lcp); ++i)
		{
			st[0][i] = lcp[i];
		}
		for (int i = 1, d = 1; i < k; ++i, d *= 2)
		{
			for (int j = 0; j + d < n; ++j)
			{
				st[i][j] = min(st[i - 1][j], st[i - 1][j + d]);
			}
		}
	}

	int get_lcp(int i) 
	{
		return lcp[i];
	}
	int get_lcp(int l, int r)
	{
		if (l > r)
		{
			swap(l, r);
		}
		++l, ++r;

		size_t d = bit_floor(size_t(r - l));
		int layer = countr_zero(d);
		return min(st[layer][l], st[layer][r - d]);
	}

	static string largestCommonSubstring(const string &s1, const string &s2)
	{
		const int n1 = size(s1);
		const int n2 = size(s2);
		const char DELIMETER = 1;
		SuffixArray sa(s1 + DELIMETER + s2);
		int mx = 0, pos = 0;
		
		for (int i = 0; i < n1 + n2; ++i)
		{
			if ((sa[i] < n1) xor (sa[i + 1] < n1))
			{
				int lcp = sa.get_lcp(i + 1);
				if (lcp > mx)
				{
					mx = lcp;
					pos = sa[i];
				}
			}
		}

		return s1.substr(pos, mx);
	}
};