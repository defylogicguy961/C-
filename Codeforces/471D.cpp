/*************************
  Author: Defy logic guy
  21:04:18 - 03/11/2026
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
#define NAME "471D"

void solve()
{
    int n, m;
    cin >> n >> m;
    int lst = 0;
    cin >> lst;
    vector<int> a(n - 1), b(m - 1);
    for (int i = 1, x; i < n; i++)
    {
        cin >> x;
        a[i - 1] = lst - x;
        lst = x;
    }
    cin >> lst;
    for (int i = 1, x; i < m; i++)
    {
        cin >> x;
        b[i - 1] = lst - x;
        lst = x;
    }
    if (m == 1)
    {
        cout << n;
        return;
    }
    vector<int> pi(m - 1);
    for (int i = 1; i < m - 1; i++)
    {
        int j = pi[i - 1];
        while (j > 0 and b[i] != b[j])
            j = pi[j - 1];
        if (b[i] == b[j])
            j++;
        pi[i] = j;
    }
    int ans = 0, cur = 0;
    for (int x : a)
    {
        while (cur > 0 and x != b[cur])
            cur = pi[cur - 1];
        if (x == b[cur])
            cur++;
        if (cur == m - 1)
            ans++, cur = pi[cur - 1];
    }
    cout << ans;
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
