/*************************
  Author: Defy logic guy
  21:35:10 - 24/10/2026
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
#define NAME "ABC287"

void solve()
{
    int n;
    cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; ++i)
        cin >> s[i];
    vector<int> res(n);
    auto dfs = [&](auto &&dfs, int pf, vector<int> idx) -> void
    {
        vector<vector<int>> idk(26);
        for (const int i : idx)
            if (pf < s[i].size())
                idk[s[i][pf] - 'a'].pb(i);
        for (const int i : idx)
            res[i] = pf;
        for (auto &&t : idk)
            if (t.size() >= 2)
                dfs(dfs, pf + 1, t);
    };
    vector<int> v(n);
    iota(all(v), 0ll);
    dfs(dfs, 0, v);
    for (int i : res)
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
