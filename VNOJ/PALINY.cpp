/*************************
  Author: Defy logic guy
  13:42:55 - 29/10/2026
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
#define NAME "PALINY"

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans = 0, c = -1;
    vector<int> odd(n + 1, 0), even(n + 1, 0);
    for (int i = 0, l = 0, r = -1; i < n; i++)
    {
        int len = (i > r) ? 1 : min(odd[l + r - i], r - i + 1);
        while (0 <= i - len and i + len < n and s[i - len] == s[i + len])
            len++;
        odd[i] = len--;
        if (i + len > r)
            l = i - len, r = i + len;
        if (odd[i] * 2 - 1 > ans)
            ans = odd[i] * 2 - 1;
    }
    for (int i = 0, l = 0, r = -1; i < n; i++)
    {
        int len = (i > r) ? 0 : min(even[l + r - i + 1], r - i + 1);
        while (0 <= i - len - 1 and i + len < n and s[i - len - 1] == s[i + len])
            len++;
        even[i] = len--;
        if (i + len > r)
            l = i - len - 1, r = i + len;
        if (even[i] * 2 > ans)
            ans = even[i] * 2;
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
