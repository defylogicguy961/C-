/*************************
  Author: Defy logic guy
  21:02:42 - 01/08/2026
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
#define NAME "1931F"

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n + 1), a(k, vector<int>(n));
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
        for (int j = 1; j < n - 1; j++)
            adj[a[i][j]].pb(a[i][j + 1]);
    }
    vector<int> tout(n + 1, 0);
    vector<bool> vis(n + 1, false);
    int cur = 1;
    auto dfs = [&](auto &&dfs, int u) -> void
    {
        vis[u] = true;
        for (int v : adj[u])
            if (!vis[v])
                dfs(dfs, v);
        tout[u] = cur++;
    };
    for (int i = 1; i <= n; i++)
        if (!tout[i])
            dfs(dfs, i);
    for (int i = 0; i < k; i++)
        for (int j = 1; j < n - 1; j++)
            if (tout[a[i][j]] < tout[a[i][j + 1]])
            {
                cout << "NO\n";
                return;
            }
    cout << "YES\n";
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
