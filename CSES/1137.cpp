/*************************
  Author: Defy logic guy
  07:40:56 - 07/08/2026
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
#define NAME "1137"

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v), adj[v].pb(u);
    }
    int timer = 1;
    vector<int> v(n + 1, 0), tin(n + 1), tout(n + 1);
    auto dfs = [&](auto dfs, int u, int p) -> void
    {
        tin[u] = timer;
        for (int child : adj[u])
            if (child != p)
            {
                timer++;
                dfs(dfs, child, u);
            }
        tout[u] = timer;
    };
    dfs(dfs, 1, 0);
    auto upd = [&](int idx, int x) -> void
    {
        while (idx <= n)
            v[idx] += x, idx += idx & -idx;
    };
    auto get = [&](int idx) -> int
    {
        int ans = 0;
        while (idx)
            ans += v[idx], idx -= idx & -idx;
        return ans;
    };
    for (int i = 1; i <= n; i++)
        upd(tin[i], a[i]);
    while (q--)
    {
        int t, s;
        cin >> t >> s;
        if (t == 1)
        {
            int x;
            cin >> x;
            int cur = get(tin[s]) - get(tin[s] - 1);
            upd(tin[s], x - cur);
        }
        else
            cout << get(tout[s]) - get(tin[s] - 1) << '\n';
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
