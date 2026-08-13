/*************************
  Author: Defy logic guy
  20:27:29 - 04/08/2026
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
#define NAME "SECONDTHRED_TREE_FLOW"

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<vector<int>>
        up(n + 1, vector<int>(19)),
        flow(n + 1, vector<int>(19));
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
    }
    vector<int> h(n + 1, 0);
    auto dfs = [&](auto &&dfs, int u) -> void
    {
        for (auto [v, w] : adj[u])
            if (!h[v])
            {
                h[v] = h[u] + 1, up[v][0] = u, flow[v][0] = w;
                dfs(dfs, v);
            }
    };
    h[1] = 1, flow[1][0] = INT_MAX;
    dfs(dfs, 1);
    for (int j = 1; j < 19; j++)
        for (int i = 1; i <= n; i++)
            up[i][j] = up[up[i][j - 1]][j - 1],
            flow[i][j] = min(flow[i][j - 1], flow[up[i][j - 1]][j - 1]);
    auto get = [&](int u, int v) -> int
    {
        if (h[u] > h[v])
            swap(u, v);
        int ans = INT_MAX, k = h[v] - h[u];
        for (int i = 0; i < 19; i++)
            if (k >> i & 1)
                ans = min(ans, flow[v][i]), v = up[v][i];
        if (v == u)
            return ans;
        for (int i = 18; i >= 0; i--)
            if (up[u][i] != up[v][i])
                ans = min({ans, flow[u][i], flow[v][i]}),
                u = up[u][i], v = up[v][i];
        return min({ans, flow[u][0], flow[v][0]});
    };
    int q;
    cin >> q;
    while (q--)
    {
        int a, b;
        cin >> a >> b;
        cout << get(a, b) << '\n';
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
