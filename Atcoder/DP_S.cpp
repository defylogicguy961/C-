/*************************
  Author: Defy logic guy
  20:38:55 - 22/09/2026
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
#define NAME "DP_S"

void solve()
{
    string s;
    int d;
    cin >> s >> d;
    int n = s.size();
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(d, vector<int>(2, 0)));
    dp[0][0][0] = 1;
    for (int i = 0; i < n; i++)
        for (int sum = 0; sum < d; sum++)
            for (int small = 0; small < 2; small++)
            {
                int lim = small ? 9 : (s[i] - '0');
                for (int x = 0; x <= lim; x++)
                    dp[i + 1][(sum + x) % d][(small | (x < lim))] = (dp[i + 1][(sum + x) % d][(small | (x < lim))] + dp[i][sum][small]) % MOD;
            }
    cout << (dp[s.size()][0][0] + dp[s.size()][0][1] - 1 + MOD) % MOD << endl;
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
