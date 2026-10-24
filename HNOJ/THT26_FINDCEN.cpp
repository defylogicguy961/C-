/*************************
  Author: Defy logic guy
  18:42:34 - 16/10/2026
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
#define NAME "THT26_FINDCEN"

int n;
vector<vector<int>> adj;
vector<int> sz;
void getsz(int u, int p)
{
    sz[u] = 1;
    for (int v : adj[u])
        if (v != p)
        {
            getsz(v, u);
            sz[u] += sz[v];
        }
}

int get(int u, int p)
{
    for (int v : adj[u])
    {
        if (v == p)
            continue;
        if (sz[v] * 2 > n)
            return get(v, u);
    }
    return u;
}

void solve()
{
    cin >> n;
    adj.resize(n + 1), sz.resize(n + 1);
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].pb(b), adj[b].pb(a);
    }
    getsz(1, 0);
    cout << get(1, 0);
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
