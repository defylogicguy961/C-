/*************************
  Author: Defy logic guy
  21:24:06 - 06/08/2026
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
#define pb push_back
#define MOD 1000000007
#define NAME "2252B"

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int zer = 0, one = 0;
    for (char c : s)
        if (c == '0')
            zer++;
        else
            one++;
    int d = zer - one;
    if (abs(d) > 2)
    {
        cout << -1 << '\n';
        return;
    }
    int cnt = 1;
    for (int i = 1; i < n; ++i)
        if (s[i] != s[i - 1])
            cnt++;
    int t = 0;
    if (s.front() == '0' and s.back() == '0')
        t = 1;
    else if (s.front() == '1' and s.back() == '1')
        t = -1;
    int mx = -1;
    for (int i = -1; i <= 1; ++i)
        if (abs(d - i) <= 1)
            mx = max(mx, cnt - abs(t - i));
    cout << (mx == -1 ? -1 : n - mx) << '\n';
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
    cin >> tt;

    while (tt--)
        solve();

    return 0;
}
