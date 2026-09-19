/*************************
  Author: Defy logic guy
  20:54:33 - 19/09/2026
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
#define NAME "DP_M"

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    vector<vector<int>> dp(n + 1, vector<int>(k + 1)),
        sum(n + 1, vector<int>(k + 1));
    dp[0][0] = 1;
    for (int i = 1; i <= k; i++)
        dp[0][i] = 0;
    for (int i = 1; i <= n; i++)
    {
        sum[i - 1][0] = dp[i - 1][0];
        for (int j = 1; j <= k; j++)
            sum[i - 1][j] = (sum[i - 1][j - 1] + dp[i - 1][j]) % MOD;
        for (int j = 0; j <= k; j++)
        {
            int r = (j - a[i] - 1);
            dp[i][j] = sum[i - 1][j];
            if (r >= 0)
                dp[i][j] = (dp[i][j] - sum[i - 1][r] + MOD) % MOD;
        }
    }
    cout << dp[n][k];
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
