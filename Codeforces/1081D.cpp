/*************************
  Author: Defy logic guy
  14:11:10 - 08/09/2026
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
#define NAME "1081D"

struct edge
{
    int u, v, w;
    edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {}
    bool operator<(const edge &o) const { return w < o.w; }
};

struct DSU
{
    DSU(int n = 0) { init(n); }
    vector<int> par, sz, v;
    void init(int n)
    {
        par.resize(n + 1);
        iota(all(par), 0);
        sz.assign(n + 1, 1);
        v.assign(n + 1, 0);
    }
    int find(int x) { return par[x] = (par[x] == x ? x : find(par[x])); }
    int size(int x) { return sz[find(x)]; }
    bool same(int x, int y) { return find(x) == find(y); }
    void uni(int x, int y, int &cur)
    {
        x = find(x), y = find(y);
        if (x == y)
            return;
        par[y] = x;
        sz[x] += sz[y];
        v[x] += v[y];
        cur = max(cur, v[x]);
    }
};

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<edge> a(m);
    int cur = 0;
    DSU dsu(n);
    for (int i = 0, x; i < k; i++)
    {
        cin >> x;
        dsu.v[x]++;
    }
    for (int i = 0; i < m; i++)
        cin >> a[i].u >> a[i].v >> a[i].w;
    sort(all(a));
    for (auto &e : a)
    {
        if (dsu.same(e.u, e.v))
            continue;
        dsu.uni(e.u, e.v, cur);
        if (cur == k)
        {
            for (int i = 0; i < k; i++)
                cout << e.w << ' ';
            return;
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
