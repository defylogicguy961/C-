/*************************
  Author: Defy logic guy
  20:38:24 - 08/09/2026
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
#define NAME "C11SEQ"

vector<int> tree, a;
int get(int idx, int l, int r, int ql, int qr)
{
    if (ql > r or qr < l)
        return 0;
    if (ql <= l and r <= qr)
        return tree[idx];
    int mid = l + r >> 1;
    return get(idx << 1, l, mid, ql, qr) +
           get(idx << 1 | 1, mid + 1, r, ql, qr);
}

void upd(int idx, int l, int r, int pos)
{
    if (l == r)
    {
        tree[idx]++;
        return;
    }
    int mid = l + r >> 1;
    if (pos <= mid)
        upd(idx << 1, l, mid, pos);
    else
        upd(idx << 1 | 1, mid + 1, r, pos);
    tree[idx] = tree[idx << 1] + tree[idx << 1 | 1];
}

void solve()
{
    int n, l, r;
    cin >> n >> l >> r;
    a.resize(n + 1);
    vector<int> pf;
    pf.pb(0);
    tree.assign(4 * n, 0);
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        a[i] = a[i - 1] + x;
        pf.pb(a[i]);
    }
    sort(all(pf));
    pf.resize(unique(all(pf)) - pf.begin());
    int ans = 0;
    for (int i = 0; i <= n; i++)
    {
        if (i)
        {
            int ll = lower_bound(all(pf), a[i] - r) - pf.begin() + 1;
            int rr = upper_bound(all(pf), a[i] - l) - pf.begin();
            if (ll <= rr)
                ans += get(1, 1, pf.size(), ll, rr);
        }
        upd(1, 1, pf.size(), lower_bound(all(pf), a[i]) - pf.begin() + 1);
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
