/*************************
  Author: Defy logic guy
  19:55:35 - 05/09/2026
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
#define NAME "1468J"

struct edge
{
    int u, v, w;
    edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {};
    bool operator<(const edge &o) const { return w < o.w; }
};

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
        if (x > y)
            swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
    }
};

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<edge> a(m);
    int ans = LLONG_MAX;
    for (int i = 0; i < m; i++)
    {
        cin >> a[i].u >> a[i].v >> a[i].w;
        ans = min(ans, abs(a[i].w - k));
    }
    sort(all(a));
    DSU dsu(n);
    int t = 0, cur = n;
    for (int i = 0; i < m; i++)
        if (a[i].w <= k)
        {
            if (!dsu.same(a[i].u, a[i].v))
            {
                dsu.uni(a[i].u, a[i].v);
                cur--;
            }
        }
        else if (cur > 1 and !dsu.same(a[i].u, a[i].v))
        {
            dsu.uni(a[i].u, a[i].v);
            cur--;
            t += a[i].w - k;
        }
    cout << (!t ? ans : t) << '\n';
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
    cin >> tt;

    while (tt--)
        solve();

    return 0;
}
