/*************************
  Author: Defy logic guy
  13:54:11 - 06/10/2026
*************************/
#include <bits/stdc++.h>
using namespace std;
ostream &operator<<(ostream &os, const string &_)
{
    os.write(_.data(), _.size());
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
#define NAME "158C"

void solve()
{
    int n;
    cin >> n;
    stack<string> st;
    while (n--)
    {
        string _;
        cin >> _;
        if (_[0] == 'c')
        {
            string t;
            cin >> t;
            string tmp;
            vector<string> v;
            for (char c : t)
                if (c == '/')
                {
                    if (tmp.size())
                        v.pb(tmp);
                    tmp = "";
                }
                else
                    tmp += c;
            if (tmp.size())
                v.pb(tmp);
            if (t[0] == '/')
                while (st.size())
                    st.pop();
            for (string a : v)
                if (a == ".." and st.size())
                    st.pop();
                else
                    st.push(a);
        }
        else if (_[0] == 'p')
        {
            string ans;
            stack<string> tmp;
            while (st.size())
            {
                ans = st.top() + "/" + ans;
                tmp.push(st.top());
                st.pop();
            }
            cout << '/' << ans << '\n';
            while (tmp.size())
            {
                st.push(tmp.top());
                tmp.pop();
            }
        }
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
