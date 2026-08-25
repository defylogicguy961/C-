/*************************
  Author: Defy logic guy
  19:03:22 - 21/08/2026
*************************/
#include <bits/stdc++.h>
using namespace std;
ostream &operator<<(ostream &os, const string &s)
{
    os.write(s.data(), s.size());
    return os;
}
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.first << ", " << p.second << ")"; }
template <typename T>
auto operator<<(ostream &os, const T &c) -> typename enable_if<!is_same<T, string>::value, decltype(c.begin(), c.end(), os)>::type
{
    for (auto it = c.begin(); it != c.end(); it++)
        os << (it == c.begin() ? "{" : ", ") << *it;
    return os << "}";
}
#define dbg(x) cerr << #x << " = " << (x) << '\n';
#define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define maxall(x) *max_element(all(x))
#define minall(x) *min_element(all(x))
#define heap priority_queue
#define pb emplace_back
#define MOD 1000000007
#define NAME "HATS"

const int maxn = 1e6 + 5;
int f[maxn], invf[maxn], ans[maxn];

int binpow(int b, int e)
{
    int res = 1;
    while (e)
    {
        if (e & 1)
            res = (res * b) % MOD;
        b = (b * b) % MOD;
        e >>= 1;
    }
    return res;
}

void pre()
{
    f[0] = invf[0] = 1;
    for (int i = 1; i < maxn; ++i)
    {
        f[i] = f[i - 1] * i % MOD;
        invf[i] = binpow(f[i], MOD - 2);
    }
    ans[1] = 0;
    for (int i = 2; i < maxn; i++)
        if (i & 1)
            ans[i] = (ans[i - 1] - invf[i] + MOD) % MOD;
        else
            ans[i] = (ans[i - 1] + invf[i]) % MOD; 
}

void solve()
{
    int n;
    cin >> n;
    cout << ans[n] << '\n';
}

signed main()
{
    if (fopen(NAME ".INP", "r"))
    {
        freopen(NAME ".INP", "r", stdin);
        freopen(NAME ".OUT", "w", stdout);
    }

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tt = 1;
    cin >> tt;

    pre();

    while (tt--)
        solve();

    return 0;
}
