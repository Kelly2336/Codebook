// Query phi(x)
int phi(int x) {
    int ret = x;
    for (int p = 2; p * p <= x; ++p) {
        if (x % p == 0) {
            while (x % p == 0) x /= p;
            ret -= ret / p;
        }
    }
    if (x > 1) ret -= ret / x;
    return ret;
}

// Query all phi(x) where x in [0, x)
vector<int> phi_in(int x) {
    vector<bool> prime(x, 1);
    vector<int> ret(x);
    prime[0] = prime[1] = false;
    for (int i = 0; i < x; i++) ret[i] = i;
    for (int i = 2; i < x; i++) {
        if (!prime[i]) continue;
        ret[i]--;
        for (int j = i * 2; j < x; j += i) {
            prime[j] = false;
            ret[j] = ret[j] / i * (i - 1);
        }
    }
    ret[1] = 0;
    return ret;
}
