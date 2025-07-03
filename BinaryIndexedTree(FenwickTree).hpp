class Fenwick
{
    vector<ll> v, t;
public:
    Fenwick(int n) : v(n), t(n)
    { }
    void set(int i, ll x)
    {
        ll d = x - v[i];
        v[i] = x;
        while (i < size(t))
        {
            t[i] += d;
            i |= i + 1;
        }
    }
    ll get(int i)
    {
        ll sum = 0;
        while (i >= 0)
        {
            sum += t[i];
            i &= i + 1;
            --i;
        }
        
        return sum;
    }
};