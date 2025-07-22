template<class T>
class FFT
{
private:
    using fpt = double;
    using cmpl = complex<fpt>;
    inline static const fpt PI = acos(-1);
    FFT() = delete;
private:
    static void fft(vector<cmpl> &P, bool is_inverse)
    {
        const int n = size(P);
 
        for (int i = 1, j = 0; i < n; ++i)
        {
            int bit = n >> 1;
            while (bit & j)
            {
                j ^= bit;
                bit >>= 1;
            }
            j ^= bit;
 
            if (i < j)
            {
                swap(P[i], P[j]);
            }
        }
 
        for (int d = 2; d <= n; d *= 2)
        {
            const fpt angle = is_inverse ? -2 * PI / d : 2 * PI / d;
            const cmpl step(cos(angle), sin(angle));
            for (int i = 0; i < n; i += d)
            {
                cmpl w(1);
                for (int j = 0; j < d / 2; ++j)
                {
                    cmpl a = P[i + j];
                    cmpl b = w * P[i + d / 2 + j];
                    P[i + j] = a + b;
                    P[i + d / 2 + j] = a - b;
                    w *= step;
                }
            }
        }
        if (is_inverse)
        {
            fpt invn = fpt(1) / n;
            for (cmpl &x : P)
            {
                x *= invn;
            }
        }
    }
    static void evaluate(vector<cmpl> &P)
    {
        const bool is_inverse = false;
        fft(P, is_inverse);
    }
    static void interpolate(vector<cmpl> &P)
    {
        const bool is_inverse = true;
        fft(P, is_inverse);
    }
public:
    static vector<T> multiply(const vector<T> &P, const vector<T> &Q)
    {
        int n = bit_ceil(size(P) + size(Q) - 1);
 
        vector<cmpl> P_cmpl(n), Q_cmpl(n);
        copy(begin(P), end(P), begin(P_cmpl));
        copy(begin(Q), end(Q), begin(Q_cmpl));
 
        evaluate(P_cmpl);
        evaluate(Q_cmpl);
        vector<cmpl> R_cmpl(n);
        for (int i = 0; i < n; ++i)
        {
            R_cmpl[i] = P_cmpl[i] * Q_cmpl[i];
        }
        interpolate(R_cmpl);
 
        n = size(P) + size(Q) - 1;
        vector<T> R(n);
        for (int i = 0; i < n; ++i)
        {
            R[i] = round(R_cmpl[i].real());
        }
        return R;
    }
};


template<ll MOD> // MOD = 998244353
class FFT
{
private:
    FFT() = delete;
    inline static ll g = -1;
private:
    static ll pow (ll x, ll pw)
    {
        ll res = 1;
        while (pw)
        {
            if (pw & 1)
            {
                res = res * x % MOD;
            }
            x = x * x % MOD;
            pw >>= 1;
        }
        return res;
    }
    static ll inv (ll x)
    {
        return pow(x, MOD - 2);
    }
    static void generator ()
    {
        if (g == -1)
        {
            vector<ll> p;
            ll phi = MOD - 1;
            ll n = phi;
            if (n % 2 == 0)
            {
                p.push_back(2);
                while (n % 2 == 0)
                {
                    n /= 2;
                }
            }
            for (ll i = 3; i * i <= n; i += 2)
            {
                if (n % i == 0)
                {
                    p.push_back(i);
                    while (n % i == 0)
                    {
                        n /= i;
                    }
                }
            }
            if (n > 1)
            {
                p.push_back(n);
            }
 
            for (ll res = 2; res < MOD; ++res)
            {
                bool f = true;
                for (ll x : p)
                {
                    if (pow(res, phi / x) == 1)
                    {
                        f = false;
                        break;
                    }
                }
                if (f)
                {
                    g = res;
                    return;
                }
            }
 
            throw "can't find primal root";
        }
    }
    static void fft(vector<ll> &P, const bool is_inverse)
    {
        const int n = size(P);
 
        for (int i = 1, j = 0; i < n; ++i)
        {
            int bit = n >> 1;
            while (bit & j)
            {
                j ^= bit;
                bit >>= 1;
            }
            j ^= bit;
 
            if (i < j)
            {
                swap(P[i], P[j]);
            }
        }
 
        for (int d = 2; d <= n; d *= 2)
        {
            const ll step = pow(g, is_inverse ? (MOD - 1) - (MOD - 1) / d : (MOD - 1) / d);
            for (int i = 0; i < n; i += d)
            {
                ll w = 1;
                for (int j = 0; j < d / 2; ++j)
                {
                    ll a = P[i + j];
                    ll b = w * P[i + d / 2 + j];
                    P[i + j] = (a + b) % MOD;
                    P[i + d / 2 + j] = a - b % MOD;
                    P[i + d / 2 + j] += P[i + d / 2 + j] < 0 ? MOD : 0;
                    w = w * step % MOD;
                }
            }
        }
        if (is_inverse)
        {
            ll invn = inv(n);
            for (ll &x : P)
            {
                x = x * invn % MOD;
            }
        }
    }
    static void evaluate (vector<ll> &P)
    {
        const bool is_inverse = false;
        fft(P, is_inverse);
    }
    static void interpolate (vector<ll> &P)
    {
        const bool is_inverse = true;
        fft(P, is_inverse);
    }
public:
    static vector<ll> multiply(vector<ll> P, vector<ll> Q)
    {
        generator();
        int n = bit_ceil(size(P) + size(Q) - 1);
        if ((MOD - 1) % n)
        {
            throw "can't use given module";
        }
 
        P.resize(n);
        Q.resize(n);
 
        evaluate(P);
        evaluate(Q);
        vector<ll> R(n);
        for (int i = 0; i < n; ++i)
        {
            R[i] = P[i] * Q[i] % MOD;
        }
        interpolate(R);
 
        n = size(P) + size(Q) - 1;
        R.resize(n);
        return R;
    }
};