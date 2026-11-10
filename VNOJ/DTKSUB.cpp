/*************************
  Author: Defy logic guy
  21:38:06 - 07/11/2026
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
#define MOD1 1000000007
#define MOD2 1000000009
#define NAME "DTKSUB"

const int base1 = 311, base2 = 317;
void solve()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> h1(n + 1, 0), h2(n + 1, 0), p1(n + 1, 1), p2(n + 1, 1);
    for (int i = 0; i < n; i++)
    {
        h1[i + 1] = (h1[i] * base1 + s[i]) % MOD1;
        h2[i + 1] = (h2[i] * base2 + s[i]) % MOD2;
        p1[i + 1] = p1[i] * base1 % MOD1;
        p2[i + 1] = p2[i] * base2 % MOD2;
    }
    int l = 0, r = n;
    int ans = 0;
    while (l <= r)
    {
        int m = l + r >> 1;
        auto f = [&]()
        {
            map<int, int> mp;
            for (int i = 0; i + m <= n; i++)
            {
                int x = (h1[i + m] - h1[i] * p1[m] % MOD1 + MOD1) % MOD1;
                int y = (h2[i + m] - h2[i] * p2[m] % MOD2 + MOD2) % MOD2;
                if (++mp[x * MOD2 + y] >= k)
                    return true;
            }
            return false;
        };
        if (f())
            ans = m, l = m + 1;
        else
            r = m - 1;
    }
    cout << ans << '\n';
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
    // cin >> tt;

    while (tt--)
        solve();

    return 0;
}
