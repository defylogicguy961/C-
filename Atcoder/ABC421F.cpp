/*************************
  Author: Defy logic guy
  20:22:19 - 30/08/2025
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
#define NAME "abc421f"

struct Node
{
    int val, sz, sum;
    unsigned int pr;
    Node *l, *r, *p;
    Node(int v, unsigned int prio)
    {
        val = v;
        pr = prio;
        l = r = p = nullptr;
        sz = 1;
        sum = v;
    }
};
int sz(Node *t) { return t ? t->sz : 0; }
int sum(Node *t) { return t ? t->sum : 0; }
void re(Node *t)
{
    if (!t)
        return;
    t->sz = 1 + sz(t->l) + sz(t->r);
    t->sum = t->val + sum(t->l) + sum(t->r);
    if (t->l)
        t->l->p = t;
    if (t->r)
        t->r->p = t;
}
Node *merge(Node *a, Node *b)
{
    if (!a)
    {
        if (b)
            b->p = nullptr;
        return b;
    }
    if (!b)
    {
        a->p = nullptr;
        return a;
    }
    if (a->pr > b->pr)
    {
        a->r = merge(a->r, b);
        if (a->r)
            a->r->p = a;
        re(a);
        a->p = nullptr;
        return a;
    }
    else
    {
        b->l = merge(a, b->l);
        if (b->l)
            b->l->p = b;
        re(b);
        b->p = nullptr;
        return b;
    }
}
void split(Node *t, int k, Node *&a, Node *&b)
{
    if (!t)
    {
        a = b = nullptr;
        return;
    }
    int lsz = sz(t->l);
    if (lsz >= k)
    {
        split(t->l, k, a, t->l);
        if (t->l)
            t->l->p = t;
        b = t;
        t->p = nullptr;
        re(b);
    }
    else
    {
        split(t->r, k - lsz - 1, t->r, b);
        if (t->r)
            t->r->p = t;
        a = t;
        t->p = nullptr;
        re(a);
    }
}
int idxx(Node *t)
{
    int idx = sz(t->l);
    Node *cur = t;
    while (cur->p)
    {
        if (cur == cur->p->r)
            idx += 1 + sz(cur->p->l);
        cur = cur->p;
    }
    return idx;
}
void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> a;
    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int x;
            cin >> x;
            a.pb({1, x});
        }
        else
        {
            int x, y;
            cin >> x >> y;
            a.pb({2, (x << 32) ^ y});
        }
    }

    vector<Node *> ptr(n + 1, nullptr);
    mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
    Node *rt = new Node(0, rng());
    ptr[0] = rt;

    for (int i = 0; i < n; ++i)
    {
        int t = a[i].first;
        if (t == 1)
        {
            int x = a[i].second;
            int val = i + 1;
            Node *nw = new Node(val, rng());
            ptr[val] = nw;
            int pos = idxx(ptr[x]);
            Node *a;
            Node *b;
            split(rt, pos + 1, a, b);
            rt = merge(merge(a, nw), b);
        }
        else
        {
            int x = (a[i].second >> 32);
            int y = (a[i].second & 0xffffffffLL);
            int ix = idxx(ptr[x]);
            int iy = idxx(ptr[y]);
            int l = min(ix, iy), r = max(ix, iy);
            if (r - l <= 1)
            {
                cout << 0 << '\n';
                continue;
            }
            Node *aa, *bc;
            split(rt, l + 1, aa, bc);
            Node *bb, *cc;
            split(bc, r - l - 1, bb, cc);
            int ans = sum(bb);
            cout << ans << '\n';
            vector<Node *> st;
            if (bb)
                st.pb(bb);
            while (st.size())
            {
                Node *cur = st.back();
                st.pop_back();
                if (cur->l)
                    st.pb(cur->l);
                if (cur->r)
                    st.pb(cur->r);
                ptr[cur->val] = nullptr;
                delete cur;
            }
            rt = merge(aa, cc);
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
    cout.tie(nullptr);

    int tt = 1;
    // cin >> tt;

    while (tt--)
        solve();

    return 0;
}
