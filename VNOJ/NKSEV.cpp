/*************************
  Author: Defy logic guy
  20:05:57 - 24/10/2026
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
#define MOD 1337377
#define NAME "NKSEV"

struct Trie
{
    struct Node
    {
        vector<int> c;
        bool flag;
        Node() : c(26, -1), flag(false) {}
    };

    vector<Node> a;
    Trie(int n = 0) { a.pb(); }

    void insert(const string &s)
    {
        int pos = 0;
        for (char ch : s)
        {
            int id = ch - 'a';
            if (a[pos].c[id] == -1)
            {
                a[pos].c[id] = a.size();
                a.pb();
            }
            pos = a[pos].c[id];
        }
        a[pos].flag = true;
    }

    int get(const string &s)
    {
        vector<int> dp(s.size() + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < s.size(); i++)
        {
            int pos = 0;
            for (int j = i; j < s.size(); j++)
            {
                if (a[pos].c[s[j] - 'a'] == -1)
                    break;
                pos = a[pos].c[s[j] - 'a'];
                if (a[pos].flag)
                    (dp[j + 1] += dp[i]) %= MOD;
            }
        }
        return dp.back();
    }
};

void solve()
{
    string s;
    cin >> s;
    int n;
    cin >> n;
    Trie trie;
    for (int i = 0; i < n; i++)
    {
        string t;
        cin >> t;
        trie.insert(t);
    }
    cout << trie.get(s);
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
