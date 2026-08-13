/*************************
  Author: Defy logic guy
  19:57:29 - 04/08/2026
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
#define NAME "SECONDTHRED_TREE_SLOTH"

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1), up(n + 1, vector<int>(19));
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v), adj[v].pb(u);
    }
    vector<int> h(n + 1, 0);
    auto dfs = [&](auto &&dfs, int u) -> void
    {
        for (int v : adj[u])
            if (!h[v])
            {
                h[v] = h[u] + 1, up[v][0] = u;
                dfs(dfs, v);
            }
    };
    h[1] = 1;
    dfs(dfs, 1);
    for (int j = 1; j < 19; j++)
        for (int i = 1; i <= n; i++)
            up[i][j] = up[up[i][j - 1]][j - 1];
    auto lca = [&](int u, int v) -> int
    {
        if (h[u] > h[v])
            swap(u, v);
        int k = h[v] - h[u];
        for (int i = 0; i < 19; i++)
            if (k >> i & 1)
                v = up[v][i];
        if (v == u)
            return u;
        for (int i = 18; i >= 0; i--)
            if (up[u][i] != up[v][i])
                u = up[u][i], v = up[v][i];
        return up[v][0];
    };
    auto jump = [&](int u, int k )-> int
    {
        for (int i = 18; i >= 0; i--)
            if (k >> i & 1)
                u = up[u][i];
        return u;
    };
    int q;
    cin >> q;
    while (q--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        int l = lca(a, b);
        int x = h[a] - h[l], y = h[b] - h[l];
        if (c >= x + y)
        {
            cout << b << '\n';
            continue;
        }
        if (c <= x)
            cout << jump(a, c) << '\n';
        else
            cout << jump(b, y - c + x) << '\n';
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
