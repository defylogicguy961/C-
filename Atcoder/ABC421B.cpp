/*************************
  Author: Defy logic guy
  19:01:51 - 30/08/2025
*************************/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define float double
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define maxall(x) *max_element(all(x))
#define minall(x) *min_element(all(x))
#define heap priority_queue
#define pb push_back
#define MOD 1000000007
#define NAME "B_Fibonacci_Reversed"

void solve()
{
    int x, y;
    cin >> x >> y;
    auto f = [&](int a, int b)
    {
        int c = a + b;
        string s = to_string(c);
        reverse(all(s));
        return stoll(s);
    };
    for (int i = 3; i <= 10; i++)
        tie(x, y) = make_pair(y, f(x, y));
    cout << y;
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
    cout.tie(nullptr);

    int tt = 1;
    // cin >> tt;

    while (tt--)
        solve();

    return 0;
}
