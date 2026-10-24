/*************************
  Author: Defy logic guy
  23:26:12 - 05/06/2026
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
#define float double
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define maxall(x) *max_element(all(x))
#define minall(x) *min_element(all(x))
#define heap priority_queue
#define pb push_back
#define MOD 1000000007
#define NAME "COWGIRL"

void solve()
{
    int n, m;
    cin >> n >> m;
    if (n < m)
        swap(n, m);
    int M = (1 << m);
    vector<vector<int>> dp(n, vector<int>(M, 0));
    for (int i = 0; i < M; i++)
        dp[0][i] = 1;
    auto f = [&](int a, int b) -> bool
    {
        for (int i = 0; i < m - 1; i++)
        {
            int A = (1ll & (a >> i));
            int B = (1ll & (a >> (i + 1)));
            int C = (1ll & (b >> i));
            int D = (1ll & (b >> (i + 1)));
            if (A * B * C * D == 1 or (A + B + C + D) == 0)
                return false;
        }
        return true;
    };
    for (int i = 1; i < n; i++)
        for (int j = 0; j < M; j++)
            for (int k = 0; k < M; k++)
                if (f(j, k))
                    dp[i][k] += dp[i - 1][j];
    cout << accumulate(all(dp[n - 1]), 0ll) << '\n';
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
