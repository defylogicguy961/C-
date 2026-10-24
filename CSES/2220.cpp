/*************************
  Author: Defy logic guy
  20:43:50 - 22/09/2026
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
#define NAME "2220"

int dp[20][2][11][2];
vector<int> d;

int cnt(int x)
{
    if (x < 0)
        return 0;
    d.clear();
    string s = to_string(x);
    for (char c : s)
        d.pb(c - '0');
    memset(dp, -1, sizeof(dp));
    auto get = [&](auto &&get, int pos, int t, int lst, int st) -> int
    {
        if (pos == d.size())
            return 1;
        int &ans = dp[pos][t][lst][st];
        if (ans != -1)
            return ans;
        ans = 0;
        int l = t ? d[pos] : 9;
        for (int d = 0; d <= l; d++)
        {
            int nxt = st || d != 0;
            if (nxt and st and d == lst)
                continue;
            ans += get(get, pos + 1, t and d == l, nxt ? d : 10, nxt);
        }
        return ans;
    };
    return get(get, 0, 1, 10, 0);
}

void solve()
{
    int a, b;
    cin >> a >> b;
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
