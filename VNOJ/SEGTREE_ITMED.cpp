/*************************
  Author: Defy logic guy
  20:24:42 - 15/09/2026
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
#define NAME "SEGTREE_ITMED"

const int N = 1e5 + 5;
int tree[4 * N], a[N];
void init(int idx, int l, int r)
{
    if (l == r)
    {
        tree[idx] = a[l];
        return;
    }
    int m = l + r >> 1;
    init(idx << 1, l, m);
    init(idx << 1 | 1, m + 1, r);
    tree[idx] = max(tree[idx << 1], tree[idx << 1 | 1]);
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
    tree[idx] = max(tree[idx << 1], tree[idx << 1 | 1]);
}

int get(int idx, int l, int r, int ql, int qr)
{
    if (ql > r or qr < l)
        return LLONG_MIN;
    if (ql <= l and r <= qr)
        return tree[idx];
    int m = l + r >> 1;
    return max(get(idx << 1, l, m, ql, qr),
               get(idx << 1 | 1, m + 1, r, ql, qr));
}

void solve()
{
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    init(1, 0, n - 1);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int x = max(a[i], (!i ? 0 : get(1, 0, n - 1, max(0ll, i - k), i - 1)) + a[i]);
        upd(1, 0, n - 1, i, x);
        ans = max(ans, x);
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
