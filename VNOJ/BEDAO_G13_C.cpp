/*************************
  Author: Defy logic guy
  19:36:22 - 18/08/2026
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
#define dbg(x) cey << #x << " = " << (x) << '\n';
#define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define maxall(x) *max_element(all(x))
#define minall(x) *min_element(all(x))
#define heap priority_queue
#define pb emplace_back
#define MOD 1000000007
#define NAME "BEDAO_G13_C"

struct DSU
{
    DSU(int n = 0) { init(n); }
    vector<int> par, sum, pre, suf, sub;
    int mx = LLONG_MIN;
    void init(int n)
    {
        par.resize(n + 2);
        iota(all(par), 0);
        sum.assign(n + 2, 0);
        pre.assign(n + 2, LLONG_MIN);
        suf.assign(n + 2, LLONG_MIN);
        sub.assign(n + 2, LLONG_MIN);
    }
    int find(int x) { return par[x] = (par[x] == x ? x : find(par[x])); }
    bool same(int x, int y) { return find(x) == find(y); }
    void uni(int x, int y)
    {
        x = find(x), y = find(y);
        if (x == y)
            return;
        if (x > y)
            swap(x, y);
        sub[x] = max({sub[x], sub[y], suf[x] + pre[y]});
        pre[x] = max(pre[x], sum[x] + pre[y]);
        suf[x] = max(suf[y], sum[y] + suf[x]);
        sum[x] += sum[y];
        par[y] = x;
        mx = max(mx, sub[x]);
    }
};

void solve()
{
    int n;
    cin >> n;
    DSU dsu(n);
    vector<int> b(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    vector<int> ans, vis(n + 2, false);
    for (int i = n; i >= 1; i--)
    {
        vis[a[i]] = true;
        dsu.sum[a[i]] = dsu.pre[a[i]] = dsu.suf[a[i]] = dsu.sub[a[i]] = b[a[i]];
        dsu.mx = max(dsu.mx, dsu.sub[a[i]]);
        if (vis[a[i] - 1])
            dsu.uni(a[i], a[i] - 1);
        if (vis[a[i] + 1])
            dsu.uni(a[i], a[i] + 1);
        ans.pb(dsu.mx);
    }
    reverse(all(ans));
    for (int i = 0; i < n; i++)
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
