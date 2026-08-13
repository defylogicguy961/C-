/*************************
  Author: Defy logic guy
  19:44:33 - 08/08/2026
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
#define NAME "5C"

void solve()
{
    string s;
    cin >> s;
    int n = s.size();
    vector<int> pf(n + 1, 0);
    for (int i = 1; i <= n; i++)
        pf[i] = pf[i - 1] + (s[i - 1] == '(' ? 1 : -1);
    int mx = 64 - __builtin_clzll(n + 1);
    vector<vector<int>> st(mx, vector<int>(n + 1));
    for (int i = 0; i <= n; i++)
        st[0][i] = pf[i];
    for (int k = 1; k < mx; k++)
        for (int i = 0; i + (1ll << k) <= n + 1; i++)
            st[k][i] = min(st[k - 1][i], st[k - 1][i + (1ll << (k - 1))]);
    auto get = [&](int l, int r)
    {
        int k = 63 - __builtin_clzll(r - l + 1);
        return min(st[k][l], st[k][r - (1ll << k) + 1]);
    };
    map<int, vector<int>> mp;
    for (int i = 0; i <= n; i++)
        mp[pf[i]].pb(i);
    int ans = 0, cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        int b = pf[i - 1];
        auto &v = mp[b];
        int lo = lower_bound(all(v), i) - v.begin();
        int l = lo, r = v.size() - 1, res = lo - 1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (get(i, v[mid]) >= b)
                res = mid, l = mid + 1;
            else
                r = mid - 1;
        }
        if (res >= lo)
        {
            int len = v[res] - i + 1;
            if (len > ans)
                ans = len, cnt = 1;
            else if (len == ans)
                cnt++;
        }
    }
    if (ans == 0)
        cout << "0 1";
    else
        cout << ans << ' ' << cnt;
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
