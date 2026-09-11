/*************************
  Author: Defy logic guy
  19:46:05 - 08/09/2026
*************************/
#include <bits/stdc++.h>
using namespace std;
ostream &operator<<(ostream &os, const string &s)
{
    os.write(s.data(), s.size());
    return os;
}
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) { return os << "" << p.first << " " << p.second << "\n"; }
template <typename T>
auto operator<<(ostream &os, const T &c) -> typename enable_if<!is_same<T, string>::value, decltype(c.begin(), c.end(), os)>::type
{
    for (auto it = c.begin(); it != c.end(); it++)
        os << (it == c.begin() ? "" : " ") << *it;
    return os << "";
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
#define NAME "1245D"

void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i].first >> a[i].second;
    vector<int> c(n), k(n);
    for (int i = 0; i < n; i++)
        cin >> c[i];
    for (int i = 0; i < n; i++)
        cin >> k[i];
    vector<bool> vis(n, false);
    int ans = 0;
    vector<int> one, par(n, -1);
    vector<pair<int, int>> two;
    for (int _ = 0; _ < n; _++)
    {
        int mn = LLONG_MAX, t = -1;
        for (int i = 0; i < n; i++)
            if (!vis[i] and c[i] < mn)
                mn = c[i], t = i;
        vis[t] = true, ans += mn;
        if (par[t] == -1)
            one.pb(t + 1);
        else
            two.pb(min(par[t], t) + 1,
                   max(par[t], t) + 1);
        for (int i = 0; i < n; i++)
        {
            if (vis[i])
                continue;
            int d = abs(a[t].first - a[i].first) + abs(a[t].second - a[i].second);
            int cost = (k[t] + k[i]) * d;
            if (cost < c[i])
                c[i] = cost, par[i] = t;
        }
    }
    sort(all(one));
    cout << ans << '\n'
         << one.size() << '\n';
    for (int i : one)
        cout << i << ' ';
    cout << '\n'
         << two.size() << '\n';
    for (auto [u, v] : two)
        cout << u << ' ' << v << '\n';
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
