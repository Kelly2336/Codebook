#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct BIT {
    int N;
    vector<ll> bitarray;
    BIT(int n) : N(n) { bitarray.assign(N + 1, 0); }
    // update single value
    void add(int index, ll val) {
        index++;
        while (index <= N) bitarray[index] += val, index += index & -index;
    }
    // query range [0, index]
    ll query(int index) {
        index++;
        ll ret = 0;
        while (index > 0) ret += bitarray[index], index -= index & -index;
        return ret;
    }
    // query range [left_inc, right_inc]
    ll query(int left_inc, int right_inc) { return query(right_inc) - query(left_inc - 1); }
};