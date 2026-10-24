/*************************
  Author: Defy logic guy
  13:49:54 - 06/10/2026
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
#define NAME "817D"

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vector<int> l1(n), r1(n);
    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        while (st.size() and a[st.top()] > a[i])
            st.pop();
        l1[i] = st.size() ? st.top() : -1;
        st.push(i);
    }
    while (st.size())
        st.pop();
    for (int i = n - 1; i >= 0; i--)
    {
        while (st.size() and a[st.top()] >= a[i])
            st.pop();
        r1[i] = st.size() ? st.top() : n;
        st.push(i);
    }
    while (st.size())
        st.pop();
    vector<int> l2(n), r2(n);
    for (int i = 0; i < n; i++)
    {
        while (st.size() and a[st.top()] < a[i])
            st.pop();
        l2[i] = st.size() ? st.top() : -1;
        st.push(i);
    }
    while (st.size())
        st.pop();
    for (int i = n - 1; i >= 0; i--)
    {
        while (st.size() and a[st.top()] <= a[i])
            st.pop();
        r2[i] = st.size() ? st.top() : n;
        st.push(i);
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
        ans += a[i] * (i - l2[i]) * (r2[i] - i) - (i - l1[i]) * (r1[i] - i) * a[i];
    cout << ans;
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
