/*************************
  Author: Defy logic guy
  20:53:09 - 15/09/2026
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
auto operator<<(ostream &os, const T &c) -> typename enable_if<!is_same<T, string>::value, decltype(all(c), os)>::type
{
    for (auto it = c.begin(); it != c.end(); it++)
        os << (it == c.begin() ? "{" : ", ") << *it;
    return os << "}";
}
#define dbg(x) cerr << #x << " = " << (x) << '\n';
// #define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define maxall(x) *max_element(all(x))
#define minall(x) *min_element(all(x))
#define heap priority_queue
#define pb emplace_back
#define MOD 1000000007
#define NAME "RMQ_DIVSEQ"

const int N = 5e5;
int stmx[20][N], stmn[20][N];
void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    vector<int> c(1 + all(a));
    sort(all(c));
    c.erase(unique(all(c)), c.end());
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(all(c), a[i]) - c.begin();
    int m = c.size();
    vector<int> lst(m, 0), l(n + 1), r(n + 1);
    for (int i = 1; i <= n; i++)
    {
        l[i] = lst[a[i]];
        lst[a[i]] = i;
    }
    fill(all(lst), n + 1);
    for (int i = n; i >= 1; i--)
    {
        r[i] = lst[a[i]];
        lst[a[i]] = i;
    }
    vector<int> lg(n + 1);
    lg[1] = 0;
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i / 2] + 1;
    for (int i = 1; i <= n; i++)
        stmx[0][i] = l[i], stmn[0][i] = r[i];
    for (int j = 1; j < 20; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
        {
            stmx[j][i] = max(stmx[j - 1][i], stmx[j - 1][i + (1 << (j - 1))]);
            stmn[j][i] = min(stmn[j - 1][i], stmn[j - 1][i + (1 << (j - 1))]);
        }
    auto mx = [&](int l, int r) -> int
    {
        if (l > r)
            return 0;
        int k = lg[r - l + 1];
        return max(stmx[k][l], stmx[k][r - (1 << k) + 1]);
    };
    auto mn = [&](int l, int r) -> int
    {
        if (l > r)
            return n + 1;
        int k = lg[r - l + 1];
        return min(stmn[k][l], stmn[k][r - (1 << k) + 1]);
    };
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        cout << max(0, min(mn(l, r), r) - max(mx(l, r), l))
             << '\n';
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
