/*************************
  Author: Defy logic guy
  19:05:30 - 30/08/2025
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
#define NAME "C_Alternated"

void solve()
{
    int n;
    string s;
    cin >> n >> s;
    vector<int> a;
    for (int i = 0; i < s.size(); i++)
        if (s[i] == 'A')
            a.pb(i);
    int one = 0, two = 0;
    for (int i = 0; i < a.size(); i++)
    {
        one += abs(a[i] - (2 * i));
        two += abs(a[i] - (2 * i + 1));
    }
    cout << min(one, two) << '\n';
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
