/*************************
  Author: Defy logic guy
  19:34:10 - 04/09/2026
*************************/
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
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
#define NAME "HAIMANG"

struct Pt
{
    int u, v;
};

void solve()
{
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++)
        cin >> x[i];
    for (int i = 0; i < n; i++)
        cin >> y[i];
    vector<Pt> pts(n);
    for (int i = 0; i < n; i++)
        pts[i] = {x[i] + y[i], x[i] - y[i]};

    int l = 0, r = 2e9;
    int ans = r;

    while (l <= r)
    {
        int m = l + (r - l) / 2;
        auto f = [&]() -> bool
        {
            vector<Pt> pu = pts;
            sort(all(pu), [](const Pt &a, const Pt &b)
                 { return a.u < b.u; });
            int mxu = pu.back().u, mnu = pu[0].u;
            int mxv = pu[0].v, mnv = pu[0].v;
            for (int i = 0; i < n; i++)
            {
                mxv = max(mxv, pu[i].v);
                mnv = min(mnv, pu[i].v);
            }
            if (mxu - mnu <= m and mxv - mnv <= m)
                return true;

            auto check_u_split = [&](bool min_u_in_g1) -> bool
            {
                int g1_min_v = 2e18, g1_max_v = -2e18;
                int g2_min_v = 2e18, g2_max_v = -2e18;
                int cnt1 = 0, cnt2 = 0;

                for (int i = 0; i < n; i++)
                {
                    bool force_g2_cond1 = (pu[i].u > pu[0].u + m);
                    bool force_g1_cond2 = (pu[i].u < pu[n - 1].u - m);

                    int forced = 0; // 0: unforced, 1: G1, 2: G2
                    if (min_u_in_g1)
                    {
                        bool to_g2 = force_g2_cond1;
                        bool to_g1 = force_g1_cond2;
                        if (to_g1 and to_g2)
                            return false;
                        if (to_g1)
                            forced = 1;
                        else if (to_g2)
                            forced = 2;
                    }
                    else
                    {
                        bool to_g1 = force_g2_cond1;
                        bool to_g2 = force_g1_cond2;
                        if (to_g1 and to_g2)
                            return false;
                        if (to_g1)
                            forced = 1;
                        else if (to_g2)
                            forced = 2;
                    }

                    if (forced == 1)
                    {
                        g1_min_v = min(g1_min_v, pu[i].v);
                        g1_max_v = max(g1_max_v, pu[i].v);
                        cnt1++;
                    }
                    else if (forced == 2)
                    {
                        g2_min_v = min(g2_min_v, pu[i].v);
                        g2_max_v = max(g2_max_v, pu[i].v);
                        cnt2++;
                    }
                }

                vector<Pt> unforced;
                for (int i = 0; i < n; i++)
                {
                    bool force_g2_cond1 = (pu[i].u > pu[0].u + m);
                    bool force_g1_cond2 = (pu[i].u < pu[n - 1].u - m);
                    bool is_unforced = false;
                    if (min_u_in_g1)
                    {
                        if (!force_g1_cond2 and !force_g2_cond1)
                            is_unforced = true;
                    }
                    else
                    {
                        if (!force_g2_cond1 and !force_g1_cond2)
                            is_unforced = true;
                    }
                    if (is_unforced)
                        unforced.pb(pu[i]);
                }

                if (unforced.empty())
                {
                    int span1 = (cnt1 > 0 ? g1_max_v - g1_min_v : 0);
                    int span2 = (cnt2 > 0 ? g2_max_v - g2_min_v : 0);
                    return span1 <= m and span2 <= m;
                }

                sort(all(unforced), [](const Pt &a, const Pt &b)
                     { return a.v < b.v; });
                int k = unforced.size();
                vector<int> pref_minv(k), pref_maxv(k);
                vector<int> suff_minv(k), suff_maxv(k);
                pref_minv[0] = pref_maxv[0] = unforced[0].v;
                for (int i = 1; i < k; i++)
                {
                    pref_minv[i] = min(pref_minv[i - 1], unforced[i].v);
                    pref_maxv[i] = max(pref_maxv[i - 1], unforced[i].v);
                }
                suff_minv[k - 1] = suff_maxv[k - 1] = unforced[k - 1].v;
                for (int i = k - 2; i >= 0; i--)
                {
                    suff_minv[i] = min(suff_minv[i + 1], unforced[i].v);
                    suff_maxv[i] = max(suff_maxv[i + 1], unforced[i].v);
                }

                for (int i = -1; i < k; i++)
                {
                    int cur_g1_min = g1_min_v, cur_g1_max = g1_max_v;
                    int cur_g2_min = g2_min_v, cur_g2_max = g2_max_v;

                    if (i >= 0)
                    {
                        cur_g1_min = (cnt1 > 0 ? min(cur_g1_min, pref_minv[i]) : pref_minv[i]);
                        cur_g1_max = (cnt1 > 0 ? max(cur_g1_max, pref_maxv[i]) : pref_maxv[i]);
                    }
                    if (i + 1 < k)
                    {
                        cur_g2_min = (cnt2 > 0 ? min(cur_g2_min, suff_minv[i + 1]) : suff_minv[i + 1]);
                        cur_g2_max = (cnt2 > 0 ? max(cur_g2_max, suff_maxv[i + 1]) : suff_maxv[i + 1]);
                    }
                    int span1 = (cnt1 > 0 || i >= 0) ? cur_g1_max - cur_g1_min : 0;
                    int span2 = (cnt2 > 0 || i + 1 < k) ? cur_g2_max - cur_g2_min : 0;
                    if (span1 <= m and span2 <= m)
                        return true;
                }
                return false;
            };

            if (mxu - mnu > m)
            {
                if (check_u_split(true) || check_u_split(false))
                    return true;
            }

            vector<Pt> pv = pts;
            sort(all(pv), [](const Pt &a, const Pt &b)
                 { return a.v < b.v; });
            int mxvall = pv.back().v, mnvall = pv[0].v;

            auto check_v_split = [&](bool min_v_in_g1) -> bool
            {
                int g1_min_u = 2e18, g1_max_u = -2e18;
                int g2_min_u = 2e18, g2_max_u = -2e18;
                int cnt1 = 0, cnt2 = 0;

                for (int i = 0; i < n; i++)
                {
                    bool force_g2_cond1 = (pv[i].v > pv[0].v + m);
                    bool force_g1_cond2 = (pv[i].v < pv[n - 1].v - m);

                    int forced = 0;
                    if (min_v_in_g1)
                    {
                        bool to_g2 = force_g2_cond1;
                        bool to_g1 = force_g1_cond2;
                        if (to_g1 and to_g2)
                            return false;
                        if (to_g1)
                            forced = 1;
                        else if (to_g2)
                            forced = 2;
                    }
                    else
                    {
                        bool to_g1 = force_g2_cond1;
                        bool to_g2 = force_g1_cond2;
                        if (to_g1 and to_g2)
                            return false;
                        if (to_g1)
                            forced = 1;
                        else if (to_g2)
                            forced = 2;
                    }

                    if (forced == 1)
                    {
                        g1_min_u = min(g1_min_u, pv[i].u);
                        g1_max_u = max(g1_max_u, pv[i].u);
                        cnt1++;
                    }
                    else if (forced == 2)
                    {
                        g2_min_u = min(g2_min_u, pv[i].u);
                        g2_max_u = max(g2_max_u, pv[i].u);
                        cnt2++;
                    }
                }

                vector<Pt> unforced;
                for (int i = 0; i < n; i++)
                {
                    bool force_g2_cond1 = (pv[i].v > pv[0].v + m);
                    bool force_g1_cond2 = (pv[i].v < pv[n - 1].v - m);
                    bool is_unforced = false;
                    if (min_v_in_g1)
                    {
                        if (!force_g1_cond2 and !force_g2_cond1)
                            is_unforced = true;
                    }
                    else
                    {
                        if (!force_g2_cond1 and !force_g1_cond2)
                            is_unforced = true;
                    }
                    if (is_unforced)
                        unforced.pb(pv[i]);
                }

                if (unforced.empty())
                {
                    int span1 = (cnt1 > 0 ? g1_max_u - g1_min_u : 0);
                    int span2 = (cnt2 > 0 ? g2_max_u - g2_min_u : 0);
                    return span1 <= m and span2 <= m;
                }

                sort(all(unforced), [](const Pt &a, const Pt &b)
                     { return a.u < b.u; });
                int k = unforced.size();
                vector<int> pref_minu(k), pref_maxu(k);
                vector<int> suff_minu(k), suff_maxu(k);
                pref_minu[0] = pref_maxu[0] = unforced[0].u;
                for (int i = 1; i < k; i++)
                {
                    pref_minu[i] = min(pref_minu[i - 1], unforced[i].u);
                    pref_maxu[i] = max(pref_maxu[i - 1], unforced[i].u);
                }
                suff_minu[k - 1] = suff_maxu[k - 1] = unforced[k - 1].u;
                for (int i = k - 2; i >= 0; i--)
                {
                    suff_minu[i] = min(suff_minu[i + 1], unforced[i].u);
                    suff_maxu[i] = max(suff_maxu[i + 1], unforced[i].u);
                }

                for (int i = -1; i < k; i++)
                {
                    int cur_g1_min = g1_min_u, cur_g1_max = g1_max_u;
                    int cur_g2_min = g2_min_u, cur_g2_max = g2_max_u;
                    if (i >= 0)
                    {
                        cur_g1_min = (cnt1 > 0 ? min(cur_g1_min, pref_minu[i]) : pref_minu[i]);
                        cur_g1_max = (cnt1 > 0 ? max(cur_g1_max, pref_maxu[i]) : pref_maxu[i]);
                    }
                    if (i + 1 < k)
                    {
                        cur_g2_min = (cnt2 > 0 ? min(cur_g2_min, suff_minu[i + 1]) : suff_minu[i + 1]);
                        cur_g2_max = (cnt2 > 0 ? max(cur_g2_max, suff_maxu[i + 1]) : suff_maxu[i + 1]);
                    }
                    int span1 = (cnt1 > 0 || i >= 0) ? cur_g1_max - cur_g1_min : 0;
                    int span2 = (cnt2 > 0 || i + 1 < k) ? cur_g2_max - cur_g2_min : 0;
                    if (span1 <= m and span2 <= m)
                        return true;
                }
                return false;
            };

            if (mxvall - mnvall > m)
            {
                if (check_v_split(true) || check_v_split(false))
                    return true;
            }

            return false;
        };

        if (f())
            ans = m, r = m - 1;
        else
            l = m + 1;
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

    int tt = 1;
    // cin >> tt;

    while (tt--)
        solve();

    return 0;
}