/*************************
  Author: Defy logic guy
  21:09:23 - 29/08/2026
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
#define NAME "UPGRANET"

struct DSU
{
    vector<int> par, sz;
    DSU(int n = 0)
    {
        par.resize(n + 1);
        iota(all(par), 0);
        sz.assign(n + 1, 1);
    }
    int find(int x) { return par[x] = (par[x] == x ? x : find(par[x])); }
    bool same(int x, int y) { return find(x) == find(y); }
    void uni(int x, int y)
    {
        x = find(x), y = find(y);
        if (x == y)
            return;
        if (sz[x] < sz[y])
            swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
    }
};

struct edge
{
    int u, v, w, id;
    bool operator<(const edge &o) const { return w > o.w; }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<edge> e(m);
    for (int i = 0; i < m; i++)
    {
        cin >> e[i].u >> e[i].v >> e[i].w;
        e[i].id = i;
    }
    vector<edge> se = e;
    sort(all(se));
    DSU dsu(n);
    vector<vector<pair<int, int>>> tree(n + 1);
    vector<bool> vis(m, false);
    for (const auto &i : se)
        if (!dsu.same(i.u, i.v))
        {
            dsu.uni(i.u, i.v);
            tree[i.u].pb(i.v, i.w);
            tree[i.v].pb(i.u, i.w);
            vis[i.id] = true;
        }
    int LOG = 20;
    vector<vector<int>> up(LOG, vector<int>(n + 1, 0));
    vector<vector<int>> mn(LOG, vector<int>(n + 1, LLONG_MAX));
    vector<int> h(n + 1, 0);
    function<void(int, int, int)> dfs = [&](int u, int p, int w)
    {
        up[0][u] = p, mn[0][u] = w;
        h[u] = h[p] + 1;
        for (auto &v : tree[u])
            if (v.first != p)
                dfs(v.first, u, v.second);
    };
    for (int i = 1; i <= n; i++)
        if (h[i] == 0)
            dfs(i, 0, LLONG_MAX);
    for (int k = 1; k < LOG; k++)
        for (int v = 1; v <= n; v++)
        {
            up[k][v] = up[k - 1][up[k - 1][v]];
            mn[k][v] = min(mn[k - 1][v], mn[k - 1][up[k - 1][v]]);
        }
    auto pathMin = [&](int u, int v)
    {
        if (h[u] < h[v])
            swap(u, v);
        int res = LLONG_MAX;
        for (int k = LOG - 1; k >= 0; k--)
            if (h[u] - (1 << k) >= h[v])
            {
                res = min(res, mn[k][u]);
                u = up[k][u];
            }
        if (u == v)
            return res;
        for (int k = LOG - 1; k >= 0; k--)
            if (up[k][u] != up[k][v])
            {
                res = min({res, mn[k][u], mn[k][v]});
                u = up[k][u];
                v = up[k][v];
            }
        return min({res, mn[0][u], mn[0][v]});
    };
    int ans = 0;
    for (const auto &i : e)
        if (!vis[i.id])
            ans += pathMin(i.u, i.v) - i.w;
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
