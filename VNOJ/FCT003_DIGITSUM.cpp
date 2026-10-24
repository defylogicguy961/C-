/*************************
  Author: Defy logic guy
  20:36:13 - 22/09/2026
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
#define NAME "FCT003_DIGITSUM"

int sum(int n)
{
    string s = to_string(n);
    int dp[s.size() + 1][2][s.size() * 9 + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][1][0] = 1; // dp[pos][is_tight][sum]
    for (int i = 0; i < s.size(); i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k <= s.size() * 9; k++)
            {
                int l = j ? s[i] - '0' : 9;
                for (int d = 0; d <= l; d++)
                    dp[i + 1][j && (d == l)][k + d] += dp[i][j][k];
            }
    int ans = 0;
    for (int i = 0; i <= s.size() * 9; i++)
        ans += (dp[s.size()][0][i] + dp[s.size()][1][i]) * i;
    return ans;
}

void solve()
{
    int a, b;
    cin >> a >> b;
    cout << sum(b) - sum(a - 1);
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
