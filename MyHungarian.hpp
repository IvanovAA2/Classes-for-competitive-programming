pair<vector<int>, ll> hungarian_min (const vector<vector<ll>>& a)
{
    int n = size(a), m = size(a[0]);
    vector<ll> addl(n), addr(m);
    for (int i = 0; i < n; ++i)
    {
        addl[i] = -ranges::min(a[i]);
    }
    vector<int> r(m, -1);
    for (int i = 0; i < n; ++i)
    {
        vector<bool> bpl(n), bpr(m);
        vector<ll> mn(m, 1e18);
        vector<int> where(m, -1);
        vector<int> from(n, -1), last(n);
        int row = i, column = 0;
        bool is_end = false;
        while (not is_end)
        {
            while (row != -1)
            {
                if (bpl[row])
                {
                    column = last[row] + 1;
                    row = from[row];
                    continue;
                }
                bpl[row] = true;
                for (int j = 0; j < m; ++j)
                {
                    if (a[row][j] + addl[row] + addr[j] < mn[j])
                    {
                        mn[j] = a[row][j] + addl[row] + addr[j];
                        where[j] = row;
                    }
                }

                bool go_back = true;
                while (column < m)
                {
                    if (bpr[column] == false and a[row][column] + addl[row] + addr[column] == 0)
                    {
                        bpr[column] = true;
                        go_back = false;
                        if (r[column] == -1)
                        {
                            while (row != -1)
                            {
                                r[column] = row;
                                column = last[row];
                                row = from[row];
                            }
                            is_end = true;
                        }
                        else
                        {
                            from[r[column]] = row;
                            last[r[column]] = column;
                            row = r[column];
                            column = 0;
                        }
                        break;
                    }
                    ++column;
                }

                if (go_back)
                {
                    column = last[row] + 1;
                    row = from[row];
                }
            }
            if (is_end)
            {
                break;
            }
            ll d = 1e18;
            for (int j = 0; j < m; ++j)
            {
                if (bpr[j] == false and mn[j] < d)
                {
                    d = mn[j];
                    row = where[j];
                }
            }
            for (int i = 0; i < n; ++i)
            {
                if (bpl[i])
                {
                    addl[i] -= d;
                }
            }
            for (int j = 0; j < m; ++j)
            {
                if (bpr[j])
                {
                    addr[j] += d;
                }
                else
                {
                    mn[j] -= d;
                }
            }
            bpl[row] = false;
            column = 0;
        }
    }
    vector<int> p(n);
    for (int i = 0; i < m; ++i)
    {
        if (r[i] != -1)
        {
            p[r[i]] = i;
        }
    }
    ll sm = 0;
    for (int i = 0; i < n; ++i)
    {
        sm += a[i][p[i]];
    }
    return {p, sm};
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
