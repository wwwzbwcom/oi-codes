#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int Mod = 1e9 + 7;

inline int fpm(LL b, int e, int m)
{
	b %= m;
	LL t = 1;
	for ( ; e; e >>= 1, (b *= b) %= m)
		if (e & 1) (t *= b) %= m;
	return t;
}

const int maxn = 550;

int n;
int a[maxn + 5], b[maxn + 5];

vector<int> v;

int dp[maxn + 5];

int inv[maxn + 5];

namespace fft
{

struct comp
{
	double x, y;

	comp(): x(0), y(0) { }
	comp(const double &_x, const double &_y): x(_x), y(_y) { }

};

inline comp operator+(const comp &a, const comp &b) { return comp(a.x + b.x, a.y + b.y); }
inline comp operator-(const comp &a, const comp &b) { return comp(a.x - b.x, a.y - b.y); }
inline comp operator*(const comp &a, const comp &b) { return comp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
inline comp conj(const comp &a) { return comp(a.x, -a.y); }

const double PI = acos(-1);

const int max0 = 1024, max1 = 10;

comp w[max0 + 5];
int bitrev[max0 + 5];

inline void fft(comp *a, const int &n)
{
	int tmp = 10 - __builtin_ctz(n);
	REP(i, 0, n) if (i < (bitrev[i] >> tmp)) swap(a[i], a[bitrev[i] >> tmp]);
	for (int i = 2, lyc = max0 >> 1; i <= n; i <<= 1, lyc >>= 1)
		for (int j = 0; j < n; j += i)
		{
			comp *l = a + j, *r = a + j + (i >> 1), *p = w;
			REP(k, 0, i >> 1)
			{
				comp tmp = *r * *p;
				*r = *l - tmp, *l = *l + tmp;
				++l, ++r, p += lyc;
			}
		}
}

inline void fft_prepare()
{
	REP(i, 0, max0) bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << (max1 - 1));
	REP(i, 0, max0) w[i] = comp(cos(2 * PI * i / max0), sin(2 * PI * i / max0));
}

inline void conv(int *x, int *y, int n, int *z)
{
	REP(i, 0, n) (x[i] += Mod) %= Mod, (y[i] += Mod) %= Mod;
	static comp a[max0 + 5], b[max0 + 5];
	static comp dfta[max0 + 5], dftb[max0 + 5], dftc[max0 + 5], dftd[max0 + 5];

	REP(i, 0, n) a[i] = comp(x[i] & 32767, x[i] >> 15);
	REP(i, 0, n) b[i] = comp(y[i] & 32767, y[i] >> 15);
	int N = n << 1;
	while (N & (N - 1)) N += N & -N;
	REP(i, n, N) a[i] = b[i] = comp(0, 0);
	fft(a, N), fft(b, N);
	REP(i, 0, N)
	{
		int j = (N - i) & (N - 1);
		static comp da, db, dc, dd;
		da = (a[i] + conj(a[j])) * comp(0.5, 0);
		db = (a[i] - conj(a[j])) * comp(0, -0.5);
		dc = (b[i] + conj(b[j])) * comp(0.5, 0);
		dd = (b[i] - conj(b[j])) * comp(0, -0.5);
		dfta[j] = da * dc;
		dftb[j] = da * dd;
		dftc[j] = db * dc;
		dftd[j] = db * dd;
	}
	REP(i, 0, N) a[i] = dfta[i] + dftb[i] * comp(0, 1);
	REP(i, 0, N) b[i] = dftc[i] + dftd[i] * comp(0, 1);
	fft(a, N), fft(b, N);
	REP(i, 0, n)
	{
		int da = (LL)(a[i].x / N + 0.5) % Mod;
		int db = (LL)(a[i].y / N + 0.5) % Mod;
		int dc = (LL)(b[i].x / N + 0.5) % Mod;
		int dd = (LL)(b[i].y / N + 0.5) % Mod;
		z[i] = (da + ((LL)(db + dc) << 15) + ((LL)dd << 30)) % Mod;
	}
}

}

using fft::fft_prepare;
using fft::conv;

int main()
{
#ifndef ONLINE_JUDGE
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif
	fft_prepare();
	scanf("%d", &n);
	REP(i, 0, n) scanf("%d%d", a + i, b + i), --a[i], v.pb(a[i]), v.pb(b[i]);
	sort(ALL(v));
	v.resize(unique(ALL(v)) - v.begin());
	REP(i, 0, maxn + 1) inv[i] = fpm(i, Mod - 2, Mod);
	int m = SZ(v);
	REP(i, 0, m - 1)
	{
		int sum = 1;
		int tmp = 1;
		static int foo[maxn + 5], bar[maxn + 5], baz[maxn + 5], pos[maxn + 5];
		int len = 0;
		REP(j, 0, n)
		{
			if (a[j] <= v[i] && v[i] < b[j])
			{
				tmp = (LL)tmp * (v[i + 1] - v[i] + len) % Mod * inv[len + 1] % Mod;
				foo[len] = tmp;
				bar[len] = sum;
				pos[len] = j;
				++len;
				sum = 0;
			}
			(sum += dp[j]) %= Mod;
		}
		conv(foo, bar, len, baz); 
		REP(i, 0, len) (dp[pos[i]] += baz[i]) %= Mod;
	}
	int ans = 0;
	REP(i, 0, n) (ans += dp[i]) %= Mod;
	(ans += Mod) %= Mod;
	printf("%d\n", ans);
	return 0;
}

