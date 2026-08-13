/*************************
  Author: Defy logic guy
  15:43:02 - 10/08/2026
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
#define NAME "1140"

struct node
{
    int a, b, p;
    node(int a = 0, int b = 0, int p = 0) : a(a), b(b), p(p) {}
};

void solve()
{
    int n;
    cin >> n;
    vector<node> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i].a >> a[i].b >> a[i].p;
    sort(all(a), [](const node &x, const node &y)
         { return x.b < y.b; });
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        v[i] = a[i].b;
    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        int j = lower_bound(v.begin(), v.begin() + (i - 1), a[i - 1].a) - v.begin();
        dp[i] = max(dp[i - 1], dp[j] + a[i - 1].p);
    }
    cout << dp[n] << '\n';
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
