/*************************
  Author: Defy logic guy
  19:47:13 - 12/09/2026
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
#define NAME "FCC2021_CLIMBING"

void solve()
{
    int n, m, c;
    cin >> n >> m >> c;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vector<int> ans;
    deque<int> mx, mn;
    for (int i = 0; i < n; i++)
    {
        if (mx.size() && mx.front() <= i - m)
            mx.pop_front();
        if (mn.size() && mn.front() <= i - m)
            mn.pop_front();

        while (mx.size() && a[mx.back()] <= a[i])
            mx.pop_back();
        while (mn.size() && a[mn.back()] >= a[i])
            mn.pop_back();

        mx.pb(i);
        mn.pb(i);

        if (i >= m - 1)
        {
            int mxx = a[mx.front()];
            int mnn = a[mn.front()];
            if (mxx - mnn <= c)
                ans.pb(i - m + 2);
        }
    }
    if (ans.empty())
        cout << "NONE";
    else
        for (int i : ans)
            cout << i << '\n';
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
