/*************************
  Author: Defy logic guy
  20:21:08 - 05/09/2026
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
#define NAME "VR_MST_CGRAPH"

struct DSU
{
    DSU(int n = 0) { init(n); }
    vector<int> par, sz;
    void init(int n)
    {
        par.resize(n + 1);
        iota(all(par), 0);
        sz.assign(n + 1, 1);
    }
    int find(int x) { return par[x] = (par[x] == x ? x : find(par[x])); }
    int size(int x) { return sz[find(x)]; }
    bool same(int x, int y) { return find(x) == find(y); }
    void uni(int x, int y, int z)
    {
        x = find(x), y = find(y);
        if (x == y)
            return;
        par[x] = par[y] = z;
    }
};

struct qry
{
    int t, u, v, i;
};

void solve()
{
    int n, m;
    if (!(cin >> n >> m))
        return;

    DSU dsu(n + m + 1);
    vector<qry> q;
    int cnt = n;
    vector<int> val(n + m + 1, 0);
    vector<vector<int>> adj(n + m + 1);

    for (int i = 1; i <= m; i++)
    {
        int t, u, v;
        cin >> t >> u >> v;
        q.pb(t, u, v, i);
        if (t == 1)
        {
            u = dsu.find(u), v = dsu.find(v);
            if (u == v)
                continue;
            cnt++;
            val[cnt] = i;
            adj[cnt].pb(u), adj[cnt].pb(v);
            dsu.uni(u, v, cnt);
        }
    }
    vector<vector<int>> up(cnt + 1, vector<int>(21));
    vector<int> h(cnt + 1, 0);
    vector<bool> vis(cnt + 1, false);
    auto dfs = [&](auto &&dfs, int u, int p) -> void
    {
        vis[u] = true;
        up[u][0] = p;
        for (int i = 1; i <= 20; i++)
            up[u][i] = up[up[u][i - 1]][i - 1];
        for (int v : adj[u])
        {
            h[v] = h[u] + 1;
            dfs(dfs, v, u);
        }
    };
    for (int i = cnt; i >= 1; i--)
        if (!vis[i] and dsu.find(i) == i)
            dfs(dfs, i, i);
    auto lca = [&](int u, int v) -> int
    {
        if (h[u] < h[v])
            swap(u, v);
        int k = h[u] - h[v];
        for (int i = 20; i >= 0; i--)
            if (k >> i & 1)
                u = up[u][i];
        if (u == v)
            return u;
        for (int i = 20; i >= 0; i--)
            if (up[u][i] != up[v][i])
            {
                u = up[u][i];
                v = up[v][i];
            }
        return up[u][0];
    };
    for (auto &i : q)
        if (i.t == 2)
        {
            if (i.u == i.v)
            {
                cout << 0 << '\n';
                continue;
            }
            if (dsu.find(i.u) != dsu.find(i.v))
                cout << -1 << '\n';
            else
            {
                int t = lca(i.u, i.v);
                cout << (val[t] > i.i ? -1 : val[t]) << '\n';
            }
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
