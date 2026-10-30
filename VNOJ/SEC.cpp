/*************************
  Author: Defy logic guy
  21:07:21 - 24/10/2026
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
#define NAME "SEC"

struct Trie
{
    struct Node
    {
        vector<int> c;
        int cnt, t;
        Node() : c(2, -1), cnt(0), t(0) {}
    };

    vector<Node> a;
    Trie(int n = 0) { a.pb(); }

    void insert(const vector<int> &v)
    {
        int pos = 0;
        for (int i : v)
        {
            if (a[pos].c[i] == -1)
            {
                a[pos].c[i] = a.size();
                a.pb();
            }
            pos = a[pos].c[i];
            a[pos].t++;
        }
        a[pos].cnt++;
    }

    int get(const vector<int> &v)
    {
        int pos = 0, ans = 0;
        for (int i : v)
        {
            if (a[pos].c[i] == -1)
                return ans;
            pos = a[pos].c[i];
            ans += a[pos].cnt;
        }
        return ans + a[pos].t - a[pos].cnt;
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    Trie trie;
    for (int i = 0; i < n; i++)
    {
        int m;
        cin >> m;
        vector<int> v(m);
        for (int j = 0; j < m; j++)
            cin >> v[j];
        trie.insert(v);
    }
    for (int i = 0; i < q; i++)
    {
        int m;
        cin >> m;
        vector<int> v(m);
        for (int j = 0; j < m; j++)
            cin >> v[j];
        cout << trie.get(v) << '\n';
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
