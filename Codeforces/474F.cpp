/*************************
  Author: Defy logic guy
  19:43:25 - 08/08/2026
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
#define NAME "474F"

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    map<int, vector<int>> mp;
    for (int i = 1; i <= n; i++)
        mp[a[i]].pb(i);
    vector<vector<int>> st(21, vector<int>(n + 1));
    for (int i = 1; i <= n; i++)
        st[0][i] = a[i];
    vector<int> lg(n + 2);
    lg[1] = 0;
    for (int i = 2; i <= n + 1; i++)
        lg[i] = lg[i / 2] + 1;
    for (int i = 1; i < 21; i++)
        for (int j = 1; j + (1 << i) <= n + 1; j++)
            st[i][j] = __gcd(st[i - 1][j], st[i - 1][j + (1ll << (i - 1))]);
    auto get = [&](int l, int r) -> int
    {
        int k = lg[r - l + 1];
        return __gcd(st[k][l], st[k][r - (1ll << k) + 1]);
    };
    int t;
    cin >> t;
    while (t--)
    {
        int l, r;
        cin >> l >> r;
        int i = get(l, r);
        cout << r - l + 1 - (upper_bound(all(mp[i]), r) - lower_bound(all(mp[i]), l)) << '\n';
    }
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
