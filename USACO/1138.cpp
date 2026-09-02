/*************************
  Author: Defy logic guy
  20:41:57 - 29/08/2026
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
#define NAME "1138"

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
    int u, v, w;
    edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {};
    bool operator<(const edge &o) const { return w < o.w; }
};

void solve()
{
    int n;
    cin >> n;
    DSU dsu(2 * n);
    vector<edge> e;
    for (int i = 0; i < n; i++)
    {
        int c, p1, p2, p3, p4;
        cin >> c >> p1 >> p2 >> p3 >> p4;
        dsu.uni(p1, p2), dsu.uni(p3, p4);
        e.pb(p1, p3, c);
    }
    sort(all(e));
    int ans = 0;
    for (auto &i : e)
        if (!dsu.same(i.u, i.v))
        {
            dsu.uni(i.u, i.v);
            ans += i.w;
        }
    cout << ans;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tt = 1;
    // cin >> tt;

    while (tt--)
        solve();

    return 0;
}
