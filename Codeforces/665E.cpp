/*************************
  Author: Defy logic guy
  22:09:15 - 24/10/2026
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
// #define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define maxall(x) *max_element(all(x))
#define minall(x) *min_element(all(x))
#define heap priority_queue
#define pb emplace_back
#define MOD 1000000007
#define NAME "665E"

struct Trie
{
    struct Node
    {
        int c[2], cnt;
        Node() : cnt(0) { c[0] = c[1] = -1; }
    };

    vector<Node> a;
    int k;
    Trie(int n = 0) { a.pb(); }

    void insert(long long x)
    {
        int pos = 0;
        a[pos].cnt++;
        for (int i = 30; i >= 0; i--)
        {
            int b = (x >> i) & 1;
            if (a[pos].c[b] == -1)
            {
                a[pos].c[b] = a.size();
                a.pb();
            }
            pos = a[pos].c[b];
            a[pos].cnt++;
        }
    }

    long long get(long long x)
    {
        int pos = 0;
        long long res = 0;
        for (int i = 30; i >= 0; i--)
        {
            if (pos == -1)
                break;
            int xb = (x >> i) & 1, kb = (k >> i) & 1;
            if (!kb)
            {
                int v = a[pos].c[xb ^ 1];
                if (v != -1)
                    res += a[v].cnt;
                pos = a[pos].c[xb];
            }
            else
                pos = a[pos].c[xb ^ 1];
        }
        if (pos != -1)
            res += a[pos].cnt;
        return res;
    }
};

void solve()
{
    int n, k;
    cin >> n >> k;
    Trie trie;
    trie.k = k;
    trie.insert(0ll);
    long long pf = 0, ans = 0;
    for (int i = 0; i < n; i++)
    {
        long long x;
        cin >> x;
        pf ^= x;
        ans += trie.get(pf);
        trie.insert(pf);
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
    // cin >> tt;

    while (tt--)
        solve();

    return 0;
}
