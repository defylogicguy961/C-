/*************************
  Author: Defy logic guy
  21:54:51 - 19/07/2025
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
#define NAME "514D"

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];

    vector<int> lg(n + 1, 0);
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i / 2] + 1;

    vector<vector<vector<int>>> st(m, vector<vector<int>>(n, vector<int>(lg[n] + 1)));
    for (int t = 0; t < m; t++)
        for (int i = 0; i < n; i++)
            st[t][i][0] = a[i][t];

    for (int t = 0; t < m; t++)
        for (int j = 1; j < lg[n] + 1; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                st[t][i][j] = max(st[t][i][j - 1], st[t][i + (1 << (j - 1))][j - 1]);

    auto get = [&](int t, int l, int r)
    {
        int u = lg[r - l + 1];
        return max(st[t][l][u], st[t][r - (1 << u) + 1][u]);
    };

    int l = 1, r = n, res = 0;
    vector<int> ans(m, 0);
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        bool flag = false;
        vector<int> v(m, 0);
        for (int i = 0; i + mid - 1 < n; i++)
        {
            int sum = 0;
            vector<int> cur(m, 0);
            for (int t = 0; t < m; t++)
                cur[t] = get(t, i, i + mid - 1), sum += cur[t];
            if (sum <= k)
            {
                flag = true, v = cur;
                break;
            }
        }
        if (flag)
            res = mid, ans = v, l = mid + 1;
        else
            r = mid - 1;
    }

    for (int i : ans)
        cout << i << ' ';
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
