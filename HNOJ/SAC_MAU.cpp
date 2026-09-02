/*************************
  Author: Defy logic guy
  20:30:46 - 27/08/2026
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
        os << (it == c.begin() ? "" : "\n") << *it;
    return os;
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
#define NAME "SAC_MAU"

int s;
struct Query
{
    int l, r, idx;
    Query(int l = 0, int r = 0, int idx = 0) : l(l), r(r), idx(idx) {}
    bool operator<(const Query &o) const
    {
        int ba = l / s, bb = o.l / s;
        if (ba != bb)
            return ba < bb;
        return (ba & 1) ? (r > o.r) : (r < o.r);
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1), c;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        c.pb(a[i]);
    }
    sort(all(c));
    c.erase(unique(all(c)), c.end());
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(all(c), a[i]) - c.begin();
    int q;
    cin >> q;
    vector<Query> qry(q);
    for (int i = 0; i < q; i++)
        cin >> qry[i].l >> qry[i].r, qry[i].idx = i;
    s = sqrt(n);
    sort(all(qry));
    vector<int> vis(c.size(), 0);
    int cnt = 0;
    auto add = [&](int idx) -> void
    {
        if (!vis[a[idx]])
            cnt++;
        vis[a[idx]]++;
    };
    auto del = [&](int idx) -> void
    {
        vis[a[idx]]--;
        if (!vis[a[idx]])
            cnt--;
    };
    int cl = 1, cr = 0;
    vector<int> ans(q);
    for (int i = 0; i < q; i++)
    {
        int l = qry[i].l, r = qry[i].r;
        while (cr < r)
            add(++cr);
        while (cr > r)
            del(cr--);
        while (cl < l)
            del(cl++);
        while (cl > l)
            add(--cl);
        ans[qry[i].idx] = cnt;
    }
    cout << ans;
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
