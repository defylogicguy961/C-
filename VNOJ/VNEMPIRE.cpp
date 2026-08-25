/*************************
  Author: Defy logic guy
  21:11:50 - 25/08/2026
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
#define NAME "VNEMPIRE"

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
    bool uni(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;
        if (sz[x] < sz[y])
            swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
        return true;
    }
};

struct tri
{
    int x, y, z;
    tri(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
    bool operator<(const tri &o) const { return tie(x, y, z) < tie(o.x, o.y, o.z); }
};

void solve()
{
    int n;
    cin >> n;
    vector<tri> pts(n);
    vector<pair<int, int>> xs(n), ys(n), zs(n);
    for (int i = 0; i < n; i++)
    {
        cin >> pts[i].x >> pts[i].y >> pts[i].z;
        xs[i] = {pts[i].x, i},
        ys[i] = {pts[i].y, i},
        zs[i] = {pts[i].z, i};
    }
    auto cost = [&](int u, int v) -> int
    {
        int dx = abs(pts[u].x - pts[v].x),
            dy = abs(pts[u].y - pts[v].y),
            dz = abs(pts[u].z - pts[v].z);
        return min({dx, dy, dz});
    };
    vector<tri> e;
    auto f = [&](int u, int v)
    {
        if (u == v)
            return;
        if (u > v)
            swap(u, v);
        e.pb(cost(u, v), u, v);
    };
    sort(all(xs)), sort(all(ys)), sort(all(zs));
    for (int i = 0; i + 1 < n; ++i)
    {
        f(xs[i].second, xs[i + 1].second);
        f(ys[i].second, ys[i + 1].second);
        f(zs[i].second, zs[i + 1].second);
    }
    if (n == 1)
    {
        cout << 0 << '\n';
        return;
    }
    sort(all(e));
    DSU dsu(n);
    int ans = 0, cnt = 0;
    for (auto &i : e)
    {
        if (cnt == n - 1)
            break;
        if (dsu.uni(i.y, i.z))
            ans += i.x, cnt++;
    }
    cout << ans;
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
