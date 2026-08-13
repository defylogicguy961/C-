/*************************
  Author: Defy logic guy
  19:36:57 - 08/08/2026
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
#define pb push_back
#define MOD 1000000007
#define NAME "2050F"

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    if (n == 1)
    {
        while (q--)
        {
            int l, r;
            cin >> l >> r;
            cout << "0 ";
        }
        cout << '\n';
        return;
    }
    vector<int> d(n - 1);
    for (int i = 0; i < n - 1; i++)
        d[i] = abs(a[i + 1] - a[i]);
    int m = d.size();
    vector<vector<int>> st(32 - __builtin_clz(m), vector<int>(m));
    st[0] = d;
    for (int j = 1; j < 32 - __builtin_clz(m); j++)
        for (int i = 0; i + (1 << j) <= m; i++)
            st[j][i] = __gcd(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        if (l == r)
        {
            cout << "0 ";
            continue;
        }
        int k = 31 - __builtin_clz(r - l);
        int pos2 = r - 1 - (1 << k);
        int g = __gcd(st[k][l - 1], st[k][pos2]);
        cout << g << ' ';
    }
    cout << '\n';
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

    while (tt--)
        solve();

    return 0;
}
