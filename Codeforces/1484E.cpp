/*************************
  Author: Defy logic guy
  20:51:45 - 12/09/2026
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
#define NAME "1484E"

void solve()
{
    int n;
    cin >> n;
    vector<int> h(n), b(n);
    for (int i = 0; i < n; i++)
        cin >> h[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    vector<int> dp(n), mx(n);
    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        mx[i] = (st.empty() ? INT_MIN : dp[st.top()]);
        while (st.size() and h[st.top()] > h[i])
        {
            mx[i] = max(mx[i], mx[st.top()]);
            st.pop();
        }
        dp[i] = max((st.empty() ? b[i] : dp[st.top()]), mx[i] + b[i]);
        st.push(i);
    }
    cout << dp[n - 1];
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
