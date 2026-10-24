/*************************
  Author: Defy logic guy
  19:57:05 - 22/09/2026
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
auto operator<<(ostream &os, const T &c) -> typename enable_if<!is_same<T, string>::x, decltype(c.begin(), c.end(), os)>::type
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
#define NAME "BINARY"

int dp[31][32][2][2];
void solve()
{
    int n, k;
    while (cin >> n >> k)
    {
        vector<int> v;
        for (int i = 30; i >= 0; i--)
            v.pb((n >> i) & 1);
        memset(dp, -1, sizeof(dp));
        auto dfs = [&](auto &&dfs, int idx, int cnt, int t, int t1) -> int
        {
            if (cnt > k)
                return 0;
            if (idx == 31)
                return t1 ? (cnt == k) : (k == 1);
            int &ans = dp[idx][cnt][t][t1];
            if (ans != -1)
                return ans;
            ans = 0;
            int l = t ? v[idx] : 1;
            for (int x = 0; x <= l; x++)
            {
                int nxtt1 = t1 or x;
                int nxtcnt = cnt + (nxtt1 and x == 0);
                ans += dfs(dfs, idx + 1, nxtcnt, t and x == v[idx], nxtt1);
            }
            return ans;
        };

        cout << dfs(dfs, 0, 0, 1, 0) << '\n';
    }
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
