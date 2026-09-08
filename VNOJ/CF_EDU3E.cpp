/*************************
  Author: Defy 19ic guy
  21:10:55 - 05/09/2026
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
#define NAME "CF_EDU3E"

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
    void uni(int x, int y)
    {
        x = find(x), y = find(y);
        if (x == y)
            return;
        par[y] = x;
        sz[x] += sz[y];
    }
};

struct edge
{
    int u, v, w, id;
};

const int N = 2e5 + 5;
int up[N][19], mx[N][19], h[N];
vector<pair<int, int>> adj[N];

void dfs(int u, int p, int w, int d)
{
    h[u] = d, up[u][0] = p, mx[u][0] = w;
    for (int i = 1; i < 19; i++)
    {
        up[u][i] = up[up[u][i - 1]][i - 1];
        mx[u][i] = max(mx[u][i - 1], mx[up[u][i - 1]][i - 1]);
    }
    for (auto &[v, w] : adj[u])
        if (v != p)
            dfs(v, u, w, d + 1);
}

int get(int u, int v)
{
    if (h[u] < h[v])
        swap(u, v);
    int res = 0, k = h[u] - h[v];
    for (int i = 18; i >= 0; i--)
        if (k >> i & 1)
        {
            res = max(res, mx[u][i]);
            u = up[u][i];
        }
    if (u == v)
        return res;
    for (int i = 18; i >= 0; i--)
        if (up[u][i] != up[v][i])
        {
            res = max(res, max(mx[u][i], mx[v][i]));
            u = up[u][i], v = up[v][i];
        }
    return max(res, max(mx[u][0], mx[v][0]));
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<edge> a(m);
    for (int i = 0; i < m; i++)
    {
        cin >> a[i].u >> a[i].v >> a[i].w;
        a[i].id = i;
    }
    vector<edge> se = a;
    sort(all(se), [](const edge &a, const edge &b)
         { return a.w < b.w; });
    DSU dsu(n);
    int t = 0;
    for (auto &i : se)
        if (!dsu.same(i.u, i.v))
        {
            dsu.uni(i.u, i.v);
            t += i.w;
            adj[i.u].pb(i.v, i.w);
            adj[i.v].pb(i.u, i.w);
        }
    dfs(1, 1, 0, 0);
    vector<int> res(m);
    for (int i = 0; i < m; i++)
        res[a[i].id] = t + a[i].w - get(a[i].u, a[i].v);
    for (int i : res)
        cout << i << '\n';
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
