/*************************
  Author: Defy logic guy
  22:01:41 - 19/09/2026
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
#define NAME "QTSEG"

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    vector<int> l(n + 1, 0), r(n + 2, 0);
    for (int i = 1; i <= n; i++)
        l[i] = l[i - 1] + a[i];
    for (int i = n; i >= 1; i--)
        r[i] = r[i + 1] + a[i];
    int res = -1, cnt = 0,
        ln = LLONG_MIN, nn = LLONG_MAX,
        c1 = 0, c2 = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        if (l[i] < nn)
            nn = l[i], c1 = 1;
        else if (l[i] == nn)
            c1++;
        if (l[i] > ln)
            ln = l[i], c2 = 1;
        else if (l[i] == ln)
            c2++;
        int nw = ln - r[i + 1];
        if (nw > res)
            res = nw, cnt = c2;
        else if (nw == res)
            cnt += c2;
        nw = r[i + 1] - nn;
        if (nw > res)
            res = nw, cnt = c1;
        else if (nw == res)
            cnt += c1;
    }
    if (!res)
        cnt /= 2;
    cout << res << ' ' << cnt;
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
