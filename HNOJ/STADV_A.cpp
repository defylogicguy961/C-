/*************************
  Author: Defy logic guy
  19:06:53 - 18/09/2026
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
#define MOD 998244353
#define NAME "STADV_A"

struct node
{
    int sum, b, c;
};

int n, q;
vector<node> st;

void init(int idx, int l, int r, const vector<int> &a)
{
    st[idx].b = 1, st[idx].c = 0;
    if (l == r)
    {
        st[idx].sum = a[l];
        return;
    }
    int m = l + r >> 1;
    init(idx << 1, l, m, a);
    init(idx << 1 | 1, m + 1, r, a);
    st[idx].sum = (st[idx << 1].sum + st[idx << 1 | 1].sum) % MOD;
}

void apply(int idx, int l, int r, int b, int c)
{
    st[idx].sum = (b * st[idx].sum + c * (r - l + 1)) % MOD;
    st[idx].b = b * st[idx].b % MOD;
    st[idx].c = (b * st[idx].c + c) % MOD;
}

void push(int idx, int l, int r)
{
    if (l == r)
        return;
    if (st[idx].b == 1 and st[idx].c == 0)
        return;
    int m = l + r >> 1;
    apply(idx << 1, l, m, st[idx].b, st[idx].c);
    apply(idx << 1 | 1, m + 1, r, st[idx].b, st[idx].c);
    st[idx].b = 1, st[idx].c = 0;
}

void upd(int idx, int l, int r, int ql, int qr, int b, int c)
{
    if (qr < l or r < ql)
        return;
    if (ql <= l and r <= qr)
    {
        apply(idx, l, r, b, c);
        return;
    }
    push(idx, l, r);
    int m = l + r >> 1;
    upd(idx << 1, l, m, ql, qr, b, c);
    upd(idx << 1 | 1, m + 1, r, ql, qr, b, c);
    st[idx].sum = (st[idx << 1].sum + st[idx << 1 | 1].sum) % MOD;
}

int get(int idx, int l, int r, int ql, int qr)
{
    if (qr < l or r < ql)
        return 0;
    if (ql <= l and r <= qr)
        return st[idx].sum;
    push(idx, l, r);
    int m = l + r >> 1;
    return (get(idx << 1, l, m, ql, qr) + get(idx << 1 | 1, m + 1, r, ql, qr)) % MOD;
}

void solve()
{
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    st.resize(4 * n + 5);
    init(1, 0, n - 1, a);
    while (q--)
    {
        int t;
        cin >> t;
        if (t == 0)
        {
            int l, r, b, c;
            cin >> l >> r >> b >> c;
            upd(1, 0, n - 1, l, r - 1, b, c);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << get(1, 0, n - 1, l, r - 1) << '\n';
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
