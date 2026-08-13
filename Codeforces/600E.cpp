/*************************
  Author: Defy logic guy
  22:35:46 - 31/07/2026
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
#define NAME "600E"

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v), adj[v].pb(u);
    }
    vector<int> ans(n + 1), mx(n + 1), sum(n + 1);
    vector<unordered_map<int, int>> mp(n + 1);
    auto dfs = [&](auto &&self, int u, int p) -> void
    {
        mp[u][a[u]]++, mx[u] = 1, sum[u] = a[u];
        for (int v : adj[u])
        {
            if (v == p)
                continue;
            self(self, v, u);
            if (mp[u].size() < mp[v].size())
            {
                swap(mp[u], mp[v]);
                swap(mx[u], mx[v]);
                swap(sum[u], sum[v]);
            }
            for (auto [x, cnt] : mp[v])
            {
                int cur = mp[u][x] += cnt;
                if (cur > mx[u])
                    mx[u] = cur, sum[u] = x;
                else if (cur == mx[u])
                    sum[u] += x;
            }
        }
        ans[u] = sum[u];
    };
    dfs(dfs, 1, 0);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
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
