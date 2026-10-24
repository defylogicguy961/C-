/*************************
  Author: Defy logic guy
  21:03:13 - 22/09/2026
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
#define NAME "MDIGITS"

int dp[27][2][2][10];
vector<int> cnt(int n)
{
    vector<int> ans(10, 0);
    if (n <= 0)
        return ans;
    for (int f = 1; f <= n; f *= 10)
    {
        int lo = n % f, cur = (n / f) % 10, hi = n / (f * 10);
        for (int i = 1; i <= 9; i++)
        {
            ans[i] += hi * f;
            if (cur > i)
                ans[i] += f;
            else if (cur == i)
                ans[i] += lo + 1;
        }
        if (hi > 0)
            ans[0] += (hi - 1) * f + (cur == 0 ? lo + 1 : f);
        if (f > n / 10)
            break;
    }
    return ans;
}

void solve()
{
    int a, b;
    while (cin >> a >> b and (a != 0 || b != 0))
    {
        if (a > b)
            swap(a, b);
        vector<int> hi = cnt(b), lo = cnt(a - 1);
        for (int i = 0; i < 10; i++)
            cout << hi[i] - lo[i] << " \n"[i == 9];
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
