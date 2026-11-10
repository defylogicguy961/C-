/*************************
  Author: Defy logic guy
  19:42:45 - 03/11/2026
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
#define NAME "271D"

const int mod1 = 1000000007;
const int mod2 = 1000000009;
const int base = 311;

struct Hash
{
    size_t operator()(const pair<int, int> &p) const
    {
        size_t h1 = hash<int>{}(p.first);
        size_t h2 = hash<int>{}(p.second);
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};

void solve()
{
    string s, check;
    int k;
    cin >> s >> check >> k;
    int n = s.size();
    vector<int> h1(n + 1), h2(n + 1), p1(n + 1, 1), p2(n + 1, 1);
    for (int i = 1; i <= n; i++)
    {
        int x = s[i - 1] - 'a' + 1;
        h1[i] = (h1[i - 1] * base + x) % mod1;
        h2[i] = (h2[i - 1] * base + x) % mod2;
        p1[i] = p1[i - 1] * base % mod1;
        p2[i] = p2[i - 1] * base % mod2;
    }
    unordered_set<pair<int, int>, Hash> st;
    for (int i = 1; i <= n; i++)
    {
        int cnt = 0;
        for (int j = i; j <= n; j++)
        {
            cnt += (check[s[j - 1] - 'a'] == '0');
            if (cnt > k)
                break;
            int x = (h1[j] - h1[i - 1] * p1[j - i + 1] % mod1 + mod1) % mod1;
            int y = (h2[j] - h2[i - 1] * p2[j - i + 1] % mod2 + mod2) % mod2;
            st.insert({x, y});
        }
    }
    cout << st.size();
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
