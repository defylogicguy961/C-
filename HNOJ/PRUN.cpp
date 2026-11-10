/*************************
  Author: Defy logic guy
  20:16:46 - 30/10/2026
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
#define NAME "PRUN"

void solve()
{
    int n, k;
    cin >> n >> k;
    if (k == 0)
    {
        cout << 0;
        return;
    }
    vector<vector<int>> dp(n + 1, vector<int>(k, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < k; j++)
        {
            (dp[i][j] += dp[i - 1][j] * (j + 1)) %= MOD;
            if (j >= 1)
                (dp[i][j] += (i - j) * dp[i - 1][j - 1]) %= MOD;
        }
    cout << dp[n][k - 1];
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
