/*************************
  Author: Defy logic guy
  19:05:33 - 30/08/2025
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
#define NAME "D_RLE_Moving"

pair<int, int> mv(char c)
{
    if (c == 'U')
        return {-1, 0};
    if (c == 'D')
        return {1, 0};
    if (c == 'L')
        return {0, -1};
    return {0, 1};
}

void solve()
{
    int rt, ct, ra, ca;
    cin >> rt >> ct >> ra >> ca;
    int n, m, l;
    cin >> n >> m >> l;
    vector<pair<char, int>> s(m);
    for (int i = 0; i < m; ++i)
    {
        string c;
        int a;
        cin >> c >> a;
        s[i] = {c[0], a};
    }
    vector<pair<char, int>> t(l);
    for (int i = 0; i < l; ++i)
    {
        string c;
        int b;
        cin >> c >> b;
        t[i] = {c[0], b};
    }

    int tr = rt - ra, tc = ct - ca;
    int i = 0, j = 0;
    int rms = (m ? s[0].second : 0), rmt = (l ? t[0].second : 0);
    int cr = 0, cc = 0;
    int ans = 0;

    while (i < m and j < l)
    {
        int len = min(rms, rmt);
        pair<int, int> vs = mv(s[i].first), vt = mv(t[j].first);
        int dr = vt.first - vs.first, dc = vt.second - vs.second;

        if (dr == 0 and dc == 0)
        {
            if (cr == tr and cc == tc)
                ans += len;
        }
        else
        {
            if (dr == 0)
            {
                if (cr == tr)
                {
                    int nc = tc - cc;
                    if (dc != 0 and nc % dc == 0)
                    {
                        int t = nc / dc;
                        if (1 <= t and t <= len)
                            ans++;
                    }
                }
            }
            else if (dc == 0)
            {
                if (cc == tc)
                {
                    int nr = tr - cr;
                    if (dr != 0 and nr % dr == 0)
                    {
                        int t = nr / dr;
                        if (1 <= t and t <= len)
                            ans++;
                    }
                }
            }
            else
            {
                int nr = tr - cr, nc = tc - cc;
                if (nr % dr == 0 and nc % dc == 0)
                {
                    int tr = nr / dr, tc = nc / dc;
                    if (tr == tc and 1 <= tr and tr <= len)
                        ans++;
                }
            }
        }

        cr += dr * len, cc += dc * len;
        rms -= len, rmt -= len;
        if (rms == 0)
        {
            if (++i < m)
                rms = s[i].second;
        }
        if (rmt == 0)
        {
            if (++j < l)
                rmt = t[j].second;
        }
    }

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
    cout.tie(nullptr);

    int tt = 1;
    // cin >> tt;

    while (tt--)
        solve();

    return 0;
}
