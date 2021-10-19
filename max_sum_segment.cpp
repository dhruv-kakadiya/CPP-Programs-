#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef pair<int, int> pii;
typedef pair<string, string> pss;
typedef pair<ll, ll> pll;
typedef vector<pii> vii;
typedef vector<pll> vll;
typedef vector<pss> vss;
typedef set<int> si;
typedef set<ll> sl;
typedef set<pii> sii;
typedef map<string, int> msi;
typedef map<int, int> mii;
typedef map<ll, ll> mll;
typedef unordered_map<int, int> umii;
typedef unordered_map<char, char> umcc;
typedef unordered_map<ll, ll> umll;
typedef unordered_map<string, ll> umsl;
typedef unordered_map<string, int> umsi;
typedef unordered_map<string, string> umss;
typedef unordered_set<int> usi;
typedef unordered_set<char> usc;
typedef unordered_set<pii> usii;
typedef unordered_set<pll> usll;
typedef unordered_set<ll> usl;
typedef unordered_set<string> uss;

#define all(x) (x).begin(), (x).end()
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define ff(i, a, b) for (int i = int(a); i < int(b); i++)
#define ffn(i, n) ff(i, 0, n)

struct node
{
    ll maxSum, prefSum, sufSum, sum;
};

struct segTree
{
    int size;
    node null = {0, 0, 0, 0};
    vector<node> sums;

    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        sums.assign(2 * size, null);
    }

    node merge(node a, node b)
    {
        node ans;
        ans.maxSum = max(a.maxSum, max(b.maxSum, a.sufSum + b.prefSum));
        ans.prefSum = max(a.prefSum, a.sum + b.prefSum);
        ans.sufSum = max(b.sufSum, a.sufSum + b.sum);
        ans.sum = a.sum + b.sum;
        return ans;
    }

    // void build(vl a, int x, int lx, int rx)
    // {
    // 	if (rx - lx == 1)
    // 	{
    // 		if (lx < (int)a.size())
    // 			sums[x] = a[lx];
    // 		return;
    // 	}

    // 	int mid = lx + (rx - lx) / 2;
    // 	build(a, 2 * x + 1, lx, mid);
    // 	build(a, 2 * x + 2, mid, rx);
    // 	sums[x] = merge(sums[2 * x + 1], sums[2 * x + 2]);
    // }

    // void build(vl a)
    // {
    // 	build(a, 0, 0, size);
    // }

    void set(int i, int v, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (v > 0)
                sums[x] = {1ll * v, 1ll * v, 1ll * v, 1ll * v};
            else
                sums[x] = {0, 0, 0, 1ll * v};
            return;
        }

        int mid = lx + (rx - lx) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, lx, mid);
        else
            set(i, v, 2 * x + 2, mid, rx);
        sums[x] = merge(sums[2 * x + 1], sums[2 * x + 2]);
    }

    void set(int i, int v)
    {
        set(i, v, 0, 0, size);
    }

    node query(int l, int r, int x, int lx, int rx)
    {
        if (lx >= r || l >= rx)
            return null;
        if (lx >= l && rx <= r)
            return sums[x];

        int mid = lx + (rx - lx) / 2;
        node s1 = query(l, r, 2 * x + 1, lx, mid);
        node s2 = query(l, r, 2 * x + 2, mid, rx);
        return merge(s1, s2);
    }

    ll query(int l, int r)
    {
        return query(l, r, 0, 0, size).maxSum;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    segTree st;
    st.init(n);

    // vl a(n);
    // ffn(i, n) cin >> a[i];
    // st.build(a);

    ffn(i, n)
    {
        int v;
        cin >> v;
        st.set(i, v);
    }

    cout << st.query(0, n) << endl;
    ffn(i, m)
    {
        // int op;
        // cin >> op;

        // if (op == 1)
        // {
        // 	int i, v;
        // 	cin >> i >> v;
        // 	st.set(i, v);
        // }
        // else
        // {
        // 	int l, r;
        // 	cin >> l >> r;
        // 	node ans = st.rMin(l, r);
        // 	cout << ans.minEle << " " << ans.cnt << endl;
        // }

        int j, v;
        cin >> j >> v;
        st.set(j, v);
        cout << st.query(0, n) << endl;
    }
    return 0;
}
