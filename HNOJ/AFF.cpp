/*************************
  Author: Defy logic guy
  18:35:56 - 30/10/2026
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
#define NAME "AFF"

struct node
{
    int t, k, s;
    node(int t = 0, int k = 0, int s = 0) : t(t), k(k), s(s) {}
};

void solve()
{
    int n, d;
    cin >> n >> d;
    vector<node> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i].t >> a[i].k >> a[i].s;
    sort(all(a), [](const node &x, const node &y)
         { return x.t < y.t; });
    heap<pair<int, int>> pq;
    int idx = 0, ans = 0;
    for (const auto &i : a)
        ans += i.k * i.s;
    for (int i = 1; i <= d; i++)
    {
        while (idx < n and a[idx].t <= i)
        {
            pq.push({a[idx].s, a[idx].k});
            idx++;
        }
        if (pq.size())
        {
            pair<int, int> t = pq.top();
            pq.pop();
            ans -= t.first;
            if (--t.second > 0)
                pq.push(t);
        }
    }
    cout << ans << '\n';
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
