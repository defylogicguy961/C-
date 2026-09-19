/*************************
  Author: Defy logic guy
  20:20:32 - 19/09/2026
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
#define NAME "ELEVATOR"

struct node
{
    int h, a, c;
};

const int N = 4e4 + 5;
bool dp[N];
int used[N];
void solve()
{
    int n;
    cin >> n;
    vector<node> b(n);
    for (int i = 0; i < n; i++)
        cin >> b[i].h >> b[i].a >> b[i].c;
    sort(all(b), [](const node &x, const node &y)
         { return x.a < y.a; });
    dp[0] = true;
    int ans = 0;
    for (auto [h, a, c] : b)
    {
        fill(used, used + N, 0ll);
        for (int j = h; j <= a; j++)
            if (!dp[j] and dp[j - h] and used[j - h] < c)
            {
                dp[j] = true;
                used[j] = used[j - h] + 1;
                ans = max(ans, j);
            }
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
