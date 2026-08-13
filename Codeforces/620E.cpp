/*************************
  Author: Defy logic guy
  22:35:06 - 13/08/2026
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
#define NAME "620E"

struct Segtree
{
    int n;
    vector<int> tree, lazy;
    Segtree(int n = 0) : n(n) { tree.assign(4 * n, 0),
                                lazy.assign(4 * n, 0); }
    void propagate(int idx, int l, int r)
    {
        if (lazy[idx] == 0)
            return;
        tree[idx] = lazy[idx];
        if (l != r)
            lazy[idx << 1] = lazy[idx << 1 | 1] = lazy[idx];
        lazy[idx] = 0;
    }
    void upd(int idx, int l, int r, int ql, int qr, int x)
    {
        propagate(idx, l, r);
        if (qr < l or r < ql)
            return;
        if (ql <= l and r <= qr)
        {
            lazy[idx] = (1ll << x), tree[idx] = (1ll << x);
            return;
        }
        int m = l + r >> 1;
        upd(idx << 1, l, m, ql, qr, x);
        upd(idx << 1 | 1, m + 1, r, ql, qr, x);
        tree[idx] = (tree[idx << 1] | tree[idx << 1 | 1]);
    }
    int get(int idx, int l, int r, int ql, int qr)
    {
        propagate(idx, l, r);
        if (qr < l or r < ql)
            return 0;
        if (ql <= l and r <= qr)
            return tree[idx];
        int m = l + r >> 1;
        return (get(idx << 1, l, m, ql, qr) |
                get(idx << 1 | 1, m + 1, r, ql, qr));
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> c(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y), adj[y].pb(x);
    }
    int timer = 0;
    vector<int> tin(n + 1, 0), tout(n + 1, 0);
    auto dfs = [&](auto &&dfs, int u) -> void
    {
        tin[u] = ++timer;
        for (int v : adj[u])
            if (!tin[v])
                dfs(dfs, v);
        tout[u] = timer;
    };
    dfs(dfs, 1);
    cerr << tin << '\n'
         << tout;
    Segtree st(n);
    for (int i = 1; i <= n; i++)
        st.upd(1, 1, n, tin[i], tin[i], c[i] - 1);
    while (q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int x, y;
            cin >> x >> y;
            st.upd(1, 1, n, tin[x], tout[x], y - 1);
        }
        else
        {
            int x;
            cin >> x;
            cout << __builtin_popcountll(st.get(1, 1, n, tin[x], tout[x])) << '\n';
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
