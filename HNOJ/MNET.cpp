/*************************
  Author: Defy logic guy
  13:49:20 - 31/07/2026
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
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define maxall(x) *max_element(all(x))
#define minall(x) *min_element(all(x))
#define heap priority_queue
#define pb push_back
#define MOD 1000000007
#define NAME "MNET"

const int N = 5e5 + 5;
int num[N], low[N], cur = 1;
bool check[N];
vector<int> adj[N];
vector<vector<int>> ans;
stack<int> st;

void solve()
{
    int n, m;
    cin >> n >> m;
    while (m--)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
    }
    for (int s = 1; s <= n; s++)
    {
        if (num[s])
            continue;
        stack<pair<int, int>> dfs;
        num[s] = low[s] = cur++;
        st.push(s);
        check[s] = true;
        dfs.push({s, 0});
        while (dfs.size())
        {
            int u = dfs.top().first;
            int &id = dfs.top().second;
            if (id < adj[u].size())
            {
                int v = adj[u][id++];
                if (!num[v])
                {
                    num[v] = low[v] = cur++;
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
                    low[p] = min(low[p], low[u]);
                }
                if (low[u] == num[u])
                {
                    vector<int> v;
                    while (true)
                    {
                        int x = st.top();
                        st.pop();
                        check[x] = false;
                        v.pb(x);
                        if (x == u)
                            break;
                    }
                    ans.pb(v);
                }
            }
        }
    }
    cout << ans.size() << '\n';
    for (auto v : ans)
    {
        for (int x : v)
            cout << x << ' ';
        cout << '\n';
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
