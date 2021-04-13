#include<iostream>
#include<cstring>
#include<cstdio>
#include<map>
using namespace std;
const int maxn=1e5+10;
const int mod=5e7+17;
struct Hash
{
	int mul[maxn];
	int rev[maxn];
	int has[maxn];
	int n;
	int ans;
	int boo[50000100];
	void init()
	{
		mul[0]=1;	for(int i=1;i<maxn;i++)	mul[i]=(mul[i-1]*130ll)%(long long)mod;
		rev[0]=1;	for(int i=1;i<maxn;i++)	rev[i]=(rev[i-1]*37307705ll)%(long long)mod;
		has[0]=0;	n=0;
	}
	inline int getkey(int p,int l)
	{
		return (((has[p+l-1]-has[p-1])%mod+mod)%mod*(long long)rev[p-1])%mod;
	}
	inline void movefront(char c)
	{
		n++;
		has[n]=((long long)has[n-1]+(long long)mul[n]*c)%(long long)mod;
		for(int i=1;i<=n;i++)
		{
			int key=getkey(i,n-i+1);
			if(boo[key]==0)	ans++;
			boo[key]++;
		} 
	}
	inline void moveback()
	{
		for(int i=1;i<=n;i++)
		{
			int key=getkey(i,n-i+1);
		//	cout<<key<<endl;
			boo[key]--;
			if(boo[key]==0)	ans--;
		}
		has[n]=0;
		n--;
	}
}h;
char opt[maxn];
int main()
{
//	freopen("hashit3.in","r",stdin);
	//freopen("out.txt","w",stdout);
	h.init();
	scanf("%s",opt);
	int len=strlen(opt);
	for(int i=0;i<len;i++)
	{
		if(opt[i]=='-')	h.moveback();
		else	h.movefront(opt[i]);
		printf("%d\n",h.ans);
	}
}
