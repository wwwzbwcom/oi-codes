#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <map>

#define rep(i, l, r) for(int i=l; i<=r; i++)
#define dow(i, l, r) for(int i=l; i>=r; i--)
#define travel(x) for(edge *p=fir[x]; p; p=p->n)
#define clr(x,c) memset(x, c, sizeof(x))

#define pb push_back
#define all(x) (x).begin(),(x).end()
#define l(x) Left[x]
#define r(x) Right[x]

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> Pii;
inline int read()
{
	int x=0,f=0; char ch=getchar();
	while (ch<'0' || '9'<ch) f|=ch=='-', ch=getchar();
	while ('0'<=ch && ch<='9') x=x*10+ch-'0', ch=getchar();
	return f?-x:x;
}

#define maxn 509
#define maxm 1009
#define Q 1000000007

int inv[maxn], n, mx, x[maxn], y[maxn], f[maxm][maxn], g[maxn];
vector<int>v;

int main()
{
	inv[1]=1; rep(i, 2, 500) inv[i]=(Q-1LL*Q/i*inv[Q%i]%Q)%Q;
	
	n=read();
	rep(i, 1, n) x[i]=read(), y[i]=read()+1, v.pb(x[i]), v.pb(y[i]);
	sort(all(v)); v.erase(unique(all(v)),v.end()); mx=v.size()-1;
	rep(i, 1, n) x[i]=lower_bound(all(v),x[i])-v.begin()+1, y[i]=lower_bound(all(v),y[i])-v.begin()+1;
	
	rep(o, 1, mx)
	{
		clr(g,0); g[0]=1; int tot=0, d=v[o]-v[o-1];
		rep(i, 1, n)
		{
			if (x[i]<=o && o<y[i])
			{
				tot++;
				dow(j, min(tot,d), 1) 
					(f[o][i]+=1LL*g[j-1]*(d-j+1)%Q*inv[j]%Q)%=Q,
					(g[j]+=1LL*g[j-1]*(d-j+1)%Q*inv[j]%Q)%=Q;
			}
			(f[o][i]+=f[o-1][i])%=Q;
			(g[0]+=f[o-1][i])%=Q;
		}
	}
	int A=0; rep(i, 1, n) (A+=f[mx][i])%=Q; printf("%d\n", A);
	return 0;
}
