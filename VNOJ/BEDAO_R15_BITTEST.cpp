/*************************
  Author: Defy logic guy
  21:59:39 - 07/11/2026
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
#define MOD1 1000000007
#define MOD2 1000000009
#define NAME "BEDAO_R15_BITTEST"

struct Node
{
    int h1, h2;
    bool lazy;
    Node(int h1 = 0, int h2 = 0, bool lazy = false) : h1(h1), h2(h2), lazy(lazy) {}
};

string s;
int n;
vector<Node> st;
vector<int> p1, p2, sum1, sum2;
const int base = 311;

void apply(int idx, int l, int r)
{
    int len = r - l + 1;
    st[idx].h1 = (sum1[len] - st[idx].h1 + MOD1) % MOD1;
    st[idx].h2 = (sum2[len] - st[idx].h2 + MOD2) % MOD2;
    st[idx].lazy ^= 1;
}

void push(int idx, int l, int r)
{
    if (!st[idx].lazy or l == r)
        return;
    int m = l + r >> 1;
    apply(idx << 1, l, m);
    apply(idx << 1 | 1, m + 1, r);
    st[idx].lazy = 0;
}

void pull(int idx, int l, int r)
{
    int m = l + r >> 1;
    int len = r - m;
    st[idx].h1 = (st[idx << 1].h1 * p1[len] + st[idx << 1 | 1].h1) % MOD1;
    st[idx].h2 = (st[idx << 1].h2 * p2[len] + st[idx << 1 | 1].h2) % MOD2;
}

void build(int idx, int l, int r)
{
    if (l == r)
    {
        st[idx].h1 = s[l - 1] - '0';
        st[idx].h2 = s[l - 1] - '0';
        return;
    }
    int m = l + r >> 1;
    build(idx << 1, l, m);
    build(idx << 1 | 1, m + 1, r);
    pull(idx, l, r);
}

void upd(int idx, int l, int r, int u, int v)
{
    if (v < l or r < u)
        return;
    if (u <= l and r <= v)
    {
        apply(idx, l, r);
        return;
    }
    push(idx, l, r);
    int m = l + r >> 1;
    upd(idx << 1, l, m, u, v);
    upd(idx << 1 | 1, m + 1, r, u, v);
    pull(idx, l, r);
}

pair<int, int> get(int idx, int l, int r, int u, int v)
{
    if (v < l or r < u)
        return {0, 0};
    if (u <= l and r <= v)
        return {st[idx].h1, st[idx].h2};
    push(idx, l, r);
    int m = l + r >> 1;
    auto a = get(idx << 1, l, m, u, v);
    auto b = get(idx << 1 | 1, m + 1, r, u, v);
    int t = max(0ll, min(v, r) - max(u, m + 1) + 1);
    return {(a.first * p1[t] + b.first) % MOD1, (a.second * p2[t] + b.second) % MOD2};
}

void solve()
{
    cin >> s;
    n = s.size();
    p1.assign(n + 1, 1), p2.assign(n + 1, 1);
    sum1.assign(n + 1, 0), sum2.assign(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        p1[i] = p1[i - 1] * base % MOD1;
        p2[i] = p2[i - 1] * base % MOD2;
        sum1[i] = (sum1[i - 1] + p1[i - 1]) % MOD1;
        sum2[i] = (sum2[i - 1] + p2[i - 1]) % MOD2;
    }
    st.assign(4 * n, Node());
    build(1, 1, n);
    int q;
    cin >> q;
    while (q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int l, r;
            cin >> l >> r;
            upd(1, 1, n, l, r);
        }
        else
        {
            int x, y, z, t;
            cin >> x >> y >> z >> t;
            if (y - x != t - z)
            {
                cout << "NO\n";
                continue;
            }
            auto a = get(1, 1, n, x, y);
            auto b = get(1, 1, n, z, t);
            cout << (a == b ? "YES\n" : "NO\n");
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
