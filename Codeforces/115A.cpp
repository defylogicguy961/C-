/*************************
  Author: Defy logic guy
  19:35:42 - 01/08/2026
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
#define NAME "115A"

void solve()
{
    int n;
    cin >> n;
    vector<int> par(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> par[i];
    vector<int> d(n + 1, 0);
    int mx = 0;
    for (int i = 1; i <= n; i++)
    {
        if (d[i])
        {
            mx = max(mx, d[i]);
            continue;
        }
        int u = i;
        vector<int> v;
        while (u != -1 and d[u] == 0)
        {
            v.pb(u);
            u = par[u];
        }
        int cur = (u == -1 ? 0 : d[u]);
        for (int j = v.size() - 1; j >= 0; j--)
            cur += 1, d[v[j]] = cur;
        mx = max(mx, cur);
    }
    cout << mx;
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
