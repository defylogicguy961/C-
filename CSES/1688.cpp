/*************************
  Author: Defy logic guy
  20:22:46 - 01/08/2026
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
#define NAME "1688"

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<vector<int>> up(n + 1, vector<int>(19, -1));
    vector<int> d(n + 1, 0);
    for (int i = 2; i <= n; i++)
    {
        int x;
        cin >> x;
        up[i][0] = x, d[i] = d[x] + 1;
    }
    for (int j = 1; j < 19; j++)
        for (int i = 1; i <= n; i++)
            if (up[i][j - 1] != -1)
                up[i][j] = up[up[i][j - 1]][j - 1];
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        if (d[u] < d[v])
            swap(u, v);

        int k = d[u] - d[v];
        for (int i = 0; i < 19; i++)
            if ((k >> i) & 1)
                u = up[u][i];
        if (u == v)
        {
            cout << u << '\n';
            continue;
        }
        for (int i = 18; i >= 0; i--)
            if (up[u][i] != up[v][i])
                u = up[u][i], v = up[v][i];
        cout << up[u][0] << '\n';
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
