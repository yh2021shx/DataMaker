#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 7;
const long long mod = 998244353, iv2 = 499122177;

int t, id;
long long n, m;
long long c[N], fac[N], inv[N];

long long ksm(long long x, long long y = mod - 2) {
    long long res = 1;
    for (; y; y >>= 1, (x *= x) %= mod)
        if (y & 1)
            (res *= x) %= mod;
    return res;
}

long long read() {
    long long x = 0, k = 1; char c = getchar();
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    if (c == '-') k = -1, c = getchar();
    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return x * k;
}

void solve() {
    n = read(), m = read();
    if (min(n, m) == 1) {
        cout << 1 << '\n';
        return ;
    }
    c[0] = 1;
    for (int t = 1; t <= m - 1; t ++) {
        long long x = n + t - 2, y = n - 2;
        c[t] = c[t - 1] * (x % mod) % mod * inv[x - y] % mod;
    }
    long long ret = ksm(2ll, n * m - n - m + 1), ans = 0;
    for (long long t = 0; t <= m - 1; t ++) {
        (ans += ret * c[t] % mod) %= mod;
        (ret *= iv2) %= mod;
    }
    cout << ans << '\n';
}

signed main() {
    fac[0] = 1; n = 1000000;
    for (int i = 1; i <= n; i ++)
        fac[i] = fac[i - 1] * i % mod;
    inv[n] = ksm(fac[n]);
    for (int i = n - 1; i >= 0; i --) 
        inv[i] = inv[i + 1] * (i + 1) % mod;
    for (int i = n; i >= 1; i --) 
        inv[i] = inv[i] * fac[i - 1] % mod;
    t = read(), id = read();
    while (t --) solve();
    return 0;
}
