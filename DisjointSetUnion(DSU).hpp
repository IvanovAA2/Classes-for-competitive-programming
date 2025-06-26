class dsu
{
private:
	vector<int> p;
public:
	dsu (int n) : p(n)
	{
		iota(begin(p), end(p), 0);
	}
	int get(int x) 
	{
		if (x == p[x]) 
		{
			return x;
		}
		
		return p[x] = get(p[x]);
	}
	void unite(int a, int b) 
	{
		a = get(a);
		b = get(b);

		if (rand() & 1)
		{
			swap(a, b);
		}
		
		p[a] = b;
	}
};