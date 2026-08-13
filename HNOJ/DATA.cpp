/*************************
  Author: Defy logic guy
  19:45:25 - 31/07/2026
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
#define pb push_back
#define MOD 1000000007
#define NAME "DATA"

void solve()
{
    int n, m;
    while (cin >> n && n)
    {
        cin >> m;
        vector<vector<int>> adj(n + 1);
        vector<pair<int, int>> edges;
        while (m--)
        {
            int u, v;
            cin >> u >> v;
            adj[u].pb(v);
            edges.pb({u, v});
        }
        vector<int> num(n + 1), low(n + 1), idx(n + 1, -1);
        vector<bool> check(n + 1, false);
        stack<int> st;
        int cur = 0, scc_cnt = 0;
        for (int s = 1; s <= n; s++)
        {
            if (num[s])
                continue;
            stack<pair<int, int>> dfs;
            num[s] = low[s] = ++cur;
            st.push(s);
            check[s] = true;
            dfs.push({s, 0});
            while (dfs.size())
            {
                int u = dfs.top().first;
                int &id = dfs.top().second;
                if (id < (int)adj[u].size())
                {
                    int v = adj[u][id++];
                    if (!num[v])
                    {
                        num[v] = low[v] = ++cur;
                        st.push(v);
                        check[v] = true;
                        dfs.push({v, 0});
                    }
                    else if (check[v])
                        low[u] = min(low[u], num[v]);
                }
                else
                {
                    dfs.pop();
                    if (dfs.size())
                    {
                        int p = dfs.top().first;
                        if (check[u])
                            low[p] = min(low[p], low[u]);
                    }
                    if (low[u] == num[u])
                    {
                        while (true)
                        {
                            int v = st.top();
                            st.pop();
                            check[v] = false;
                            idx[v] = scc_cnt;
                            if (v == u)
                                break;
                        }
                        scc_cnt++;
                    }
                }
            }
        }
        int ans = 0;
        for (auto [u, v] : edges)
            if (idx[u] == idx[v])
                ans++;
        cout << ans << '\n';
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
