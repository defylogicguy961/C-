/*************************
  Author: Defy logic guy
  19:51:51 - 03/10/2026
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
#define NAME "SNAD"

int dfs(int l, int r)
{
    string s = to_string(l);
    int dp[20][172][2] = {};
    dp[0][0][1] = 1;
    for (int i = 0; i < s.size(); i++)
        for (int sum = 0; sum <= r; sum++)
            for (int t = 0; t <= 1; t++)
                if (dp[i][sum][t])
                {
                    int lim = t ? s[i] - '0' : 9;
                    for (int d = 0; d <= lim && sum + d <= r; ++d)
                        dp[i + 1][sum + d][t && d == lim] += dp[i][sum][t];
                }

    return dp[s.size()][r][0] + dp[s.size()][r][1];
}

void solve()
{
    int l, r;
    cin >> l >> r;
    int ans = 0;
    for (int sum = 1; sum <= 171; sum++)
    {
        int lo = l / sum + (l % sum != 0), hi = r / sum;
        if (lo > hi)
            continue;
        ans += dfs(hi, sum) - (!lo ? 0 : dfs(lo - 1, sum));
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
    cin >> tt;

    while (tt--)
        solve();

    return 0;
}
