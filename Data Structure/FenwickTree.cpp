struct BIT {
    const int N;
    vector<ll> d, dd;
    BIT(int n) : N(n) {
        d.assign(N + 2, 0);
        dd.assign(N + 2, 0);
    }
    ll query(int index) {
        index++;
        ll s = 0, ss = 0;
        ll c = index + 1;
        while (index > 0) {
            s += d[index], ss += dd[index];
            index -= index & -index;
        }
        return c * s - ss;
    }
    void add(int index, ll val) {
        index++;
        int c = index;
        while (index <= N) {
            d[index] += val, dd[index] += c * val;
            index += index & -index;
        }
    }
    // Query sum in [left_inc, right_inc]
    ll query(int left_inc, int right_inc) { return query(right_inc) - query(left_inc - 1); }
    // Increase all elements in [left_inc, right_inc] by val
    void add(int left_inc, int right_inc, ll val) { add(left_inc, val), add(right_inc + 1, -val); }
};