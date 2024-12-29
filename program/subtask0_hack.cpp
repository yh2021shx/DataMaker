#include <bits/stdc++.h>
using namespace std;

mt19937_64 rnd(time(0));

long long f(long long l, long long r) {
    return rnd() % (r - l + 1) + l;
}

signed main() {
    int t = 30;
    cout << t << ' ' << 1 << '\n';
    while (t --) {
        long long n = 2, m = 9;
        cout << n << ' ' << m << '\n';
    }
    return 0;
}
