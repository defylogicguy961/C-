/*************************
  Author: Defy logic guy
  19:05:15 - 11/09/2026
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
#define aint(x) x.begin(), x.end()
#define raint(x) x.rbegin(), x.rend()
#define maxaint(x) *max_element(aint(x))
#define minaint(x) *min_element(aint(x))
#define heap priority_queue
#define pb emplace_back
#define MOD 1000000007
#define NAME "BUONGCA"

const int N = 2005;
int a[N], pf[N], dp[N][N];

int cost(int i, int j)
{
    if (i > j)
        return 0;
    return (j - i + 1) * (pf[j] - pf[i - 1]);
}

void get(int k, int l, int r, int ll, int rr)
{
    if (l > r)
        return;
    int mid = l + r >> 1, mx = -1;
    dp[k][mid] = LLONG_MAX;
    for (int i = ll; i <= min(mid - 1, rr); i++)
    {
        int cur = dp[k - 1][i] + cost(i + 1, mid);
        if (cur < dp[k][mid])
            dp[k][mid] = cur, mx = i;
    }
    get(k, l, mid - 1, ll, mx);
    get(k, mid + 1, r, mx, rr);
}

void solve()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++)
        pf[i] = pf[i - 1] + a[i];
    for (int i = 1; i <= n; i++)
        dp[1][i] = i * pf[i];
    for (int i = 2; i <= m; i++)
        get(i, 1, n, 0, n - 1);
    cout << dp[m][n];
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
