/*************************
  Author: Defy logic guy
  19:45:31 - 18/09/2026
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
auto operator<<(ostream &os, const T &c) -> typename enable_if<!is_same<T, string>::value, decltype(c.begin(), c.end(), os)>::t
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
#define NAME "STADV_B"

const int INF = (1LL << 60);

struct Segtree
{
    vector<int> lo, hi;

    Segtree(int n)
    {
        lo.assign(4 * n + 5, 0);
        hi.assign(4 * n + 5, INF);
    }

    void appmx(int idx, int x)
    {
        lo[idx] = max(lo[idx], x);
        hi[idx] = max(hi[idx], x);
    }

    void appmn(int idx, int x)
    {
        lo[idx] = min(lo[idx], x);
        hi[idx] = min(hi[idx], x);
    }

    void push(int idx)
    {
        appmx(idx << 1, lo[idx]);
        appmn(idx << 1, hi[idx]);
        appmx(idx << 1 | 1, lo[idx]);
        appmn(idx << 1 | 1, hi[idx]);
        lo[idx] = 0;
        hi[idx] = INF;
    }

    void upd(int idx, int l, int r, int ql, int qr, int x, int t)
    {
        if (qr < l or r < ql)
            return;
        if (ql <= l and r <= qr)
        {
            if (t == 1)
                appmx(idx, x);
            else
                appmn(idx, x);
            return;
        }
        push(idx);
        int mid = l + r >> 1;
        upd(idx << 1, l, mid, ql, qr, x, t);
        upd(idx << 1 | 1, mid + 1, r, ql, qr, x, t);
    }

    void get(int idx, int l, int r, vector<int> &ans)
    {
        if (l == r)
        {
            ans[l] = lo[idx];
            return;
        }
        push(idx);
        int mid = l + r >> 1;
        get(idx << 1, l, mid, ans);
        get(idx << 1 | 1, mid + 1, r, ans);
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    Segtree st(n);
    while (q--)
    {
        int t, l, r, h;
        cin >> t >> l >> r >> h;
        st.upd(1, 0, n - 1, l, r, h, t);
    }
    vector<int> ans(n);
    st.get(1, 0, n - 1, ans);
    for (int i = 0; i < n; i++)
        cout << ans[i] << ' ';
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
