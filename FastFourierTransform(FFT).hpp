class FFT
{
private:
    using cmpl = complex<double>;
    vector<cmpl> w;
private:
    void evaluate(vector<cmpl> &P) const
    {
        const int n = size(P);
        if (n == 1)
        {
            return;
        }

        vector<cmpl> P_even(n / 2);
        vector<cmpl> P_odd(n / 2);
        for (int i = 0; i < n / 2; ++i)
        {
            P_even[i] = P[i * 2];
            P_odd[i] = P[i * 2 + 1];
        }

        evaluate(P_even);
        evaluate(P_odd);

        const int step = size(w) / n;
        vector<cmpl> P_val(n);
        for (int i = 0; i < n / 2; ++i)
        {
            P[i] = P_even[i] + w[step * i] * P_odd[i];
            P[i + n / 2] = P_even[i] - w[step * i] * P_odd[i];
        }
    }
    void interpolate(vector<cmpl> &P) const
    {
        const int n = size(P);
        if (n == 1)
        {
            return;
        }

        const int step = size(w) / n;
        vector<cmpl> P_even(n / 2);
        vector<cmpl> P_odd(n / 2);
        for (int i = 0; i < n / 2; ++i)
        {
            P_even[i] = (P[i] + P[i + n / 2]) / cmpl(2);
            P_odd[i] = (P[i] - P[i + n / 2]) / (cmpl(2) * w[step * i]);
        }

        interpolate(P_even);
        interpolate(P_odd);

        for (int i = 0; i < n / 2; ++i)
        {
            P[i * 2] = P_even[i];
            P[i * 2 + 1] = P_odd[i];
        }
    }
public:
    vector<ll> multiply(const vector<ll> &P, const vector<ll> &Q)
    {
        int n = bit_ceil(size(P) + size(Q) - 1);

        vector<cmpl> P_cmpl(n), Q_cmpl(n);
        copy(begin(P), end(P), begin(P_cmpl));
        copy(begin(Q), end(Q), begin(Q_cmpl));
        w.resize(n);
        w[0] = 1;
        if (n > 1)
        {
            const double PI = acos(-1);
            w[1] = cmpl(cos(2 * PI / n), sin(2 * PI / n));
            for (int i = 2; i < n; ++i)
            {
                w[i] = w[i - 1] * w[1];
            }
        }

        evaluate(P_cmpl);
        evaluate(Q_cmpl);
        vector<cmpl> R_cmpl(n);
        for (int i = 0; i < n; ++i)
        {
            R_cmpl[i] = P_cmpl[i] * Q_cmpl[i];
        }
        interpolate(R_cmpl);

        n = size(P) + size(Q) - 1;
        vector<ll> R(n);
        for (int i = 0; i < n; ++i)
        {
            R[i] = round(R_cmpl[i].real());
        }
        return R;
    }
};