/*************************
  Author: Defy logic guy
  19:53:16 - 16/10/2026
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
#define NAME "CEN_COMMANDER"

const int maxn = 1e5 + 5;
int n;
vector<int> adj[maxn];
int par[maxn], sz[maxn];
char ans[maxn];
bool rm[maxn];

int find(int idx)
{
    vector<int> o;
    o.pb(idx);
    par[idx] = 0;
    for (int i = 0; i < o.size(); i++)
    {
        int u = o[i];
        for (int v : adj[u])
        {
            if (rm[v] or v == par[u])
                continue;
            par[v] = u;
            o.pb(v);
        }
    }
    for (int i = o.size() - 1; i >= 0; i--)
    {
        int u = o[i];
        sz[u] = 1;
        for (int v : adj[u])
        {
            if (rm[v] or par[v] != u)
                continue;
            sz[u] += sz[v];
        }
    }
    for (int u : o)
    {
        int mx = o.size() - sz[u];
        for (int v : adj[u])
        {
            if (rm[v] or par[v] != u)
                continue;
            mx = max(mx, sz[v]);
        }
        if (mx * 2 <= o.size())
            return u;
    }
    return idx;
}

void f(int idx, int len)
{
    int c = find(idx);
    ans[c] = char('A' + len);
    rm[c] = true;
    for (int v : adj[c])
        if (!rm[v])
            f(v, len + 1);
}

void solve()
{
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v), adj[v].pb(u);
    }
    f(1, 0);
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
