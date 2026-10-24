/*************************
  Author: Defy logic guy
  21:55:57 - 22/09/2026
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
#define NAME "DEMSO"

void solve()
{
    int a, b, d, k;
    cin >> a >> b >> d >> k;
    auto cnt = [&](int x) -> int
    {
        if (x <= 0)
            return 0;
        string s = to_string(x);
        int mx = min(k, (int)s.size());
        int dp[20][2][10][20];
        memset(dp, -1, sizeof(dp));
        auto dfs = [&](auto &&dfs, int pos, bool st, int prv, int bad, bool t) -> int
        {
            if (bad > mx)
                return 0;
            if (pos == s.size())
                return st;
            if (!t and dp[pos][st][prv][bad] != -1)
                return dp[pos][st][prv][bad];
            int l = t ? s[pos] - '0' : 9, ans = 0;
            for (int i = 0; i <= l; i++)
            {
                bool nxtst = st || i != 0;
                int nxtbad = bad;
                if (st and abs(prv - i) <= d)
                    nxtbad++;
                ans += dfs(dfs, pos + 1, nxtst, i, nxtbad, (t and i == l));
            }
            if (!t)
                dp[pos][st][prv][bad] = ans;
            return ans;
        };

        return dfs(dfs, 0, false, 0, 0, true);
    };
    cout << cnt(b) - cnt(a - 1) << '\n';
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
