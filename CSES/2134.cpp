/*************************
  Author: Defy logic guy
  20:36:57 - 30/07/2026
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
#define NAME "2134"

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
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<int> head(n + 1, -1), id(n + 1), arr(n + 1), pos(n + 1), sz(n + 1, 1),
        d(n + 1), par(n + 1);
    d[1] = 1;
    auto dfs = [&](auto &&self, int u, int p) -> void
    {
        for (int v : adj[u])
            if (v != p)
            {
                par[v] = u;
                d[v] = d[u] + 1;
                self(self, v, u);
                sz[u] += sz[v];
            }
    };
    dfs(dfs, 1, 0);
    int cur = 1, curpos = 1;
    auto hld = [&](auto &&self, int u, int p) -> void
    {
        if (head[cur] == -1)
            head[cur] = u;
        id[u] = cur, pos[u] = curpos, arr[curpos++] = u;
        int nxt = 0;
        for (int v : adj[u])
            if (v != p)
                if (!nxt or sz[v] > sz[nxt])
                    nxt = v;
        if (nxt)
            self(self, nxt, u);
        for (int v : adj[u])
            if (v != p and v != nxt)
            {
                cur++;
                self(self, v, u);
            }
    };
    hld(hld, 1, 0);
    vector<int> tree(2 * n + 1, 0);
    auto upd = [&](int p, int val)
    {
        for (tree[p += n] = val; p > 1; p >>= 1)
            tree[p >> 1] = max(tree[p], tree[p ^ 1]);
    };
    for (int i = 1; i <= n; i++)
        upd(pos[i] - 1, a[i]);
    auto get = [&](int u, int v)
    {
        int res = 0;
        while (id[u] != id[v])
        {
            if (d[head[id[u]]] < d[head[id[v]]])
                swap(u, v);
            int l = pos[head[id[u]]] - 1, r = pos[u];
            for (l += n, r += n; l < r; l >>= 1, r >>= 1)
            {
                if (l & 1)
                    res = max(res, tree[l++]);
                if (r & 1)
                    res = max(res, tree[--r]);
            }
            u = par[head[id[u]]];
        }
        if (d[u] > d[v])
            swap(u, v);
        int l = pos[u] - 1, r = pos[v];
        for (l += n, r += n; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                res = max(res, tree[l++]);
            if (r & 1)
                res = max(res, tree[--r]);
        }
        return res;
    };
    while (q--)
    {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 1)
            upd(pos[u] - 1, v);
        else
            cout << get(u, v) << ' ';
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
