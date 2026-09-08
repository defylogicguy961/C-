/*************************
  Author: Defy logic guy
  20:41:09 - 03/09/2026
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
#define NAME "CAP_DAO_NGUOC"

int N = 5e4 + 5;
struct Fenwreck
{
    int n;
    vector<int> a;
    Fenwreck(int n = 1) : n(n) { a.assign(n + 1, 0); }
    void upd(int idx, int val)
    {
        while (idx <= n)
        {
            a[idx] += val;
            idx += idx & -idx;
        }
    }
    int get(int idx)
    {
        int ans = 0;
        while (idx > 0)
        {
            ans += a[idx];
            idx -= idx & -idx;
        }
        return ans;
    }
};

void solve()
{
    Fenwreck f(N);
    int n;
    cin >> n;
    int sz = sqrt(n), cur = 0;
    vector<int> a(n + 1);
    vector<vector<int>> block(n / sz + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        cur += i - 1 - f.get(a[i]);
        f.upd(a[i], 1);
        block[i / sz].pb(a[i]);
    }
    for (int i = 0; i <= n / sz; i++)
        sort(all(block[i]));
    int m;
    cin >> m;
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        if (a[x] == y)
        {
            cout << cur << '\n';
            continue;
        }
        int idx = x / sz;
        for (int i = 0; i < idx; i++)
        {
            cur -= block[i].end() - upper_bound(all(block[i]), a[x]);
            cur += block[i].end() - upper_bound(all(block[i]), y);
        }
        for (int i = idx + 1; i <= n / sz; i++)
        {
            cur -= lower_bound(all(block[i]), a[x]) - block[i].begin();
            cur += lower_bound(all(block[i]), y) - block[i].begin();
        }
        int st = idx * sz;
        int nd = min(n, (idx + 1) * sz - 1);
        st = max(st, 1ll);
        for (int i = st; i <= nd; i++)
            if (i == x)
                continue;
            else if (i < x)
            {
                if (a[i] > a[x])
                    cur--;
                if (a[i] > y)
                    cur++;
            }
            else
            {
                if (a[i] < a[x])
                    cur--;
                if (a[i] < y)
                    cur++;
            }
        auto it = lower_bound(all(block[idx]), a[x]);
        block[idx].erase(it);
        block[idx].insert(lower_bound(all(block[idx]), y), y);
        a[x] = y;
        cout << cur << '\n';
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
