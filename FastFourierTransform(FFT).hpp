template<class T>
class FFT
{
private:
    using cmpl = complex<double>;
    static const double PI;
    FFT() = delete;
private:
    static void evaluate(vector<cmpl> &P)
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
            const double angle = 2 * PI / d;
            const cmpl step(cos(angle), sin(angle));
            for (int i = 0; i < n; i += d)
            {
                cmpl w(1);
                for (int j = 0; j < d / 2; ++j)
                {
                    cmpl even = P[i + j];
                    cmpl odd  = P[i + d / 2 + j];
                    P[i + j]         = even + w * odd;
                    P[i + d / 2 + j] = even - w * odd;
                    w *= step;
                }
            }
        }
    }
    static void interpolate(vector<cmpl> &P)
    {
        const int n = size(P);

        for (int d = n; d >= 2; d /= 2)
        {
            const double angle = 2 * PI / d;
            const cmpl step(cos(angle), sin(angle));
            for (int i = 0; i < n; i += d)
            {
                cmpl w(1);
                for (int j = 0; j < d / 2; ++j)
                {
                    cmpl pos = P[i + j];
                    cmpl neg = P[i + d / 2 + j];
                    P[i + j]         = (pos + neg) / (cmpl(2));
                    P[i + d / 2 + j] = (pos - neg) / (cmpl(2) * w);
                    w *= step;
                }
            }
        }

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
template<class T> 
const double FFT<T>::PI = acos(-1);