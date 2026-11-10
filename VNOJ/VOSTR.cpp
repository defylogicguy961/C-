/*************************
  Author: Defy logic guy
  20:18:58 - 07/11/2026
*************************/
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
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
#define lll long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define maxall(x) *max_element(all(x))
#define minall(x) *min_element(all(x))
#define heap priority_queue
#define pb emplace_back
#define MOD1 1000000007
#define MOD2 1000000009
#define NAME "VOSTR"

const lll base1 = 59, base2 = 241;
vector<lll> p1, p2;
struct idk
{
    vector<lll> h1, h2;

    idk(const string &s)
    {
        int n = s.size();
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);

        for (int i = 1; i <= n; i++)
        {
            int c = s[i - 1] - 'a';
            h1[i] = h1[i - 1] + p1[i - 1] * c;
            h2[i] = h2[i - 1] + p2[i - 1] * c;
        }
    }

    pair<lll, lll> get(int l, int r)
    {
        return {
            h1[r] - h1[l - 1],
            h2[r] - h2[l - 1]};
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    p1.assign(max(n, m) + 1, 1);
    p2.assign(max(n, m) + 1, 1);
    for (int i = 1; i <= max(n, m); i++)
    {
        p1[i] = p1[i - 1] * base1;
        p2[i] = p2[i - 1] * base2;
    }
    idk one(s), two(t);
    int q;
    cin >> q;
    while (q--)
    {
        int l, r, u, v;
        cin >> l >> r >> u >> v;
        int ll = 0, rr = min(r - l + 1, v - u + 1);
        int k = 0;
        while (ll <= rr)
        {
            int mid = ll + rr >> 1;
            if (mid == 0)
            {
                k = 0;
                ll = 1;
                continue;
            }
            auto x = one.get(l, l + mid - 1);
            auto y = two.get(u, u + mid - 1);
            if (x.first * p1[u] == y.first * p1[l] and x.second * p2[u] == y.second * p2[l])
                k = mid, ll = mid + 1;
            else
                rr = mid - 1;
        }
        if (k == min(r - l + 1, v - u + 1))
        {
            if (r - l == v - u)
                cout << '=';
            else if (r - l < v - u)
                cout << '<';
            else
                cout << '>';
        }
        else
        {
            if (s[l + k - 1] < t[u + k - 1])
                cout << '<';
            else
                cout << '>';
        }
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
