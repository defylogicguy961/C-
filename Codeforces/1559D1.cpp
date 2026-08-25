/*************************
  Author: Defy logic guy
  21:11:26 - 22/08/2026
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
#define NAME "1559D1"

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
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        par[y] = x;
        sz[x] += sz[y];
    }
};

void solve()
{
    int n, m1, m2;
    cin >> n >> m1 >> m2;
    DSU dsu1(n), dsu2(n);
    for (int i = 0; i < m1; i++)
    {
        int u, v;
        cin >> u >> v;
        dsu1.uni(u, v);
    }
    for (int i = 0; i < m2; i++)
    {
        int u, v;
        cin >> u >> v;
        dsu2.uni(u, v);
    }
    vector<pair<int, int>> ans;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (!dsu1.same(i, j) and !dsu2.same(i, j))
            {
                dsu1.uni(i, j), dsu2.uni(i, j);
                ans.pb(i, j);
            }
    cout << ans.size() << '\n';
    for (auto [u, v] : ans)
        cout << u << ' ' << v << '\n';
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
