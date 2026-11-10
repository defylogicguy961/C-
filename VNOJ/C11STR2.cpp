/*************************
  Author: Defy logic guy
  19:36:39 - 07/11/2026
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
#define NAME "C11STR2"

const int base = 311;
void solve()
{
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    int one = 0, two = 0, cur = 1, k = 0;
    for (int i = n - 1, j = 0; i >= 0 && j < m; i--, j++)
    {
        one = (one + (s[i] - 'a') * cur % MOD) % MOD;
        two = (two * base + (t[j] - 'a')) % MOD;
        if (one == two)
            k = j + 1;
        (cur *= base) %= MOD;
    }
    cout << s << t.substr(k);
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
