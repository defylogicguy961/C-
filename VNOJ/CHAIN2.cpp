/*************************
  Author: Defy logic guy
  19:36:24 - 24/10/2026
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
#define NAME "CHAIN2"

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

    int get()
    {
        int ans = 0;
        stack<pair<int, int>> st;
        st.push({0, 0});
        while (st.size())
        {
            auto [u, mx] = st.top();
            st.pop();
            if (a[u].flag)
                mx++, ans = max(ans, mx);
            for (int ch = 0; ch < 26; ch++)
            {
                int v = a[u].c[ch];
                if (v != -1)
                    st.push({v, mx});
            }
        }
        return ans;
    }
};

void solve()
{
    int n;
    cin >> n;
    Trie trie;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        trie.insert(s);
    }
    cout << trie.get();
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
