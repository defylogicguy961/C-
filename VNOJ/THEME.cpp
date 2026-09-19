/*************************
  Author: Defy logic guy
  20:47:27 - 19/09/2026
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
#define NAME "THEME"

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n), d(n - 1);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i + 1 < n; i++)
        d[i] = a[i + 1] - a[i];
    int m = n - 1, ans = 0;
    vector<int> dp(m + 1);
    for (int i = m - 1; i >= 0; i--)
    {
        vector<int> ndp(m + 1);
        for (int j = m - 1; j > i; j--)
            if (d[i] == d[j])
            {
                ndp[j] = dp[j + 1] + 1;
                int len = min(ndp[j] + 1, j - i);
                if (len >= 5)
                    ans = max(ans, len);
            }
        dp.swap(ndp);
    }
    cout << ans << '\n';
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
