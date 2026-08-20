/*************************
  Author: Defy logic guy
  15:56:05 - 18/08/2026
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
#define NAME "TIMELINE"

void solve()
{
    int n, m, c;
    cin >> n >> m >> c;
    vector<int> ans(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> ans[i];
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<int> sz(n + 1, 0);
    for (int i = 0; i < c; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb(v, w);
        sz[v]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!sz[i])
            q.push(i);
    while (q.size())
    {
        int u = q.front();
        q.pop();
        for (auto [v, w] : adj[u])
        {
            ans[v] = max(ans[v], ans[u] + w);
            if (!--sz[v])
                q.push(v);
        }
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';
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
