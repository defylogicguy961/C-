/*************************
  Author: Defy logic guy
  20:08:14 - 28/08/2026
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
#define NAME "DIEM_CAN_BANG"

vector<pair<int, int>> tree;
vector<int> a;

void build(int idx, int l, int r)
{
    if (l == r)
    {
        tree[idx] = {a[l], a[l]};
        return;
    }
    int m = l + r >> 1;
    build(idx << 1, l, m);
    build(idx << 1 | 1, m + 1, r);
    tree[idx].first = tree[idx << 1].first + tree[idx << 1 | 1].first;
    tree[idx].second = max(tree[idx << 1].second, tree[idx << 1 | 1].second);
}

void upd(int idx, int l, int r, int pos, int x)
{
    if (l == r)
    {
        tree[idx] = {x, x}, a[l] = x;
        return;
    }
    int m = l + r >> 1;
    if (pos <= m)
        upd(idx << 1, l, m, pos, x);
    else
        upd(idx << 1 | 1, m + 1, r, pos, x);
    tree[idx].first = tree[idx << 1].first + tree[idx << 1 | 1].first;
    tree[idx].second = max(tree[idx << 1].second, tree[idx << 1 | 1].second);
}

int get(int idx, int l, int r, int x)
{
    if (tree[idx].second < x)
    {
        if (!tree[idx].second and !x)
            return l;
        return -1;
    }
    if (l == r)
    {
        if (tree[idx].second == x)
            return l;
        return -1;
    }
    int m = l + r >> 1;
    int t = get(idx << 1, l, m, x);
    if (t != -1)
        return t;
    return get(idx << 1 | 1, m + 1, r, x + tree[idx << 1].first);
}

void solve()
{
    int n, q;
    cin >> n >> q;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    tree.resize(4 * (n + 1));
    build(1, 1, n);
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        upd(1, 1, n, u, v);
        cout << get(1, 1, n, 0) << '\n';
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
