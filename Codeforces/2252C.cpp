/*************************
  Author: Defy logic guy
  21:24:15 - 06/08/2026
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
#define pb push_back
#define MOD 1000000007
#define NAME "2252C"

struct Seg
{
    int n;
    vector<int> sum, cnt, a;
    Seg(int n, const vector<int> &v) : n(n), a(v) { sum.assign(4 * n, 0), cnt.assign(4 * n, 0); }
    void upd(int idx, int l, int r, int pos, int x)
    {
        sum[idx] += x, cnt[idx]++;
        if (l == r)
            return;
        int m = l + r >> 1;
        if (pos <= m)
            upd(idx << 1, l, m, pos, x);
        else
            upd(idx << 1 | 1, m + 1, r, pos, x);
    }
    int get(int idx, int l, int r, int x)
    {
        if (l == r)
            return (a[l] + x - 1) / a[l];
        int m = l + r >> 1;
        if (sum[idx << 1 | 1] >= x)
            return get(idx << 1 | 1, m + 1, r, x);
        else
            return cnt[idx << 1 | 1] + get(idx << 1, l, m, x - sum[idx << 1 | 1]);
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    vector<vector<int>> a(n, vector<int>(m));
    vector<int> c;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j], c.pb(a[i][j]);
    sort(all(c));
    c.erase(unique(all(c)), c.end());
    Seg tree(c.size(), c);
    int ans = m;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < m; j++)
        {
            int pos = lower_bound(all(c), a[i][j]) - c.begin();
            tree.upd(1, 0, c.size() - 1, pos, a[i][j]);
        }
        if (tree.sum[1] >= v[i])
            ans = min(ans, tree.get(1, 0, c.size() - 1, v[i]));
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
    cin >> tt;

    while (tt--)
        solve();

    return 0;
}
