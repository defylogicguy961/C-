/*************************
  Author: Defy logic guy
  21:15:38 - 17/10/2026
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
#define NAME "DP_U"

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    int M = 1 << n;
    vector<int> c(M, 0);
    for (int i = 1; i < M; i++)
    {
        int r = i ^ (1ll << (__builtin_ctzll(i)));
        c[i] = c[r];
        for (int j = 0; j < n; j++)
            if (r & (1 << j))
                c[i] += a[__builtin_ctzll(i)][j];
    }
    vector<int> dp(M, LLONG_MIN);
    dp[0] = 0;
    for (int i = 1; i < M; i++)
        for (int j = i; j; j = (j - 1) & i)
            dp[i] = max(dp[i], dp[i ^ j] + c[j]);
    cout << dp[M - 1] << '\n';
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
