/*************************
  Author: Defy logic guy
  22:28:41 - 19/07/2025
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
#define NAME "475D"

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    vector<int> lg(n + 1, 0);
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i / 2] + 1;
    vector<vector<int>> st(n + 1, vector<int>(20, 0));
    for (int i = 1; i <= n; i++)
        st[i][0] = a[i];
    for (int j = 1; j < 20; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            st[i][j] = __gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    auto get = [&](int l, int r)
    {
        int k = lg[r - l + 1];
        return __gcd(st[l][k], st[r - (1 << k) + 1][k]);
    };
    map<int, int> mp;
    for (int i = 1; i <= n; i++)
    {
        int pos = i;
        while (pos <= n)
        {
            int cur = get(i, pos);
            int l = pos, r = n, res = pos;
            while (l <= r)`
            {
                int mid = (l + r) >> 1;
                if (get(i, mid) == cur)
                {
                    res = mid;
                    l = mid + 1;
                }
                else
                    r = mid - 1;
            }
            mp[cur] += (res - pos + 1);
            pos = res + 1;
        }
    }
    int q;
    cin >> q;
    while (q--)
    {
        int x;
        cin >> x;
        cout << (mp.count(x) ? mp[x] : 0ll) << '\n';
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
    cout.tie(nullptr);

    int tt = 1;
    // cin >> tt;

    while (tt--)
        solve();
    return 0;
}
