/*************************
  Author: Defy logic guy
  20:04:47 - 11/08/2026
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
#define NAME "BEDAO_R14_BRACKET"

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1, 0);
    map<int, set<int>> mp;
    mp[0].insert(0);
    for (int i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        a[i + 1] = a[i] + (c == '(' ? 1 : -1);
        mp[a[i + 1]].insert(i + 1);
    }
    vector<int> lg(n + 1, 0);
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i >> 1] + 1;
    vector<vector<int>> st(n + 1, vector<int>(lg[n] + 1));
    for (int i = 0; i <= n; i++)
        st[i][0] = a[i];
    for (int j = 1; j <= lg[n]; j++)
        for (int i = 0; i + (1 << (j - 1)) <= n; i++)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    auto get = [&](const int &l, const int &r) -> int
    {
        int k = lg[r - l + 1];
        return min(st[l][k], st[r - (1 << k) + 1][k]);
    };
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        int t = get(l - 1, r);
        auto ll = mp[t].upper_bound(l - 1);
        if (ll == mp[t].begin())
        {
            cout << "-1\n";
            continue;
        }
        auto rr = mp[t].lower_bound(r);
        if (rr == mp[t].end())
        {
            cout << "-1\n";
            continue;
        }
        cout << *prev(ll) + 1 << ' ' << *rr << '\n';
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
