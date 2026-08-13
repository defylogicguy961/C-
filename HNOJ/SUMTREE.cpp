/*************************
  Author: Defy logic guy
  20:17:25 - 31/07/2026
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
#define NAME "SUMTREE"

const int MAXN = 2e5 + 5;
vector<pair<int, int>> adj[MAXN];
int sz[MAXN], ans[MAXN], n;

void dfs1(int u, int p)
{
    sz[u] = 1, ans[u] = 0;
    for (auto &[v, w] : adj[u])
    {
        if (v == p)
            continue;
        dfs1(v, u);
        sz[u] += sz[v];
        ans[1] += sz[v] * w;
    }
}

void dfs2(int u, int p)
{
    for (auto &[v, w] : adj[u])
    {
        if (v == p)
            continue;
        ans[v] = ans[u] + (n - 2 * sz[v]) * w;
        dfs2(v, u);
    }
}

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        adj[i].clear();
    for (int i = 0; i < n - 1; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({v, w}), adj[v].pb({u, w});
    }
    ans[1] = 0;
    dfs1(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << "\n";
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
