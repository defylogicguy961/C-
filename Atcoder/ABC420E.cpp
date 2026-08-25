/*************************
  Author: Defy logic guy
  21:31:00 - 22/08/2026
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
#define NAME "ABC420E"

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> par(n + 1, -1), cnt(n + 1, 0);
    vector<bool> vis(n + 1, false);
    auto dfs = [&](auto &&dfs, int x) -> int
    { return par[x] < 0 ? x : par[x] = dfs(dfs, par[x]); };
    while (q--)
    {
        int t, v;
        cin >> t >> v;
        if (t == 1)
        {
            int u;
            cin >> u;
            int rv = dfs(dfs, v), ru = dfs(dfs, u);
            if (rv != ru)
            {
                if (par[rv] > par[ru])
                    swap(rv, ru);
                par[rv] += par[ru], par[ru] = rv, cnt[rv] += cnt[ru];
            }
        }
        else if (t == 2)
        {
            int r = dfs(dfs, v);
            if (vis[v])
                vis[v] = false, cnt[r]--;
            else
                vis[v] = true, cnt[r]++;
        }
        else
            cout << (cnt[dfs(dfs, v)] ? "Yes\n" : "No\n");
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
