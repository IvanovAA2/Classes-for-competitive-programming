vector<int> get_z_function(const string& to_find, const string& in_where) 
{
	const char DELIMETER = 0;
	string text = to_find + DELIMETER + in_where;

	return get_z_function(text);
}
vector<int> get_z_function (const string& s)
{
    int l = 0, r = 0, n = ssize(s);
    vector<int> z(n);
 
    for (int i = 1; i < n; ++i)
    {
        if (r > i)
        {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < n and s[i + z[i]] == s[z[i]])
        {
            ++z[i];
        }
        if (i + z[i] > r)
        {
            l = i;
            r = i + z[i];
        }
    }
 
    return z;
}

vector<int> get_kmp(const string& to_find, const string& in_where) 
{
	const char DELIMETER = 0;
	string text = to_find + DELIMETER + in_where;

	return get_kmp(text);
}
vector<int> get_kmp (const string& s)
{
    int n = ssize(s), cnt = 0;
    vector<int> kmp(n);
 
    for (int i = 1; i < n; ++i)
    {
        while (cnt > 0 and s[cnt] != s[i])
        {
            cnt = kmp[cnt - 1];
        }
        cnt += s[cnt] == s[i];
        kmp[i] = cnt;
    }
 
    return kmp;
}