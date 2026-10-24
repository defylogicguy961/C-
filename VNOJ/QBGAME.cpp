/*************************
  Author: Defy logic guy
  20:06:13 - 17/10/2026
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
#define NAME "QBGAME"

void solve()
{
    int n;
    cin >> n;
    int xx = LLONG_MIN;
    vector<vector<int>> a(9, vector<int>(n + 1));
    for (int i = 1; i <= 8; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> a[i][j];
            xx = max(xx, a[i][j]);
        }
    if (xx <= 0)
    {
        cout << xx;
        return;
    }
    vector<int> v;
    for (int i = 0; i < (1 << 8); i++)
        if ((i & (i << 1)) == 0)
            v.pb(i);
    vector<int> dp(v.size(), LLONG_MIN), ndp(v.size(), LLONG_MIN);
    for (int i = 0; i < v.size(); i++)
    {
        int sum = 0;
        for (int j = 0; j < 8; j++)
            if (v[i] >> j & 1)
                sum += a[j + 1][1];
        dp[i] = sum;
    }
    for (int i = 2; i <= n; i++)
    {
        fill(all(ndp), LLONG_MIN);
        for (int j = 0; j < v.size(); j++)
        {
            int sum = 0;
            for (int k = 0; k < 8; k++)
                if (v[j] >> k & 1)
                    sum += a[k + 1][i];
            for (int k = 0; k < (int)v.size(); k++)
                if ((v[j] & v[k]) == 0 and dp[k] != LLONG_MIN)
                    ndp[j] = max(ndp[j], dp[k] + sum);
        }
        dp.swap(ndp);
    }
    cout << maxall(dp);
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
