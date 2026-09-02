/*************************
  Author: Defy logic guy
  22:15:48 - 27/08/2026
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
#define NAME "TRAM_DO"

struct Segtree
{
    int n;
    vector<int> tree;
    Segtree(int n, const vector<int> &a) : n(n)
    {
        tree.assign(4 * n, 0);
        build(1, 1, n, a);
    }
    void build(int idx, int l, int r, const vector<int> &a)
    {
        if (l == r)
        {
            tree[idx] = a[l];
            return;
        }
        int m = l + r >> 1;
        build(idx << 1, l, m, a);
        build(idx << 1 | 1, m + 1, r, a);
        tree[idx] = tree[idx << 1] + tree[idx << 1 | 1];
    }
    void upd(int idx, int l, int r, int pos, int x)
    {
        if (l == r)
        {
            tree[idx] = x;
            return;
        }
        int m = l + r >> 1;
        if (pos <= m)
            upd(idx << 1, l, m, pos, x);
        else
            upd(idx << 1 | 1, m + 1, r, pos, x);
        tree[idx] = tree[idx << 1] + tree[idx << 1 | 1];
    }
    int get(int idx, int l, int r, int ql, int qr)
    {
        if (ql <= l and r <= qr)
            return tree[idx];
        if (qr < l or r < ql)
            return 0;
        int m = l + r >> 1;
        return (get(idx << 1, l, m, ql, qr) + get(idx << 1 | 1, m + 1, r, ql, qr));
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    Segtree st(n, a);
    while (q--)
    {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 1)
            st.upd(1, 1, n, u, v);
        else
            cout << st.get(1, 1, n, u, v) << '\n';
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
