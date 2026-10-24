/*************************
  Author: Defy logic guy
  19:42:46 - 09/10/2026
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
#define NAME "TV"

struct Fenwreck
{
    int n;
    vector<int> a;
    Fenwreck(int n = 0) : n(n) { a.assign(n + 1, 0); }
    void upd(int idx, int x)
    {
        while (idx <= n)
            a[idx] += x, idx += idx & -idx;
    }
    int get(int idx)
    {
        int ans = 0;
        while (idx > 0)
            ans += a[idx], idx -= idx & -idx;
        return ans;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> c(n);
    for (int i = 0; i < n; i++)
        cin >> c[i];
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u - 1].pb(v - 1);
        adj[v - 1].pb(u - 1);
    }
    int q;
    cin >> q;
    vector<vector<pair<int, int>>> qry(n);
    for (int i = 0; i < q; i++)
    {
        int v, k;
        cin >> v >> k;
        qry[v - 1].pb(k, i);
    }
    vector<int> sz(n, 1), heavy(n, -1), tin(n), tout(n), e(n);
    int timer = 0;
    function<void(int, int)> dfs = [&](int u, int p)
    {
        tin[u] = timer;
        e[timer++] = u;
        int mx = 0;
        for (int v : adj[u])
        {
            if (v == p)
                continue;
            dfs(v, u);
            sz[u] += sz[v];
            if (sz[v] > mx)
            {
                mx = sz[v];
                heavy[u] = v;
            }
        }
        tout[u] = timer - 1;
    };
    dfs(0, -1);
    Fenwreck bit(n);
    vector<int> freq(n + 1, 0), ans(q, 0);
    int cnt = 0;
    auto add = [&](int u, int delta)
    {
        int x = c[u];
        int old = freq[x];
        if (old > 0)
            bit.upd(old, -1);
        else
            cnt++;
        freq[x] += delta;
        int now = freq[x];
        if (now > 0)
            bit.upd(now, 1);
        else
            cnt--;
    };
    auto addSubtree = [&](int u, int delta)
    {
        for (int i = tin[u]; i <= tout[u]; i++)
            add(e[i], delta);
    };
    function<void(int, int, bool)> sack = [&](int u, int p, bool keep)
    {
        for (int v : adj[u])
        {
            if (v == p or v == heavy[u])
                continue;
            sack(v, u, false);
        }
        if (heavy[u] != -1)
            sack(heavy[u], u, true);
        for (int v : adj[u])
        {
            if (v == p or v == heavy[u])
                continue;
            addSubtree(v, 1);
        }
        add(u, 1);
        for (auto [k, id] : qry[u])
            ans[id] = cnt - bit.get(k - 1);
        if (!keep)
            addSubtree(u, -1);
    };
    sack(0, -1, true);
    for (int i = 0; i < q; i++)
        cout << ans[i] << ' ';
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
