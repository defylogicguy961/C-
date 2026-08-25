/*************************
  Author: Defy logic guy
  15:36:21 - 20/08/2026
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
#define NAME "SEABR"

void solve()
{
    int n, k, x, y;
    cin >> n >> k >> x >> y;
    map<pair<int, int>, int> mp;
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 1; i < n; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb(v, w), adj[v].pb(u, w);
        mp[{u, v}] = mp[{v, u}] = i;
    }
    vector<int> sz(n + 1, 0);
    vector<pair<int, int>> ans;
    auto dfs = [&](auto &&dfs, int u, int p) -> void
    {
        for (auto [v, w] : adj[u])
            if (v != p)
            {
                dfs(dfs, v, u);
                ans.pb(sz[v] * (n - sz[v]) * w, mp[{u, v}]);
                sz[u] += sz[v];
            }
        sz[u]++;
    };
    dfs(dfs, 1, 0);
    sort(rall(ans));
    for (int i = 0; i < k; i++)
        cout << ans[i].second << '\n';
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
