/*************************
  Author: Defy logic guy
  18:49:17 - 30/10/2026
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
#define NAME "GOODS"

void solve()
{
    string s;
    cin >> s;
    vector<int> dp(s.size() + 1, 0);
    stack<int> st;
    for (int i = 0; i < s.size(); i++)
        if (s[i] == '(' or s[i] == '{' or s[i] == '[')
            st.push(i);
        else
        {
            if (st.empty() or
                (s[st.top()] == '(' and s[i] != ')') or
                (s[st.top()] == '[' and s[i] != ']') or
                (s[st.top()] == '{' and s[i] != '}'))
            {
                dp[i] = 0;
                while (st.size())
                    st.pop();
                continue;
            }
            dp[i] = 1;
            if (st.top() >= 1)
                dp[i] += dp[st.top() - 1];
            st.pop();
        }
    cout << accumulate(all(dp), 0ll);
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
