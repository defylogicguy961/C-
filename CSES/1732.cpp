/*************************
  Author: Defy logic guy
  20:27:26 - 03/11/2026
*************************/
#include <bits/stdc++.h>
using namespace std;
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
#define NAME "1732"

const int mod1 = 1000000007, mod2 = 1000000009,
          base = 311;
void solve()
{
    string s;
    cin >> s;
    vector<int> h1(s.size() + 1), h2(s.size() + 1),
        p1(s.size() + 1, 1), p2(s.size() + 1, 1);
    for (int i = 0; i < (int)s.size(); i++)
    {
        h1[i + 1] = (h1[i] * base + s[i]) % mod1;
        h2[i + 1] = (h2[i] * base + s[i]) % mod2;
        p1[i + 1] = p1[i] * base % mod1;
        p2[i + 1] = p2[i] * base % mod2;
    }
    for (int len = 1; len < (int)s.size(); len++)
    {
        int one = (h1[s.size()] - h1[s.size() - len] * p1[len] % mod1 + mod1) % mod1;
        int two = (h2[s.size()] - h2[s.size() - len] * p2[len] % mod2 + mod2) % mod2;
        if (h1[len] == one and h2[len] == two)
            cout << len << ' ';
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
