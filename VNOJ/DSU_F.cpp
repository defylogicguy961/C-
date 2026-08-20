/*************************
  Author: Defy logic guy
  20:59:04 - 18/08/2026
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
#define NAME "DSU_F"

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
        if (x < y)
            swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    vector<bool> vis(n + 1, false);
    for (int i = 0; i < m; i++)
    {
        char c;
        int x;
        cin >> c >> x;
        if (c == '-')
        {
            if (x > 1 and vis[x - 1])
                dsu.uni(x, x - 1);
            if (x < n and vis[x + 1])
                dsu.uni(x, x + 1);
            vis[x] = true;
        }
        else
        {
            if (!vis[x])
                cout << x << '\n';
            else
            {
                x = dsu.find(x);
                if (x == n)
                    cout << "-1\n";
                else
                    cout << x + 1 << '\n';
            }
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
