/*************************
  Author: Defy logic guy
  19:00:27 - 16/10/2026
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
#define NAME "CEN_BASIC"

const int maxn = 5e5 + 5;
int n, q;
vector<int> adj[maxn];
int sz[maxn], prv[maxn], heavy[maxn], cen[maxn];

bool check(int v, int c) { return ((sz[v] - sz[c]) * 2 <= sz[v] and heavy[c] * 2 <= sz[v]); }

void dfs_calc(int v, int p)
{
    heavy[v] = 0, sz[v] = 1, prv[v] = p;
    for (int u : adj[v])
    {
        dfs_calc(u, v);
        sz[v] += sz[u];
        heavy[v] = max(heavy[v], sz[u]);
    }
}

void dfscen(int v)
{
    if (sz[v] == 1)
        cen[v] = v;
    else
    {
        int t = 0;
        for (int i = 0; i < adj[v].size(); i++)
        {
            dfscen(adj[v][i]);
            if (sz[adj[v][t]] < sz[adj[v][i]])
                t = i;
        }
        int c = cen[adj[v][t]];
        while (!check(v, c))
            c = prv[c];
        cen[v] = c;
    }
}

void solve()
{
    cin >> n >> q;
    for (int i = 1; i < n; i++)
    {
        int v;
        cin >> v;
        adj[v - 1].pb(i);
    }
    dfs_calc(0, 0);
    dfscen(0);
    while (q--)
    {
        int v;
        cin >> v;
        cout << cen[v - 1] + 1 << '\n';
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
